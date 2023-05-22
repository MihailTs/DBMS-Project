#include "Integer.h"

Integer::Integer(){
    setValue(0);
}

Integer::Integer(int _value){
    setValue(_value);
}

Integer::Integer(const std::string& _strValue){
    //std::stoi няма подходяща проверка за валидност
    if(!isValid(_strValue)) 
        throw std::invalid_argument(_strValue + " is not a valid int number!");
    
    setValue(std::stoi(_strValue));
}

std::string Integer::getTypeName(){
    return "int";
}

int Integer::getValue() const{
    return value;
}

void Integer::setValue(int newVal){
    value = newVal;
    setStringValue(std::to_string(newVal));
}

bool Integer::isValid(const std::string& _strValue){
    unsigned size = _strValue.size();
    char firstChar = _strValue[0];

    //случаи като '+', '-', 'm',...
    if(size == 1 && (firstChar < '0' || firstChar > '9')) return false;

    //Граничен случай, който не е прихванат от останалите условия
    if(firstChar == '0' && size == 1) return true;

    //случаи, в които първият символ е невалиден
    if(firstChar != '-' && firstChar != '+' &&
        (firstChar <= '0' || firstChar > '9')) return false;

    //случаи като '+012',...
    if((firstChar == '-' || firstChar == '+') && _strValue[1] == '0' && size > 2) 
        return false;

    //проверка за валидност на символите
    for(int i = 1; i < size; i++)
        if(_strValue[i] < '0' || _strValue[i] > '9') return false;

    return true;
}

bool Integer::equals(const std::string& _value){
    if(_value == "NULL") return getStringValue() == "NULL";
    return std::stoi(_value) == getValue();
}