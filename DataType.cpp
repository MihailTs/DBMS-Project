#include "DataType.h"

std::string DataType::getStringValue() const{
    return stringValue;
}

void DataType::setStringValue(const std::string& str){
    stringValue = str;
}
