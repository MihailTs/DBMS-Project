#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>
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

        friend std::ostream& operator<<(std::ostream&, const Integer&);

        friend std::fstream& operator<<(std::fstream&, const Integer&);
};