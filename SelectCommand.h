#pragma once
#include "ICommand.h"

class SelectCommand : public ICommand{

    private:
        TableManager* tableManager;
        std::string tableName;
        std::string fieldName;
        std::string value;

    public:
        SelectCommand(TableManager*, const std::string&, const std::string&, const std::string&);

        void execute();
};