#pragma once
#include "ICommand.h"

class PrintTableCommand : public ICommand{

    private:
        TableManager* tableManager;
        std::string tableName;

    public:
        PrintTableCommand(TableManager*, const std::string&);

        void execute();

        std::string getTableName();

        TableManager* getTableManager();



};