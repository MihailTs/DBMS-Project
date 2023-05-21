#include "OpenCommand.h"

OpenCommand::OpenCommand(TableManager* _tableManager, const std::string& _tableName){
    tableManager = _tableManager;
    tableName = _tableName;
}

void OpenCommand::execute(){
    if(!tableManager->contains(tableName)) throw std::invalid_argument("No table with such name!");
    tableManager->openTable(tableName);
    std::cout << "Table opened successfully" << "\n";
}