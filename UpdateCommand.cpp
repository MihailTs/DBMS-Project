#include "UpdateCommand.h"

UpdateCommand::UpdateCommand(TableManager* _tableManager, const std::string& _tableName,
                                 const std::string& _searchField, const std::string& _searchValue,
                                    const std::string& _targetField, const std::string& _targetValue){
    tableManager = _tableManager;
    tableName = _tableName;
    searchField = _searchField;
    searchValue = _searchValue;
    targetField = _targetField;
    targetValue = _targetValue;
}

void UpdateCommand::execute(){
    tableManager->getTable(tableName)->update(searchField, searchValue, targetField, targetValue);
}