#pragma once
#include <vector>
#include <string>
#include "ICommand.h"
#include "Table.h"

class DescribeCommand{

    private:
        Table* table;

    public:
        DescribeCommand(Table*);

        void execute();

};