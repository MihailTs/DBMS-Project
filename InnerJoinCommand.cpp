#include "InnerJoinCommand.h"

InnerJoinCommand::InnerJoinCommand(TableManager* _tableManager, const std::string& _table1, const std::string& _field1,
                                     const std::string& _table2, const std::string& _field2, const std::string& _newTableName){
    tableManager = _tableManager;
    table1 = _table1;
    field1 = _field1;
    table2 = _table2;
    field2 = _field2;
    newTableName = _newTableName;
}

void InnerJoinCommand::execute(){
    tableManager->innerJoin(table1, field1, table2, field2, newTableName);
}