#pragma once
#include <fstream>
#include <iostream>
#include "DataType.h"

class Integer : public DataType{

    private:
        int value;

        bool isValid(const std::string&);

    public:

        Integer();

        Integer(int);

        Integer(const std::string&);

        std::string getTypeName();

        int getValue() const;

        void setValue(int);

        Integer& operator=(const Integer&);

        bool equals(const std::string&);

};