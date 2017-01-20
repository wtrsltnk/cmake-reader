#include <iostream>
#include <string>
#include <sstream>
#include "tokenizer.h"
#include "interpreter.h"

int main(int argc, char* argv[])
{
    if (argc <= 1)
    {
        std::cout << "No parameters to work with..." << std::endl;
        return 0;
    }

    Tokenizer t(argv[1]);

    for (auto itr : t.AllTokens())
    {
        std::cout << itr << std::endl;
    }

    Interpreter i(t.AllTokens());

    return 0;
}
