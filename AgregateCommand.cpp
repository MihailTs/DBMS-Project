#include "AgregateCommand.h"

AgregateCommand::AgregateCommand(TableManager* _tableManager, const std::string& _tableName, const std::string& _searchField,
                                     const std::string& _searchValue, const std::string& _targetField, const std::string& _operation){
    tableManager = _tableManager;
    tableName = _tableName;
    searchField = _searchField;
    searchValue = _searchValue;
    targetField = _targetField;
    operation = _operation;
}

void AgregateCommand::execute(){
    tableManager->getTable(tableName)->agregate(searchField, searchValue, targetField, operation);
}