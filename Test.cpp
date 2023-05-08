#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <string>
#include <vector>
#include "Table.h"

// std::string align(const std::string& str, unsigned cnt){
//     std::string aligned;
//     unsigned spacesToAdd = str.size() - cnt;
//     int i = 0;
//     for(int i = 0; i < spacesToAdd/2; i++)
//         aligned += " ";
    
//     aligned += str;

//     for(; i < spacesToAdd; i++)
//         aligned += " ";
    
//     return aligned;
// }


int main(){
    Table t("table", "ExampleTable.csv");

    t.printTable();

     _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG); 
    _CrtDumpMemoryLeaks();
}


