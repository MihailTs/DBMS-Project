#pragma once
#include "ICommand.h"
#include <string>
#include <vector>

class InsertCommand : public ICommand{

    private:
        TableManager* tableManager;
        std::string tableName;
        std::vector<std::string> values;

    public:
        InsertCommand(TableManager*, const std::string&, const std::vector<std::string>&);

        void execute();

};