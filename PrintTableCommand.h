#pragma once
#include "ICommand.h"
#include "TableMenager.h"

class PrintTableCommand : public ICommand{

    private:
        TableMenager* tableMenager;
        std::string tableName;

    public:
        PrintTableCommand(TableMenager*, const std::string&);

        void execute();

        std::string getTableName();

        TableMenager* getTableMenager();



};