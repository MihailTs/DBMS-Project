#include "SelectCommand.h"

SelectCommand::SelectCommand(TableManager* _tableManager, const std::string& _tableName, const std::string& _fieldName, const std::string& _value){
    tableManager = _tableManager;
    tableName = _tableName;
    fieldName = _fieldName;
    value = _value;
}

void SelectCommand::execute(){
    tableManager->getTable(tableName)->select(fieldName, value);
}