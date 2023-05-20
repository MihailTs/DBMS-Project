#include "Double.h"

Double::Double(){
    setValue(0);
}

Double::Double(double _value){
    setValue(_value);
}

Double::Double(const std::string& _strValue){
    if(!isValid(_strValue)) 
        throw std::invalid_argument(_strValue + " is not a valid double number!");
    setValue(std::stod(_strValue));
}

std::string Double::getTypeName(){
    return "double";
}

double Double::getValue() const{
    return value;
}

void Double::setValue(double newVal){
    value = newVal;
    setStringValue(trimRight(std::to_string(newVal)));
}

bool Double::isValid(const std::string& _strValue){
    unsigned size = _strValue.size();
    char firstChar = _strValue[0];

    //случаи като '+', '-', 'm',...
    if(size == 1 && (firstChar < '0' || firstChar > '9')) return false;

    if(firstChar == '0' && size == 1) return true;

    //случаи, в които първият символ е невалиден
    if(firstChar != '-' && firstChar != '+' &&
        (firstChar <= '0' || firstChar > '9')) return false;

    //случаи като '+012',...
    if((firstChar == '-' || firstChar == '+') && (_strValue[1] == '0' || _strValue[1] == '.') && size > 2) 
        return false;

    //ако последният символ е '.' - невалидно
    if(_strValue[size-1] == '.') return false;

    unsigned dotCount = 0;
    //проверка за валидност на символите
    for(int i = 1; i < size; i++){
        if(dotCount >= 2) return false; 
        if(_strValue[i] == '.') {
            continue;
            dotCount++;
        }
        if(_strValue[i] < '0' || _strValue[i] > '9') return false;
    }

    return true;
}

//Оставя нула след запетаята ако числото е цяло
std::string Double::trimRight(const std::string& _strValue){
    std::string trimmed;
    int i;
    for(i = _strValue.size()-1; i > 0 && _strValue.at(i) == '0' && _strValue.at(i-1) != '.'; i--){}

    trimmed = _strValue.substr(0, i+1);
    return trimmed;
}

bool Double::equals(const std::string& _value){
    return std::stod(_value) == getValue();
}