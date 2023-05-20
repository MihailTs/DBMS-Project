#pragma once
#include "ICommand.h"

class CountCommand : public ICommand{

    private:
        TableManager* tableManager;
        std::string tableName;
        std::string searchField;
        std::string value;

    public:
        CountCommand(TableManager*, const std::string&, const std::string&, const std::string&);

        void execute();
};