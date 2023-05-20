#pragma once
#include <cstdlib>
#include "ICommand.h"

class ExitCommand : public ICommand{

    private:
        TableManager* tableManager;

    public:
    	
        ExitCommand(TableManager*);

        void execute();

};