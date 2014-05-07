/*********************************************************************
*                                                                    *
*                   SIMPLE BRAINFUCK INTERPRETER                     *
*        By Koushtav Chakrabarty a.k.a The Illusionist Mirage        *
*                                                                    *
**********************************************************************
*                                                                    *
*   This simple interpreter for the brainfuck programming language   *
*   was written by me as a  small  programming assignment upon the   *
*   recommendation of texus(one of my best buddies). Also, special   *
*   thanks to him for bearing with me whenever the possible seemed   *
*   impossible to me.                                                *
*                                                                    *
*********************************************************************/


#include "Interpreter.hpp"

int main(int argc, char *argv[])
{
    std::string bf_srcFile;
    std::cin >> bf_srcFile;

    bfck::Interpreter simple_brainfuck_interpreter(bf_srcFile);
    simple_brainfuck_interpreter.parse();
    simple_brainfuck_interpreter.checkForErrors();
    simple_brainfuck_interpreter.execute();

    return 0;
}
