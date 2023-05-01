#pragma once
#include <string>
#include "ICommand.h"


class Invoker{

    private:

        //Съхранява се като указател, защото ICommand е просто интерфейс(абстрактен)
        ICommand* command;

    public:

        Invoker();

        Invoker(const ICommand&);

        // Invoker(std::string);


        void setCommand(const ICommand&);

        // void setCommand(std::string);

        ICommand& getCommand();

};