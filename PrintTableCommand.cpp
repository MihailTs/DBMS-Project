#include "PrintTableCommand.h"

PrintTableCommand::PrintTableCommand(TableMenager* _tableMenager, const std::string& _tableName){
    tableMenager = _tableMenager;
    tableName = _tableName;
}

void PrintTableCommand::execute(){
    getTableMenager()->openTable(getTableName());
    getTableMenager()->getTable(getTableName())->printTable();
}

std::string PrintTableCommand::getTableName(){
    return tableName;
}

TableMenager* PrintTableCommand::getTableMenager(){
    return tableMenager;
}