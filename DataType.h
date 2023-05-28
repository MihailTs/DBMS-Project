#pragma once
#include <iostream>
#include <string>
#include <stdexcept>

class DataType{

    private:
        std::string stringValue;

    public:

        virtual std::string getTypeName()=0;

        std::string getStringValue() const;

        void setStringValue(const std::string&);

        //проверява дали две стойности са равни
        virtual bool equals(const std::string&)=0;
};