#include "SaveCommand.h"
#include <stdexcept>

SaveCommand::SaveCommand(TableManager* _tableManager, const std::string& _tableName){
    tableManager = _tableManager;
    tableName = _tableName;
}

void SaveCommand::execute(){
    tableManager->saveTable(tableName);
    std::cout << "Table saved successfully!\n"; 
}
