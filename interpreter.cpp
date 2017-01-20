#include "interpreter.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>

InterpreterContext::InterpreterContext(Tokenizer &tokenizer)
    : _tokenizer(tokenizer)
{ }

InterpreterContext::~InterpreterContext() { }

Tokenizer& InterpreterContext::tokenizer()
{
    return this->_tokenizer;
}

std::string& InterpreterContext::variable(const std::string& name)
{
    if (this->_variables.find(name) == this->_variables.end()) throw std::runtime_error(std::string("Unknown variable name ") + name);

    return this->_variables[name];
}

void InterpreterContext::setVariable(const std::string& name, const std::string& value)
{
    if (this->_variables.find(name) == this->_variables.end())
        this->_variables.insert(std::make_pair(name, value));
    else
        this->_variables[name] = value;
}

Interpreter::Interpreter(Tokenizer& t)
{
    InterpreterContext context(t);
    auto itr = t.AllTokens().cbegin();
    while (*itr != "")
    {
        auto i = Interpreter::RunInterpreter(context, itr);
        if (i != nullptr)
            this->_commands.push_back(i);
    }
}

Interpreter::~Interpreter()
{ }

bool Interpreter::Equals(const std::string& a, const std::string& b)
{
    std::string aa = a, bb = b;
    std::transform(aa.begin(), aa.end(), aa.begin(), ::tolower);
    std::transform(bb.begin(), bb.end(), bb.begin(), ::tolower);
    return aa == bb;
}

Command* Interpreter::RunInterpreter(InterpreterContext& context, std::vector<std::string>::const_iterator& itr)
{
    Command* result = nullptr;

    if (*itr != "")
    {
        while ((*itr)[0] == '#')
        {
            ++itr;
            if (*itr == "") return result;
        }

        // we assume everything is a command
        std::string command = *itr++;

        if (*itr == "")
        {
            throw std::runtime_error("unexpected end of file");
        }
        else if (*itr != "(")
        {
            throw std::runtime_error("Invalid token, i am looking for '('");
        }

        ++itr;  // skip (

        // grab all parameters until the next )
        std::vector<std::string> parameters;
        while (*itr != "" && *itr != ")")
        {
            parameters.push_back(*itr);
            ++itr;
        }
        if (*itr == "") throw std::runtime_error("unexpected end of file");

        ++itr;  // skip )

        auto i = Interpreter::ConstructCommand(context, command, parameters);
        if (i != nullptr)
        {
            i->Run(context, itr);
            result = i;
        }
    }

    return result;
}

Command* Interpreter::ConstructCommand(InterpreterContext& context, const std::string& command, const std::vector<std::string>& parameters)
{
    std::cout << "command: " << command << std::endl;
    for (auto param : parameters)
        std::cout << "    param: " << param << std::endl;

    if (Interpreter::Equals(command, "if"))
    {
        return new IfCommand(parameters);
    }
    else if (Interpreter::Equals(command, "set"))
    {
        return new SetCommand(parameters);
    }
    return nullptr;
}

Command::Command(const std::string& command, const std::vector<std::string>& parameters)
    : _command(command), _parameters(parameters)
{ }

Command::~Command()
{ }

IfCommand::IfCommand(const std::vector<std::string>& parameters)
    : Command("if", parameters)
{ }

IfCommand::~IfCommand()
{ }

void IfCommand::Run(InterpreterContext& context, std::vector<std::string>::const_iterator& itr)
{
    while (*itr != "" && *itr != "endif")
    {
        auto i = Interpreter::RunInterpreter(context, itr);
        if (i != nullptr)
            this->_subcommands.push_back(i);
    }
    ++itr;  // skip endif

    if (*itr == "")
    {
        throw std::runtime_error("unexpected end of file");
    }
    else if (*itr != "(")
    {
        throw std::runtime_error("Invalid token, i am looking for '('");
    }
    else
        ++itr;  // skip (

    while (*itr != "" && *itr != ")") ++itr;

    if (*itr == "")
    {
        throw std::runtime_error("unexpected end of file");
    }
    else
        ++itr;  // skip )
}

SetCommand::SetCommand(const std::vector<std::string>& parameters)
    : Command("set", parameters)
{ }

SetCommand::~SetCommand()
{ }

void SetCommand::Run(InterpreterContext& context, std::vector<std::string>::const_iterator& itr)
{ }
