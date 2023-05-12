#include "DescribeCommand.h"

DescribeCommand::DescribeCommand(TableManager* _tableManager, const std::string& _tableName){
    tableManager = _tableManager;
    tableName = _tableName;
}

void DescribeCommand::execute(){
    getTableManager()->getTable(getTableName())->describe();
}

std::string DescribeCommand::getTableName(){
    return tableName;
}

TableManager* DescribeCommand::getTableManager(){
    return tableManager;
}