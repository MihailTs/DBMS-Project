#include "ShowTablesCommand.h"

ShowTablesCommand::ShowTablesCommand(TableManager* _tableManager){
    tableManager = _tableManager;
}

void ShowTablesCommand::execute(){
    tableManager->showTables();
}