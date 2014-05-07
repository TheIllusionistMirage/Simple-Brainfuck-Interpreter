/*********************************************************************
*                                                                    *
*                   SIMPLE BRAINFUCK INTERPRETER                     *
*        By Koushtav Chakrabarty a.k.a The Illusionist Mirage        *
*                                                                    *
*********************************************************************/


#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP


#define DEFAULT_FILE_NAME "HelloWorld.bf"

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <stack>

namespace bfck
{
    class Interpreter
    {
        public:
            Interpreter(const std::string &fileName = DEFAULT_FILE_NAME);
            ~Interpreter();
            void execute();
            void parse();
            void displayParsedCode();
            void checkForErrors();

        private:
            bool isValidCommand(char command);
            void open(const std::string &fileName = DEFAULT_FILE_NAME);

            std::string _commands;
            std::string _srcFileName;
            std::ifstream _srcFile;
            std::vector<int> _dataCell;
            std::vector<int>::iterator _dataCell_ptr;
            std::stack<std::string::iterator> _loopStack;
    };
}

#endif // INPTERPRETER_HPP
