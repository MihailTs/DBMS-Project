#pragma once
#include <string>
#include "NumericType.h"

class Integer : public NumericType{

    private:
        int value;

    public:

        std::string getTypeName();

        int getValue();

};