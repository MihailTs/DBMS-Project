#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <fstream>
#include "TableManager.h"
#include "Invoker.h"


int main(){
    
    TableManager* tableManager = new TableManager("archive.txt");
    Invoker invoker(tableManager);

    std::cout << "Welcome to MTDB!\n";

    while(true){
        std::cout << "MTDB > ";

        //Приемат се само едноредови команди. Засега.
        std::string command;
        std::getline(std::cin, command);

        if(command == "") {continue;}

        //try{
            invoker.setCommand(command);
            invoker.getCommand()->execute();//}
        // }catch(const std::invalid_argument& ia){
        //     std::cout << "The command you entered is either not a valid command or has a sintax error! Type \"help\" to check the sintax of your command.";
        // }


        std::cout << "\n";
    }


    delete tableManager;
}


