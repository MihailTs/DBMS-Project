#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "DataType.h"
#include "Double.h"
#include "String.h"
#include "Integer.h"
#include "Table.h"

int main(){

    Table t("table", "TableTemplate.csv");
    
    t.describe();

    return 0;
}


