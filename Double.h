#pragma once
#include "DataType.h"

class Double : public DataType{

    private:
        double value;

        bool isValid(const std::string&);

        std::string trimRight(const std::string&);

    public:

        Double();

        Double(double);

        Double(const std::string&);

        std::string getTypeName();

        double getValue() const;

        void setValue(double);

        bool equals(const std::string&);
};