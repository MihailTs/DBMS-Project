#pragma once
#include <string>
//#include <iostream>
#include <fstream>
#include "DataType.h"

class String : public DataType{

    private:

        bool isValid(const std::string&);

        std::string format(const std::string&);

    public:

        String();

        String(const std::string&);

        std::string getTypeName();

        String& operator=(const String&);

        String& operator=(const char*);

        friend std::ostream& operator<<(std::ostream&, const String&);

        friend std::fstream& operator<<(std::fstream&, const String&);
};