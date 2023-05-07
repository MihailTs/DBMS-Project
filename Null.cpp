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

// Null& operator=(DataType* other){
//     if(getTypeName() != other->getTypeName())
//         throw "Illegal use of operator '='";
// }