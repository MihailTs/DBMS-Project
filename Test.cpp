#include <iostream>
#include <string>
#include "DataType.h"
#include "String.h"
#include "Integer.h"
#include "Double.h"


int main(){

    std::string t;
    std::cin >> t;
    Double d(t);

    std::cout << d;


    return 0;
}