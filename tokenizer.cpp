#include "tokenizer.h"
#include <fstream>

Tokenizer::Tokenizer(const std::string& filename)
    : _inputstream(filename.c_str()), c('\0')
{
    if (this->_inputstream.good())
        this->_inputstream.get(c);
}

Tokenizer::~Tokenizer()
{ }

void Tokenizer::skipSpaces()
{
    while (this->_inputstream.good() && c <= ' ')
    {
        this->_inputstream.get(c);
    }
    if (!this->_inputstream.good()) c = '\0';
}

void Tokenizer::nextChar()
{
    if (this->_inputstream.good())
    {
        this->_inputstream.get(c);
    }
    else
        c = '\0';
}

std::string Tokenizer::returnToken(const std::string& token)
{
    this->_alltokens.push_back(token);
    return token;
}

std::string Tokenizer::NextToken()
{
    std::string token;

    if (c <= ' ')
    {
        this->skipSpaces();
    }

    if (c == '#')
    {
        while (this->_inputstream.good() && c != '\n')
        {
            token += c;
            this->nextChar();
        }
        if (!this->_inputstream.good())
            c = '\0';
        else
        {
            return returnToken(token);
        }
    }

    if (c == '(')
    {
        this->nextChar();
        return returnToken("(");
    }
    else if (c == ')')
    {
        this->nextChar();
        return returnToken(")");
    }
    else if (c == '\"')
    {
        token += c;
        this->nextChar();
        while (this->_inputstream.good() && c != '\"')
        {
            token += c;
            this->nextChar();
        }
        token += c;
        this->nextChar();
        return returnToken(token);
    }

    while (c != 0)
    {
        if (c <= ' ')
        {
            return returnToken(token);
        }
        else if (c == '(')
        {
            return returnToken(token);
        }
        else if (c == ')')
        {
            return returnToken(token);
        }
        else if (c == '\"')
        {
            return returnToken(token);
        }
        else
        {
            token += c;
        }

        this->nextChar();
    }

    return returnToken(token);
}

const std::vector<std::string>& Tokenizer::AllTokens()
{
    if (!this->_inputstream.eof())
    {
        auto token = NextToken();
        while (token != "")
        {
            token = NextToken();
        }
    }

    return this->_alltokens;
}
