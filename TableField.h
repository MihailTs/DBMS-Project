#pragma once
#include <vector>
#include <fstream>
#include "DataType.h"

class TableField{

    private:

        std::string type;
        std::string name;
        
        std::vector<DataType*> values;
        unsigned valuesCount = 0;

    public:

        TableField(const std::string&, const std::string&);

        std::vector<DataType*>& getValues();

        //На практика връща броят на редовете в таблицата
        unsigned getValuesCount();

        void setValuesCount(unsigned);

        //Добавя нова стойност към колоната
        void addValue(DataType*);

        void setValues(const std::vector<DataType*>&);

        std::string getType() const;

        std::string getName() const;

        void setType(const std::string&);

        void setName(const std::string&);

        ~TableField();

};