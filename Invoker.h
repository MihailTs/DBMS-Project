#pragma once
#include <string>
#include "ICommand.h"
#include "TableMenager.h"


class Invoker{

    private:

        //Така ще достъпваме таблиците, за да изпълняваме команди
        TableMenager* tableMenager;

        //Съхранява се като указател, защото ICommand е просто интерфейс(абстрактен)
        ICommand* command;

    public:

        Invoker(TableMenager*);

        Invoker(TableMenager*, const std::string&);

        void setCommand(const std::string&);
        
        ICommand* getCommand();

        ~Invoker();
};