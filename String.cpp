#include "String.h"

String::String(){
    setStringValue("");
}

String::String(const std::string& _strValue){
    if(!isValid(_strValue)) throw std::invalid_argument(_strValue + " is not a valid string!");
    //Премахва кавичките
    setStringValue(_strValue.substr(1, _strValue.size()-2));
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

bool String::isValid(const std::string& str){
    unsigned length = str.size();
    //Проверка дали стрингът е ограден в кавички
    if(str.at(0) != '\"' || str.at(length-1) != '\"') return false;

    //Проверка за валидност на останалата част
    for(int i = 1; i < length-1; i++){
        if(str.at(i) == '\\'){
            if((str.at(i+1) != '\\' && str.at(i+1) != '\"') || i == length-2) return false;
            i++;
        } 
        else if(str.at(i) == '\"'){
            return false;
        }
    }
    return true;
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

