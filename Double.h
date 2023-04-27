#pragma once
#include <string>
#include "NumericType.h"

class Double : public NumericType{

    private:
        double value;

    public:

        std::string getTypeName();

        double getValue();

};