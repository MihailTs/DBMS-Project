#pragma once
#include "ICommand.h"
#include <string>
#include <vector>

class InsertIntoCommand : public ICommand{

    private:
        TableManager* tableManager;
        std::string tableName;
        std::vector<std::string> values;

    public:
        InsertIntoCommand(TableManager*, const std::string&, const std::vector<std::string>&);

        void execute();

};