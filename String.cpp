#include "String.h"

String::String(){
    setStringValue("");
}

String::String(const std::string& str){
    setStringValue(str);
}

std::string String::getTypeName() const{
    return "string";
}





std::ostream& operator<<(std::ostream& out, const String& str){
    out << str.getStringValue();
}