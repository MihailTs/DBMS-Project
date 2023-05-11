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

    //strCommand = stripSpaces(strCommand);

    //Няма нужда от Factory, защото командите ще се строят по единствен начин тук
    if(toLower(strCommand) == "exit") command = new ExitCommand;
    else if(toLower(strCommand) == "help") command = new HelpCommand;
    else if(toLower(strCommand.substr(0, 8)) == "describe"){
        command = new DescribeCommand(tableMenager, strCommand.substr(9));
    }
    else if(toLower(strCommand.substr(0, 5)) == "print"){
        command = new PrintTableCommand(tableMenager, strCommand.substr(6));
    }
    else if(toLower(strCommand) == "showtables"){
        command = new ShowTablesCommand(tableMenager);
    }
    //else if(toLower(strCommand.substr) == "insert into")



}

ICommand* Invoker::getCommand(){
    return command;
}

Invoker::~Invoker(){
    delete []getCommand();
}

std::string Invoker::trim(const std::string& str){

    std::string trim = "";
    unsigned leftSpaces = 0;
    unsigned rightSpaces = 0;
    
    int i = 0;
    while(i < str.size() && (str.at(i) == ' ' || str.at(i) == '\t')) i++;
    leftSpaces = i;

    i = str.size()-1;
    while(i >= 0 && (str.at(i) == ' ' || str.at(i) == '\t')) i--;
    rightSpaces = i;

    if(leftSpaces > rightSpaces) return trim;

    trim = str.substr(leftSpaces, rightSpaces-leftSpaces+1);
    return trim;
}

std::string Invoker::toLower(const std::string& str){
    std::string lowerStr = "";

    for(int i = 0; i < str.size(); i++){
        if(str.at(i) >= 'A' && str.at(i) <= 'Z') lowerStr += str.at(i) - ('A' - 'a');
        else lowerStr += str.at(i);
    }
    return lowerStr;
}