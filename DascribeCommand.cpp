#include "DescribeCommand.h"

DescribeCommand::DescribeCommand(TableMenager* _tableMenager, const std::string& _tableName){
    tableMenager = _tableMenager;
    tableName = _tableName;
}

void DescribeCommand::execute(){
    getTableMenager()->openTable(getTableName());
    getTableMenager()->getTable(getTableName())->describe();
}

std::string DescribeCommand::getTableName(){
    return tableName;
}

TableMenager* DescribeCommand::getTableMenager(){
    return tableMenager;
}