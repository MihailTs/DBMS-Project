#pragma once
#include "ICommand.h"

class CloseCommand : public ICommand{

    private:
        TableManager* tableManager;
        std::string tableName;

        std::string toLower(const std::string&);

    public:
        CloseCommand(TableManager*, const std::string&);

        void execute();



};