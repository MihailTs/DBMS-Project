#pragma once
#include "ICommand.h"

class AgregateCommand : public ICommand{

    private:
        TableManager* tableManager;
        std::string tableName;
        std::string searchField;
        std::string searchValue;
        std::string targetField;
        std::string operation;

    public:
        AgregateCommand(TableManager*, const std::string&, const std::string&, const std::string&, 
                            const std::string&, const std::string&);

        void execute();

};