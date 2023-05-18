#pragma once
#include <string>
#include "ICommand.h"
#include "HelpCommand.h"
#include "ExitCommand.h"
#include "DescribeCommand.h"
#include "TableManager.h"
#include "PrintTableCommand.h"
#include "ShowTablesCommand.h"
#include "InsertCommand.h"
#include "AddColumnCommand.h"
#include "RenameCommand.h"
#include "SelectCommand.h"
#include "ExportCommand.h"
#include "SaveCommand.h"
#include "SaveAsCommand.h"
#include "ImportCommand.h"

class Invoker{

    private:

        //Така ще достъпваме таблиците, за да изпълняваме команди
        TableManager* tableManager;

        //Съхранява се като указател, защото ICommand е просто интерфейс(абстрактен)
        ICommand* command;

        //Някои функциии за обработка на командите, представени като низ
        std::string trim(const std::string&);

        std::string toLower(const std::string&);

        std::vector<std::string> splitLine(const std::string&);

        std::string getFirstValue(const std::string&, int*);

        std::string removeParentheses(const std::string&);

    public:

        Invoker(TableManager*);

        Invoker(TableManager*, const std::string&);

        void setCommand(const std::string&);
        
        ICommand* getCommand();

        ~Invoker();
};