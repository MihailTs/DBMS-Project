#include "ExitCommand.h"

void ExitCommand::execute(){
    std::cout << "Goodbye!";
    exit(0);
}