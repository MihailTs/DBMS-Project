#include "ExitCommand.h"

ExitCommand::ExitCommand(TableManager* _tableManager){
    tableManager = _tableManager;
}

void ExitCommand::execute(){
    for(Table* t : tableManager->getOpenedTables()){
        if(t->isModified()) askToSave(t->getTableName());
    }
    delete tableManager;
    std::cout << "Goodbye!\n";
    exit(0);
}

void ExitCommand::askToSave(const std::string& _tableName){
    std::cout << "Do you want to save unsaved changes made to " << _tableName << "?\n";
    std::string answer;
    do{
        std::cout << "Type \"yes\" or \"no\" : ";
        std::cin >> answer;
        answer = toLower(answer);
    }while(answer != "yes" && answer != "y" && answer != "no" && answer != "n");

    answer = toLower(answer);
    if(answer == "yes" || answer == "y") {
        tableManager->saveTable(_tableName); 
        std::cout << "Changes saved successfully\n";
    }
}

std::string ExitCommand::toLower(const std::string& str){
    std::string low = "";
    for(int i = 0; i < str.length(); i++){
        low += (str.at(i) >= 'A' && str.at(i) <= 'Z')? str.at(i)+('a' - 'A'): str.at(i);  
    }

    return low;
}