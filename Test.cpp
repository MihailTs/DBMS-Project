#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <string>
#include <vector>
#include "Table.h"

bool isValid(std::string str){
    unsigned length = str.size();
    //Проверка дали стрингът е ограден в кавички
    if(str.at(0) != '\"' || str.at(length-1) != '\"') return false;

    //Проверка за валидност на останалата част
    for(int i = 1; i < length-1; i++){
        if(str.at(i) == '\\'){
            if((str.at(i+1) != '\\' && str.at(i+1) != '\"') || i == length-2) return false;
            i++;
        } 
        else if(str.at(i) == '\"'){
            return false;
        }
    }
    return true;
}

int main(){
    Table t("table", "ExampleTable.csv");

    t.printTable();
    
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG); 
    _CrtDumpMemoryLeaks();
}


