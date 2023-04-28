#include "Integer.h"

Integer::Integer(){
    setValue(0);
}

Integer::Integer(int _value){
    setValue(_value);
}

Integer::Integer(const std::string& _strValue){
    setValue(stringToInt(_strValue));
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

std::ostream& operator<<(std::ostream& out, const Integer& number){
    out << number.getValue();
    return out;
}

std::fstream& operator<<(std::fstream& out, const Integer& number){
    out << number.getStringValue().c_str();
    return out;
}

Integer& Integer::operator=(const Integer& other){
    setValue(other.getValue());
    return *this;
}

bool Integer::isValid(const std::string& _strValue){
    unsigned size = _strValue.size();
    char firstChar = _strValue[0];

    //случаи като '+', '-', 'm',...
    if(size == 1 && (firstChar < '0' || firstChar > '9')) return false;

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

int Integer::myPower(int number, int power){
    int product = 1;
    for(int i = 1; i <= power; i++)
        product *= number;
    return product;
}

int Integer::stringToInt(const std::string& _strValue){
    
    if(!isValid(_strValue)) 
        throw std::invalid_argument(_strValue + " is not a valid int number!");
    
    int numValue = 0;
    
    int power = 0;
    for(int i = _strValue.size()-1; i > 0; i--)
        numValue += (_strValue[i]-'0') * myPower(10, power++);

    if(_strValue[0] == '+') return numValue;
    if(_strValue[0] == '-') return -1*numValue;
    numValue += (_strValue[0]-'0') * myPower(10, power++);

    return numValue;
}