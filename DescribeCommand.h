#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "ICommand.h"

class DescribeCommand : public ICommand{

    private:
        TableManager* tableManager;
        std::string tableName;

    public:
        DescribeCommand(TableManager*, const std::string&);

        void execute();

        std::string getTableName();

        TableMenager* getTableManager();

};