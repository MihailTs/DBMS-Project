#pragma once
#include "ICommand.h"

class UpdateCommand : public ICommand{

    private:
        TableManager* tableManager;
        std::string tableName;
        std::string searchField;
        std::string searchValue;
        std::string targetField;
        std::string targetValue;

    public:
        UpdateCommand(TableManager*, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&);

        void execute();
};