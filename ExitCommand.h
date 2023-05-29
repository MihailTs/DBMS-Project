#pragma once
#include <cstdlib>
#include "ICommand.h"

class ExitCommand : public ICommand{

    private:
        TableManager* tableManager;

        void askToSave(const std::string&);

        std::string toLower(const std::string&);

    public:
    	
        ExitCommand(TableManager*);

        void execute();

};