/*********************************************************************
*                                                                    *
*                   SIMPLE BRAINFUCK INTERPRETER                     *
*        By Koushtav Chakrabarty a.k.a The Illusionist Mirage        *
*                                                                    *
*********************************************************************/


#include "Interpreter.hpp"

bfck::Interpreter::Interpreter(const std::string &fileName) : _srcFileName(fileName)
{
    try{
        _dataCell.resize(30000, 0);
        _dataCell_ptr = _dataCell.begin();
    }
    catch(std::runtime_error &e){
        std::cout << e.what() << std::endl;
    }
    open(_srcFileName);
}

void bfck::Interpreter::open(const std::string &fileName)
{
    _srcFile.open(fileName, std::ios::in);
    if(!_srcFile.is_open())
        throw std::runtime_error("ERROR :: Couldn't open brainfuck source file '" + fileName + "' !");
}

bool bfck::Interpreter::isValidCommand(char command)
{
    /*for(auto validCommands : { '<', '>', '+', '-', '.', ',', '[', ']' } )
        if(command == validCommands)
            return true;
    return false;*/
    std::vector<char> validCommands{ '<', '>', '+', '-', '.', ',', '[', ']' };
    return std::find(validCommands.begin(), validCommands.end(), command) != validCommands.end();
}

void bfck::Interpreter::parse()
{
    char inputChar;
    while(_srcFile.get(inputChar))
    {
        if(isValidCommand(inputChar))
            _commands += inputChar;
    }
}

void bfck::Interpreter::displayParsedCode()
{
    std::cout << _commands << std::endl;
}

void bfck::Interpreter::checkForErrors()
{
    auto _itr = _commands.begin();
    int loopCounter = 0;
    for( ; _itr != _commands.end(); _itr++)
    {
        switch(*_itr)
        {
            case '[':
                {
                    loopCounter++;
                } break;

            case ']':
                {
                    if(loopCounter == 0)
                        throw std::logic_error("ERROR :: No matching '[' found for a corresponding ']' in the source file!");
                    else
                        loopCounter--;
                } break;
        }
    }
    if(loopCounter != 0)
        throw std::logic_error("ERROR :: No matching ']' found for a corresponding '[' in the source file!");
}

void bfck::Interpreter::execute()
{
    for(auto _ins_ptr = _commands.begin(); _ins_ptr != _commands.end(); _ins_ptr++)
    {
        switch((*_ins_ptr))
        {
            case '<':
                {
                    _dataCell_ptr--;
                } break;

            case '>':
                {
                    _dataCell_ptr++;
                } break;

            case '+':
                {
                    (*_dataCell_ptr)++;
                } break;

            case '-':
                {
                    if((*_dataCell_ptr) > 0)(*_dataCell_ptr)--;
                } break;

            case '.':
                {
                    if((*_dataCell_ptr) == 10)
                        std::cout << "\n";
                    else if((*_dataCell_ptr) == 13)
                        std::cout << "\r";
                    else
                        std::cout << (char)(*_dataCell_ptr);
                } break;

            case ',':
                {
                    std::cin >> (*_dataCell_ptr);
                } break;

            case '[':
                {
                    if((*_dataCell_ptr) != 0)
                        _loopStack.push(_ins_ptr);
                    else
                    {
                        int loopCounter = 0;
                        for(auto _itr = _ins_ptr + 1; _itr != _commands.end(); _itr++)
                        {
                            if(*_itr == '[')
                                loopCounter++;
                            else if(*_itr == ']' && loopCounter != 0)
                                loopCounter--;
                            else if(*_itr == ']' && loopCounter == 0)
                            {
                                _ins_ptr = _itr;
                                break;
                            }
                        }
                    }

                } break;

            case ']':
                {
                    if((*_dataCell_ptr) != 0)
                        _ins_ptr = _loopStack.top();
                    else
                    {
                        _loopStack.pop();
                    }
                } break;
        }
    }
}

bfck::Interpreter::~Interpreter()
{
    _srcFile.close();
}
