#include "Invoker.h"

Invoker::Invoker(){
    setCommand("exit");
}

Invoker::Invoker(const std::string& strCommand){
    setCommand(strCommand);
}

void Invoker::setCommand(const std::string& strCommand){
    delete []getCommand();

    //Няма нужда от Factory, защото командите ще се строят по единствен начин тук
    if(strCommand == "exit") coommand = new ExitCommand;
    else if(strCommand == "help") coommand = new HelpCommand;
    else if(strCommand.substr(0, 8) == "describe"){
        //Вика метода describe(име на таблицата) на tableMenager
        coommand = new DescribeCommand(tableMenager, strCommand.substr(9));
    }
    else if(strCommand == "showTables"){
        //Вика метода showTables на tableMenager
        coommand = new ShowTablesCommand(tableMenager);
    }
    else if(strCommand.substr(0, 5) == "print"){
        //Вика метода print(име на таблицата) на tableMenager
        coommand = new PrintCommand(tableMenager, getTable(strCommand.substr(6)));
    }
    


}

ICommand* Invoker::getCommand(){
    return command;
}

Invoker::~Invoker(){
    delete []getCommand();
}