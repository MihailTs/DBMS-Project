#pragma once
#include <string>
#include "DataType.h"

class NumericType : public DataType{


    public:

        virtual std::string getStringValue()=0;

        //covariant return type
        virtual double getValue()=0;


};