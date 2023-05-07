#include <iostream>
#include <string>
#include <vector>
#include "Table.h"

int main(){

    Table t("table", "ExampleTable.csv");
    
    //std::cout << t.getRowsCount();

    t.printTable();

    return 0;
}


