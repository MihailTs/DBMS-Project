#include "DropTableCommand.h"

DropTableCommand::DropTableCommand(TableManager* _tableManager, const std::string& _tableName){
    tableManager = _tableManager;
    tableName = _tableName;
}

void DropTableCommand::execute(){
    tableManager->dropTable(tableName);
}