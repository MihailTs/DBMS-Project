#pragma once
#include "ICommand.h"
#include <string>

class RenameCommand : public ICommand{

    public:
        TableManager* tableManager;
        std::string oldName;
        std::string newName;

    public:
        RenameCommand(TableManager*, const std::string&, const std::string&);

        void execute();

};