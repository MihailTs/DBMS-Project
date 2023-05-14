#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Table.h"
#include "TableManager.h"

std::vector<std::string> splitLine(const std::string& line){
    bool quotes = false;
    std::vector<std::string> splLine;
    std::string currentString = "";

    for(char c : line){
        if(c == '\"') quotes = !quotes;
        if(c == ',' && !quotes) {
            splLine.push_back(currentString);
            currentString = "";   
            continue;
        }
        currentString += c;
    }

    splLine.push_back(currentString);
    return splLine;
}

std::string trim(const std::string& str){

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

int main(){
    
    Table t1("table1", "ExampleTable.csv");
    //Table t2("table2", "ExampleTable.csv");

    t1.printTable();
    //t1.describe();

    std::cout << "\n";


    // TableManager tm("archive.txt");
    // tm.openTable(t1.getTableName());
    // //tm.openTable(t2.getTableName());

    // tm.showTables();
    
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG); 
    _CrtDumpMemoryLeaks();
}


