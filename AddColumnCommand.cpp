#include "AddColumnCommand.h"

AddColumnCommand::AddColumnCommand(TableManager* _tableManager, const std::string& _tableName, const std::string& _fieldName, const std::string& _fieldType){
    tableManager = _tableManager;
    tableName = _tableName;
    fieldName = _fieldName;
    fieldType = _fieldType;
}

void AddColumnCommand::execute(){
    tableManager->getTable(tableName)->addField(fieldName, fieldType);
}