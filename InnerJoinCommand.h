#pragma once
#include "ICommand.h"

class InnerJoinCommand : public ICommand{

    private:
        TableManager* tableManager;
        std::string table1;
        std::string field1;
        std::string table2;
        std::string field2;
        std::string newTableName;

    public:
        InnerJoinCommand(TableManager*, const std::string&, const std::string&, const std::string&, 
                            const std::string&, const std::string&);

        void execute();

};