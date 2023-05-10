#pragma once
#include "TableMenager.h"
#include "Table.h"

class ICommand{

    public:

        virtual void execute() = 0;

        virtual ~ICommand() = default;

};