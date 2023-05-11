#pragma once
#include <string>
#include "ICommand.h"
#include "HelpCommand.h"
#include "ExitCommand.h"
#include "DescribeCommand.h"
#include "TableMenager.h"
#include "PrintTableCommand.h"
#include "ShowTablesCommand.h"


class Invoker{

    private:

        //Така ще достъпваме таблиците, за да изпълняваме команди
        TableMenager* tableMenager;

        //Съхранява се като указател, защото ICommand е просто интерфейс(абстрактен)
        ICommand* command;

        //Някои функциии за обработка на командите, представени като низ
        std::string trim(const std::string&);

        std::string toLower(const std::string&);

    public:

        Invoker(TableMenager*);

        Invoker(TableMenager*, const std::string&);

        void setCommand(const std::string&);
        
        ICommand* getCommand();

        ~Invoker();
};