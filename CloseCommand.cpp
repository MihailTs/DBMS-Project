#include "CloseCommand.h"

CloseCommand::CloseCommand(TableManager* _tableManager, const std::string& _tableName){
    tableManager = _tableManager;
    tableName = _tableName;
}

void CloseCommand::execute(){

    if(!tableManager->contains(tableName)) throw std::invalid_argument("No table with such name!");
    if(!tableManager->isOpened(tableName)) {
        std::cout << "Table closed successfully" << "\n";
        return;
    }

    std::cout << "Do you want to save unsaved changes made to " << tableName << "?\n";
    std::string answer;
    do{
        std::cout << "Type \"yes\" or \"no\" : ";
        std::cin >> answer;
        answer = toLower(answer);
    }while(answer != "yes" && answer != "y" && answer != "no" && answer != "n");

    answer = toLower(answer);
    if(answer == "yes" || answer == "y") {
        tableManager->saveTable(tableName); 
        std::cout << "Changes saved successfully\n";
    }


    tableManager->closeTable(tableName);
    std::cout << "Table closed successfully" << "\n";
}

std::string CloseCommand::toLower(const std::string& str){
    std::string low = "";
    for(int i = 0; i < str.length(); i++){
        low += (str.at(i) >= 'A' && str.at(i) <= 'Z')? str.at(i)+('a' - 'A'): str.at(i);  
    }

    return low;
}