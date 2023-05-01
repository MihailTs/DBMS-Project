#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "ICommand.h"

class HelpCommand : public ICommand{

    private:
        const std::string helpFileName = "Help.txt";

        std::string getHelpFileName();

    public:

        void execute();

        void printFile(std::string);

};