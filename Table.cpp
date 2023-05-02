#include "Table.h"

Table::Table(const std::string& fileAddres){
    std::ifstream file(fileAddres);
    if(!file.is_open()) throw std::runtime_error("Could not open file");

    std::string line;
    if(file.good()){

        //Задаване на типовете
        std::getline(file, line);
        setFieldsTypes(splitLine(line));

        //Задаване на имената на полетата
        std::getline(file, line);
        setFieldsNames(splitLine(line));

        if(getFieldsNames().size() != getFieldsTypes().size())
            throw "Error! Number of types and field names does not match!";


        //Добавяне на стойностите към колоните

    }

}

void Table::setFieldsNames(const std::vector<std::string>& _newNames){
    fieldsNames = _newNames;
}

void Table::setFieldsTypes(const std::vector<std::string>& _newTypes){
    fieldsTypes = _newTypes;
}

std::vector<std::string>& Table::getFieldsNames(){
    return fieldsNames;
}

unsigned Table::getFieldsCount() const{
    return fieldsCount;
}

const std::vector<std::string>& Table::getFieldsTypes() const{
    return fieldsTypes;
}

unsigned Table::getRowsCount() const{
    return fieldsCount;
}

std::vector<TableCol> &Table::getTableColumns(){
    return columns;
}

std::vector<std::string> Table::splitLine(const std::string& line){
    std::vector<std::string> splLine;
    std::string currentString;

    for(char c : line){
        if(c == ',') {
            splLine.push_back(currentString);
            currentString = "";   
            continue;
        }
        currentString += c;
    }

    splLine.push_back(currentString);
    return splLine;
}