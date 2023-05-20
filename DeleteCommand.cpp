#include "DeleteCommand.h"

DeleteCommand::DeleteCommand(TableManager* _tableManager, const std::string& _tableName, const std::string& _searchField, const std::string& _value){
    tableManager = _tableManager;
    tableName = _tableName;
    searchField = _searchField;
    value = _value;
}

void DeleteCommand::execute(){
    tableManager->getTable(tableName)->deleteValues(searchField, value);
}