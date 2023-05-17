#include "InsertCommand.h"

InsertCommand::InsertCommand(TableManager* _tableManager, const std::string& _tableName, const std::vector<std::string>& _values){
    tableManager = _tableManager;
    tableName = _tableName;
    values = _values;
}

void InsertCommand::execute(){
    tableManager->getTable(tableName)->insertRecord(values);
}
