#include "String.h"

String::String(){
    setStringValue("");
}

String::String(const std::string& str){
    setStringValue(str);
}

std::string String::getTypeName() {
    return "string";
}

String& String::operator=(const String& str){
    setStringValue(str.getStringValue());
    return *this;
}

String& String::operator=(const char* str){
    setStringValue(str);
    return *this;
}


std::fstream& operator<<(std::fstream& out, const String& str){
    //.c_str() е защото операторът << на fstream 
    //не приема std::string аргументи
    out << str.getStringValue().c_str();
    return out;
}


std::ostream& operator<<(std::ostream& out, const String& str){
    out << str.getStringValue();
    return out;
}

