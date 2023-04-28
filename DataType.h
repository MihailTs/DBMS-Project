#pragma once
#include <iostream>
#include <string>

class DataType{

    private:
        //има ли смисъл?
        std::string stringValue;

    public:


        //Да се добави без да поражда грешки
        //
        //virtual std::string getTypeName()=0;
        //
        //

        std::string getStringValue() const;

        void setStringValue(const std::string&);

};