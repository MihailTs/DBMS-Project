#pragma once
#include <vector>
#include <string>
#include "ICommand.h"
#include "Table.h"

class DescribeCommand{

    private:
        TableMenager* tableMenager;
        std::string tableName;

    public:
        DescribeCommand(TableMenager*, const std::string&);

        void execute();

};