#include "Table.h"

Table::Table(const std::string& _tableName, const std::string& fileAddres){

    setTableName(_tableName);

    //отвряне на файла
    std::ifstream file(fileAddres);
    if(!file.is_open()) throw std::runtime_error("Could not open file!");

    std::string line;
    if(file.good()){
        
        //Задаване на типовете
        std::getline(file, line);
        setFieldsTypes(splitLine(line));

        //Задаване на имената на полетата
        std::getline(file, line);
        setFieldsNames(splitLine(line));        

        //Проверка дали броят на подадените имена е различен от броя на типовете
        unsigned tempFieldsCount = getFieldsNames().size();
        if(tempFieldsCount != getFieldsTypes().size())
            throw "Error! Number of types and field names does not match!";

        setFieldsCount(tempFieldsCount);

        //Добавяне на колоните и добавяне на дължините на имената на колоните
        for(int i = 0; i < tempFieldsCount; i++){
            TableCol* tC = new TableCol;
            getTableColumns().push_back(tC);
            columnLongest.push_back(getFieldsNames().at(i).size());
        }

        //Добавяне на стойностите към колоните
        while(std::getline(file, line)){
            std::vector<std::string> rowValues = splitLine(line);
            insertRecord(rowValues);    
        }   
    }

    file.close();
}

void Table::setTableName(const std::string& _tableName){
    tableName = _tableName;
}

void Table::setFieldsCount(unsigned _fieldsCount){
    fieldsCount = _fieldsCount;
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

unsigned Table::getRowsCount(){
    return getTableColumns().at(0)->getValuesCount();
}

std::string Table::getTableName(){
    return tableName;
}

std::vector<TableCol*>& Table::getTableColumns(){
    return columns;
}

std::vector<std::string> Table::splitLine(const std::string& line){
    bool quotes = false;
    std::vector<std::string> splLine;
    std::string currentString = "";

    for(char c : line){
        if(c == '\"') quotes = !quotes;
        if(c == ',' && !quotes) {
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

    if(getFieldsCount() == 0) return;

    //Подобно на printTable()

    //В началото на редовете се добавят "Field" и "Type"

    std::string lineSeparator = "+-------";

    for(int i = 0; i < getFieldsCount(); i++){
        lineSeparator += "+";
        int len = std::max(getFieldsNames().at(i).size(), getFieldsTypes().at(i).size());
        std::string temp(len+2, '-');
        lineSeparator += temp;
    }
    lineSeparator += "+";

    std::cout << lineSeparator << "\n";
    
    std::cout << "| Type  ";

    int colNumber = 0;
    for(std::string type : getFieldsTypes()){
        std::cout << align(type, std::max(type.size(), getFieldsNames().at(colNumber).size()));
        colNumber++;
    }

    std::cout << "|\n" << lineSeparator << "\n";
    
    std::cout << "| Field ";

    colNumber = 0;
    for(std::string name : getFieldsNames()){
        std::cout << align(name, std::max(getFieldsTypes().at(colNumber).size(), name.size()));
        colNumber++;
    }
    
    std::cout << "|\n" << lineSeparator;
}

void Table::printTable(){

    //Първо се изгражда разделителя за редове
    //Извеждат се имената на полетата, а после и един по един - редовете
    //В края на всеки ред се добавя |

    std::string lineSeparator;
    for(int len : columnLongest){
        lineSeparator += "+";
        std::string temp(len+2, '-');
        lineSeparator += temp;
    }
    lineSeparator += "+";

    std::cout << lineSeparator << "\n";

    int i = 0;
    for(std::string name : getFieldsNames()){
        std::cout << align(name, columnLongest.at(i));
        i++;
    }
    if(i != 0) std::cout << "|";
    else return;

    std::cout << "\n" << lineSeparator << "\n";


    for(int j = 0; j < getRowsCount(); j++){
        for(int k = 0; k < getFieldsCount(); k++){
            std::cout << align(getTableColumns().at(k)->getValues().at(j)->getStringValue(), columnLongest.at(k));
        }
        std::cout << "|\n";
    }

    std::cout << lineSeparator;
}

std::string Table::align(const std::string& str, unsigned maxLength){
    std::string aligned = "| ";
    unsigned spacesToAdd = maxLength - str.size();
    int i = 0;
    for(; i < spacesToAdd/2; i++)
        aligned += " ";
    
    aligned += str;

    for(; i < spacesToAdd; i++)
        aligned += " ";
    
    return aligned + " ";
}

void Table::insertRecord(const std::vector<std::string>& values){
    if(values.size() < getFieldsCount()) throw std::invalid_argument("Invalid number of arguments!");

    //ТОЗИ МЕТОД ДА НЕ СЕ ПРОМЕНЯ!!!
    int i = 0;
    for(std::string value : values){
        DataType* temp = factory(value, getFieldsTypes().at(i));
        getTableColumns().at(i)->addValue(temp); 
        //ТУК Е ВАЖНО ДА Е ТОЧНО temp->getStringValue().size(), а не value.size()!       
        if(temp->getStringValue().size() > columnLongest.at(i)) columnLongest.at(i) = temp->getStringValue().size();
        i++;
    }
}

DataType* Table::factory(const std::string& value, const std::string& type){
    DataType* product;
    
    if(value == "") product = new Null(type);
    else if(type == "int")
        product = new Integer(value);
    else if(type == "double")
        product = new Double(value);
    else if(type == "string")
        product = new String(value);
    else throw std::invalid_argument(type + " is not a data valid type!");
    
    return product;
}

void Table::addField(const std::string& _name, const std::string& _type){
    getFieldsNames().push_back(_name);
    getFieldsTypes().push_back(_type);
    columnLongest.push_back(_name.size());
    TableCol* newColumn = new TableCol;


    DataType* value;
    for(int i = 0; i < getRowsCount(); i++){
        value = factory("", _type);
        newColumn->addValue(value);
        if(value->getStringValue().size() > columnLongest.at(getFieldsCount()-1)) columnLongest.at(getFieldsCount()-1) = value->getStringValue().size();
    }


    getTableColumns().push_back(newColumn);
    fieldsCount++;
}

Table::~Table(){
    for(TableCol* col : getTableColumns()){
        for(DataType* t : col->getValues()){
            delete t;
        }
        delete col;
    }
}   