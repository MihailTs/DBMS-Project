#pragma once
#include "ICommand.h"

class DropTableCommand : public ICommand{

    private:
        TableManager* tableManager;
        std::string tableName;

    public:
        DropTableCommand(TableManager*, const std::string&);

        void execute();

};