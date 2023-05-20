#include "ExitCommand.h"

ExitCommand::ExitCommand(TableManager* _tableManager){
    tableManager = _tableManager;
}

void ExitCommand::execute(){
    delete tableManager;
    std::cout << "Goodbye!";
    exit(0);
}