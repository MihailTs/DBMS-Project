#include <iostream>
#include <string>
#include <fstream>
#include "DataType.h"
#include "Double.h"
#include "String.h"
#include "Integer.h"

int main(){

    std::ifstream file("Help.txt");
    char fileRow[1024];

    while(file.getline(fileRow, 1024)){
        std::cout << fileRow << "\n";
    }

    file.close();

    return 0;
}