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

        try{
            invoker.setCommand(command);
            invoker.getCommand()->execute();
        }catch(std::exception& e){
            std::cout << e.what() << " Check the manual for the right syntax for your command.\n";
        }


        std::cout << "\n";
    }

    delete tableManager;
}


