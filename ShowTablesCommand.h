#pragma once
#include "ICommand.h"

class ShowTablesCommand : public ICommand{

    private:
        TableMenager* tableMenager;

    public:

        ShowTablesCommand(TableMenager*);

        void execute();

};