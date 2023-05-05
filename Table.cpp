#include "Table.h"

Table::Table(const std::string& _tableName, const std::string& fileAddres){

    setTableName(_tableName);

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
    file.close();

}

void Table::setTableName(const std::string& _tableName){
    tableName = _tableName;
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

unsigned Table::getFieldsCount(){
    return fieldsCount;
}

std::vector<std::string>& Table::getFieldsTypes(){
    return fieldsTypes;
}

// unsigned Table::getRowsCount(){
//     return columns.at(0).getValuesCount();
// }

std::string Table::getTableName(){
    return tableName;
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

void Table::describe(){
    for(std::string type : getFieldsTypes())
        std::cout << type << " ";
    std::cout << "\n";
    for(std::string name : getFieldsNames())
        std::cout << name << " ";
    std::cout << "\n";
}

// Table::~Table(){

// }