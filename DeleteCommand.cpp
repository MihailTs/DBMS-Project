#include "DeleteCommand.h"

DeleteCommand::DeleteCommand(TableManager* _tableManager, const std::string& _tableName, const std::string& _searchColumn, const std::string& _value){
    tableManager = _tableManager;
    tableName = _tableName;
    searchColumn = _searchColumn;
    value = _value;
}

void DeleteCommand::execute(){
    tableManager->getTable(tableName)->deleteValues(searchColumn, value);
}