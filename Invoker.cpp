#include "Invoker.h"

Invoker::Invoker(TableMenager* _tableMenager){
    tableMenager = _tableMenager;
    setCommand("exit");
}

Invoker::Invoker(TableMenager* _tableMenager, const std::string& strCommand){
    tableMenager = _tableMenager;
    setCommand(strCommand);
}

void Invoker::setCommand(const std::string& strCommand){
    delete []getCommand();

    //Няма нужда от Factory, защото командите ще се строят по единствен начин тук
    if(strCommand == "exit") command = new ExitCommand;
    else if(strCommand == "help") command = new HelpCommand;
    else if(strCommand.substr(0, 8) == "describe"){
        command = new DescribeCommand(tableMenager, strCommand.substr(9));
    }
    else if(strCommand.substr(0, 5) == "print"){
        command = new PrintTableCommand(tableMenager, strCommand.substr(6));
    }
    else if(strCommand == "showtables"){
        command = new ShowTablesCommand(tableMenager);
    }
    

}

ICommand* Invoker::getCommand(){
    return command;
}

Invoker::~Invoker(){
    delete []getCommand();
}