#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_

#include "tokenizer.h"
#include <map>

// TODO: add these commands:
// - project
// - add_executable
// - add_library
// - add_subdirectory
// - find_package
// - target_link_libraries
// - target_include_directories
// - target_compile_definitions
// - target_compile_options
// - target_compile_features
// - foreach
// - cmake_minimum_required

class InterpreterContext
{
    std::map<std::string, std::string> _variables;

public:
    InterpreterContext();
    virtual ~InterpreterContext();

    std::string& variable(const std::string& name);
    void setVariable(const std::string& name, const std::string& value);

public:
    std::string extractVariableValue(const std::string& token);
};

class Command
{
protected:
    std::string _command;
    std::vector<std::string> _parameters;

public:
    Command(const std::string& command, const std::vector<std::string>& parameters);
    virtual ~Command();

    virtual void Run(InterpreterContext& context, std::vector<std::string>::const_iterator& itr) = 0;
};

class IfCommand : public Command
{
    std::vector<Command*> _subcommands;
public:
    IfCommand(const std::vector<std::string>& parameters);
    virtual ~IfCommand();

    virtual void Run(InterpreterContext& context, std::vector<std::string>::const_iterator& itr);

};

class SetCommand : public Command
{
public:
    SetCommand(const std::vector<std::string>& parameters);
    virtual ~SetCommand();

    virtual void Run(InterpreterContext& context, std::vector<std::string>::const_iterator& itr);

};

class Interpreter
{
    std::vector<Command*> _commands;
    static bool Equals(const std::string& a, const std::string& b);

public:
    Interpreter(const std::vector<std::string>& tokens);
    virtual ~Interpreter();

    static Command* RunInterpreter(InterpreterContext& context, std::vector<std::string>::const_iterator& itr);
    static Command* ConstructCommand(InterpreterContext& context, const std::string& command, const std::vector<std::string>& parameters);
};

#endif // _INTERPRETER_H_
