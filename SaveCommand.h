#pragma once
#include "ICommand.h"

class SaveCommand : public ICommand{

    private:
        TableManager* tableManager;
        std::string tableName;

    public:
        //Име на таблица
        SaveCommand(TableManager*, const std::string&);

        void execute();
};