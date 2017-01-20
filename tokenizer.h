#ifndef _TOKENIZER_H_
#define _TOKENIZER_H_

#include <vector>
#include <string>
#include <fstream>

class Tokenizer
{
    std::ifstream _inputstream;
    char c;
    void skipSpaces();
    void nextChar();
    std::vector<std::string> _alltokens;

    std::string returnToken(const std::string& token);
public:
    Tokenizer(const std::string& filename);
    virtual ~Tokenizer();

    std::string NextToken();
    const std::vector<std::string>& AllTokens();
};

#endif // _TOKENIZER_H_
