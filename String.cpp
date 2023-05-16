#include "String.h"

String::String(){
    setStringValue("");
}

String::String(const std::string& _strValue){
    if(!isValid(_strValue)) throw std::invalid_argument(_strValue + " is not a valid string!");
    //Премахва кавичките
    setStringValue(format(_strValue.substr(1, _strValue.size()-2)));
}

std::string String::getTypeName() {
    return "string";
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

//Премахва '\' използвани за специални символи
std::string String::format(const std::string& str){
    std::string formatted;
    bool dash = false;
    for(int i = 0; i < str.size(); i++){
        if(str.at(i) == '\\' && !dash) {dash = true; continue;}
        else dash = false;

        formatted += str.at(i);
    }
    return formatted;
}

bool String::equals(const std::string& _value){
    return getStringValue() == _value;
}