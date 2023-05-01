#include "HelpCommand.h"

std::string HelpCommand::getHelpFileName(){
    return helpFileName;
}

void HelpCommand::execute(){
    printFile(getHelpFileName());
}

void HelpCommand::printFile(std::string fileName){

    std::ifstream file(fileName);
    char fileRow[1024];

    while(file.getline(fileRow, 1024)){
        std::cout << fileRow << "\n";
    }

    file.close();
}