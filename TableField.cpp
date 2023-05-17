#include "TableField.h"

TableField::TableField(const std::string& _type, const std::string& _name){
    setType(_type);
    setName(_name);
    setValuesCount(0);
}

void TableField::setValues(const std::vector<DataType*>& _values){
    values = _values;
    setValuesCount(_values.size());
}

std::vector<DataType*>& TableField::getValues(){
    return values;
}

unsigned TableField::getValuesCount(){
    return valuesCount;
}

void TableField::setValuesCount(unsigned count){
    valuesCount = count;
}

void TableField::addValue(DataType* _value){
    getValues().push_back(_value);
    valuesCount++;
}

std::string TableField::getType() const{
    return type;
}

std::string TableField::getName() const{
    return name;
}

void TableField::setType(const std::string& _type){
    type = _type;
}

void TableField::setName(const std::string& _name){
    name = _name;
}

TableField::~TableField(){
    for(DataType* dt : getValues())
        delete dt;
}