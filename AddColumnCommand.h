#pragma once
#include "ICommand.h"

class AddColumnCommand : public ICommand{

    private:
        TableManager* tableManager;
        std::string tableName;
        std::string fieldName;
        std::string fieldType;

    public:
        AddColumnCommand(TableManager*, const std::string&, const std::string&, const std::string&);

        void execute();
};