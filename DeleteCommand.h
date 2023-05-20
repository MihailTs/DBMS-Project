#pragma once
#include "ICommand.h"

class DeleteCommand : public ICommand{

    private:
        TableManager* tableManager;
        std::string tableName;
        std::string searchField;
        std::string value;

    public:
        DeleteCommand(TableManager*, const std::string&, const std::string&, const std::string&);

        void execute();

};