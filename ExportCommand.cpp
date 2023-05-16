#include "ExportCommand.h"

ExportCommand::ExportCommand(TableManager* _tableManager, const std::string& _tableName, const std::string& _fileAddress){
    tableManager = _tableManager;
    tableName = _tableName;
    fileAddress = _fileAddress;
}

void ExportCommand::execute(){
    tableManager->getTable(tableName)->writeToFile(fileAddress);
}