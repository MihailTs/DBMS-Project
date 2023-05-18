#pragma once
#include "ICommand.h"

class ImportCommand : public ICommand{

    private:
        TableManager* tableManager;
        std::string tableName;
        std::string fileAddress;

    public:
        ImportCommand(TableManager*, const std::string&, const std::string&);

        void execute();
};