#include "ShowTablesCommand.h"

ShowTablesCommand::ShowTablesCommand(TableMenager* _tableMenager){
    tableMenager = _tableMenager;
}

void ShowTablesCommand::execute(){
    tableMenager->showTables();
}