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

        unsigned tempFieldsCount = getFieldsNames().size();
        if(tempFieldsCount != getFieldsTypes().size())
            throw "Error! Number of types and field names does not match!";

        setFieldsCount(tempFieldsCount);

        for(int i = 0; i < tempFieldsCount; i++){
            TableCol* tC = new TableCol;
            columns.push_back(tC);
        }
            

        //Добавяне на стойностите към колоните
        while(std::getline(file, line)){
            std::vector<std::string> rowValues = splitLine(line);
            int col = 0;
            DataType* value;
            for(std::string str : rowValues){
                
                if(getFieldsTypes()[col] == "int")
                    value = new Integer(str);
                else if(getFieldsTypes()[col] == "double")
                    value = new Double(str);
                else if(getFieldsTypes()[col] == "string")
                    value = new String(str);
                // else if(getFieldsTypes().at(col) == "")
                //     value = new Null;

                columns[col]->addValue(value);
                /////////////////
                //getTableColumns()=.at(col).addValue(value);
                /////////////////
                
                col++;
            }   
            std::cout << "\n";
        }
    }
    //std::cout << (columns[0]->getValues().at(0))->getStringValue();
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
    return columns[0]->getValuesCount();
}

std::string Table::getTableName(){
    return tableName;
}

std::vector<TableCol*>& Table::getTableColumns(){
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

void Table::printTable(){
    for(std::string name : getFieldsNames())
        std::cout << name << " ";

    std::cout << "\n________________________________________\n";
    for(int i = 0; i < getRowsCount(); i++){
        for(int j = 0; j < getFieldsCount(); j++){
            std::cout << getTableColumns().at(j)->getValues().at(i)->getStringValue() << " ";
        }
        std::cout << "\n";
    }
}

Table::~Table(){
    for(TableCol* col : getTableColumns()){
        for(DataType* t : col->getValues()){
            delete t;
        }
    }
}   