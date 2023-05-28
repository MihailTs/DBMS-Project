#pragma once
#include "TableManager.h"
#include "Table.h"

class ICommand{

    public:
        //метод за изпълнение на командата
        virtual void execute() = 0;

        virtual ~ICommand() = default;

};