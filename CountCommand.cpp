#include "CountCommand.h"

CountCommand::CountCommand(TableManager* _tableManager, const std::string& _tableName, const std::string& _searchField, const std::string& _value){
    tableManager = _tableManager;
    tableName = _tableName;
    searchField = _searchField;
    value = _value;
}

void CountCommand::execute(){
    std::cout << tableManager->getTable(tableName)->countValues(searchField, value) << "\n";
}