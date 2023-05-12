#pragma once
#include <vector>
#include <fstream>
#include "DataType.h"

class TableCol{

    private:

        ///////
        //ДА СЕ ДОБАВИ И ТИП НА КОЛОНАТА!!!
        ///////
        
        
        std::vector<DataType*> values;
        unsigned valuesCount;

        void setValuesCount(unsigned);

    public:

        TableCol();

        TableCol(const std::vector<DataType*>&);

        std::vector<DataType*>& getValues();

        //На практика връща броят на редовете в таблицата
        unsigned getValuesCount();

        //Добавя нова стойност към колоната
        void addValue(DataType*);

        void setValues(const std::vector<DataType*>&);

};