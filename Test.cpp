#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
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


        invoker.setCommand(command);
        invoker.getCommand()->execute();


        std::cout << "\n";
    }


    delete tableManager;




    // Table t1("table1", "ExampleTable.csv");
    // //Table t2("table2", "ExampleTable.csv");

    // t1.printTable();
    // //t1.describe();

    // std::cout << "\n";


    // // TableManager tm("archive.txt");
    // // tm.openTable(t1.getTableName());
    // // //tm.openTable(t2.getTableName());

    // // tm.showTables();
    
    // _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG); 
    // _CrtDumpMemoryLeaks();
}


