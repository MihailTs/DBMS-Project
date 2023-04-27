#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "DataType.h"

class String : public DataType{

    public:

        String();

        String(const std::string&);

        std::string getTypeName();

        friend std::ostream& operator<<(std::ostream&, const String&);

        
};