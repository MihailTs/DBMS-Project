#include "Null.h"

Null::Null(const std::string& _typeName){
    setStringValue("NULL");
    setTypeName(_typeName);
}

void Null::setTypeName(const std::string& _typeName){
    typeName = _typeName;
}

std::string Null::getTypeName(){
    return "null";
}

bool Null::equals(const std::string& _value){
    return _value == "" || _value == "NULL";
}