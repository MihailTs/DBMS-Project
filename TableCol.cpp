#include "TableCol.h"

TableCol::TableCol(const std::string& _type, const std::string& _name){
    setType(_type);
    setName(_name);
    setValuesCount(0);
}

void TableCol::setValues(const std::vector<DataType*>& _values){
    values = _values;
    setValuesCount(_values.size());
}

std::vector<DataType*>& TableCol::getValues(){
    return values;
}

unsigned TableCol::getValuesCount(){
    return valuesCount;
}

void TableCol::setValuesCount(unsigned count){
    valuesCount = count;
}

void TableCol::addValue(DataType* _value){
    getValues().push_back(_value);
    valuesCount++;
}

std::string TableCol::getType() const{
    return type;
}

std::string TableCol::getName() const{
    return name;
}

void TableCol::setType(const std::string& _type){
    type = _type;
}

void TableCol::setName(const std::string& _name){
    name = _name;
}

TableCol::~TableCol(){
    for(DataType* dt : getValues())
        delete dt;
}