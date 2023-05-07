#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "ICommand.h"
#include "Table.h"
#include "TableMenager.h"

class DescribeCommand : public ICommand{

    private:
        TableMenager* tableMenager;
        std::string tableName;

    public:
        DescribeCommand(TableMenager*, const std::string&);

        void execute();

        std::string getTableName();

        TableMenager* getTableMenager();

};