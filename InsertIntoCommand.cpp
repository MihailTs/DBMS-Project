#include "InsertIntoCommand.h"

InsertIntoCommand::InsertIntoCommand(TableManager* _tableManager, const std::string& _tableName, const std::vector<std::string>& _values){
    tableManager = _tableManager;
    tableName = _tableName;
    values = _values;
}

void InsertIntoCommand::execute(){
    tableManager->getTable(tableName)->insertRecord(values);
}
