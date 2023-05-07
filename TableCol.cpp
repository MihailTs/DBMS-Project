#include "TableCol.h"

TableCol::TableCol(){
    setValuesCount(0);
}

TableCol::TableCol(const std::vector<DataType*>& _values){
    setValues(_values);
    setValuesCount(_values.size());
}

void TableCol::setValues(const std::vector<DataType*>& _values){
    values = _values;
    setValuesCount(_values.size());
}

std::vector<DataType*>& TableCol::getValues(){
    return values;
}

unsigned TableCol::getValuesCount(){
    return getValues().size();
}

void TableCol::setValuesCount(unsigned count){
    valuesCount = count;
}

void TableCol::addValue(DataType* _value){
    getValues().push_back(_value);
}
