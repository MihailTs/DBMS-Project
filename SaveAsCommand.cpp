#include "SaveAsCommand.h"

SaveAsCommand::SaveAsCommand(TableManager* _tableManager, const std::string& _tableName, const std::string& _saveAddress){
    tableManager = _tableManager;
    tableName = _tableName;
    saveAddress = _saveAddress;
}

void SaveAsCommand::execute(){
    tableManager->saveTable(tableName);
    tableManager->getTable(tableName)->writeToFile(saveAddress);
    std::cout << "Table saved successfully!\n"; 
}