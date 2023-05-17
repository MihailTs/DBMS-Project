#pragma once
#include <vector>
#include <fstream>
#include "DataType.h"

class TableCol{

    private:

        std::string type;
        std::string name;
        
        std::vector<DataType*> values;
        unsigned valuesCount = 0;

        void setValuesCount(unsigned);

    public:

        TableCol(const std::string&, const std::string&);

        std::vector<DataType*>& getValues();

        //На практика връща броят на редовете в таблицата
        unsigned getValuesCount();

        //Добавя нова стойност към колоната
        void addValue(DataType*);

        void setValues(const std::vector<DataType*>&);

        std::string getType() const;

        std::string getName() const;

        void setType(const std::string&);

        void setName(const std::string&);

        ~TableCol();

};