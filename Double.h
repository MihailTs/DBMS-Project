#pragma once
#include <string>
#include "DataType.h"

class Double : public DataType{

    private:
        double value;

        bool isValid(const std::string&);

    public:

        Double();

        Double(double);

        Double(const std::string&);

        std::string getTypeName();

        double getValue() const;

        void setValue(double);

        Double& operator=(const Double&);

        friend std::ostream& operator<<(std::ostream&, const Double&);

        friend std::fstream& operator<<(std::fstream&, const Double&);

};