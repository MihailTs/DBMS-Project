#include "PrintTableCommand.h"

PrintTableCommand::PrintTableCommand(TableManager* _tableManager, const std::string& _tableName){
    tableManager = _tableManager;
    tableName = _tableName;
}

void PrintTableCommand::execute(){
    getTableManager()->getTable(getTableName())->printTable();
}

std::string PrintTableCommand::getTableName(){
    return tableName;
}

TableManager* PrintTableCommand::getTableManager(){
    return tableManager;
}