#pragma once
#include "ICommand.h"

class ShowTablesCommand : public ICommand{

    private:
        TableManager* tableManager;

    public:

        ShowTablesCommand(TableManager*);

        void execute();

};