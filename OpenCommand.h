#pragma once
#include "ICommand.h"

//Тази команда на практика е излишна, но е добавена с цел изпълнение на условията на задачата
//При подаване на команда необходимата таблица автоматично се отваря, ако не е била отворена преди това
class OpenCommand : public ICommand{

    private:
        TableManager* tableManager;
        std::string tableName;

    public:
        OpenCommand(TableManager*, const std::string&);

        void execute();

};