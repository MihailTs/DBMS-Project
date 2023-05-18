#include "SaveCommand.h"
#include <stdexcept>

SaveCommand::SaveCommand(TableManager* _tableManager, const std::string& _tableName){
    tableManager = _tableManager;
    tableName = _tableName;
}

void SaveCommand::execute(){
    if(!tableManager->contains(tableName)) throw std::invalid_argument("No table with such name!");
    tableManager->saveTable(tableName);
}
