#pragma once
#include <iostream>
#include <string>

class DataType{

    private:
        std::string stringValue;

    public:

        virtual std::string getTypeName()=0;

        std::string getStringValue() const;

        void setStringValue(const std::string&);

};