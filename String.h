#pragma once
#include <string>
#include "DataType.h"

class String : public DataType{

    private:

        bool isValid(const std::string&);

        std::string format(const std::string&);

    public:

        String();

        String(const std::string&);

        std::string getTypeName();

        bool equals(const std::string&);

};