#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Table.h"
#include "TableMenager.h"

int main(){
    
    Table t1("table1", "ExampleTable.csv");
    Table t2("table2", "ExampleTable.csv");

    //t.printTable();


    TableMenager tm("archive.txt");
    tm.openTable(t1.getTableName());
    tm.openTable(t2.getTableName());

    tm.showTables();


    
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG); 
    _CrtDumpMemoryLeaks();
}


