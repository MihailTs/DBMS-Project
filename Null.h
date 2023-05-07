#pragma once
#include "DataType.h"

class Null : public DataType{

    private:
        std::string typeName;

        void setTypeName(const std::string&);

    public:

        //Конструктор по тип
        Null(const std::string&);

        std::string getTypeName();

        //Null& operator=(DataType*);

};