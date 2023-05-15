#include "RenameCommand.h"

RenameCommand::RenameCommand(TableManager* _tableManager, const std::string& _oldName, const std::string& _newName){
    tableManager = _tableManager;
    oldName = _oldName;
    newName = _newName;
}

void RenameCommand::execute(){
    if(oldName == newName) return;
    if(tableManager->contains(newName)) throw std::invalid_argument("The new name is not unique!");
    tableManager->getTable(oldName)->setTableName(newName);
}