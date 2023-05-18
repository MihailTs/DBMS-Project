#include "ImportCommand.h"

ImportCommand::ImportCommand(TableManager* _tableManager, const std::string& _tableName, const std::string& _fileAddress){
    tableManager = _tableManager;
    tableName = _tableName;
    fileAddress = _fileAddress;
}

void ImportCommand::execute(){
    tableManager->importTable(tableName, fileAddress);
}