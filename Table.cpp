#define underline "\033[4m"
#define nounderline "\033[24m"
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

        //Проверка дали броят на подадените имена е различен от броя на типовете
        unsigned tempFieldsCount = getFieldsNames().size();
        if(tempFieldsCount != getFieldsTypes().size())
            throw "Error! Number of types and field names does not match!";

        setFieldsCount(tempFieldsCount);

        //Добавяне на колоните и добавяне на дължините на имената на колоните
        for(int i = 0; i < tempFieldsCount; i++){
            TableCol* tC = new TableCol;
            columns.push_back(tC);
            columnLongest.push_back(getFieldsNames().at(i).size());
        }

        //Добавяне на стойностите към колоните
        while(std::getline(file, line)){
            std::vector<std::string> rowValues = splitLine(line);
            int col = 0;
            DataType* value;

            for(std::string str : rowValues){
                
                std::string colType = getFieldsTypes()[col];

                if(str == "") value = new Null(colType);
                else if(colType == "int")
                    value = new Integer(str);
                else if(colType == "double")
                    value = new Double(str);
                else if(colType == "string")
                    value = new String(str);
                

                columns[col]->addValue(value);
                
                //Проверка дали дължината на стойността в колоната е най-голямата досега
                //това е с цел принтиране на таблицата по по-естетичен начин
                int length = value->getStringValue().size();
                if(length > columnLongest.at(col)) columnLongest.at(col) = length;

                /////////////////
                //getTableColumns()=.at(col).addValue(value);
                /////////////////
                
                col++;
            }   
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
    for(std::string type : getFieldsTypes())
        std::cout << type << " ";
    std::cout << "\n";
    for(std::string name : getFieldsNames())
        std::cout << name << " ";
    std::cout << "\n";
}

void Table::printTable(){
    int i = 0;
    for(std::string name : getFieldsNames()){
        std::cout << underline << align(name, i) << nounderline;
        i++;
    }

    std::cout << "\n";
    for(i = 0; i < getRowsCount(); i++){
        for(int j = 0; j < getFieldsCount(); j++){
            std::cout << align(getTableColumns().at(j)->getValues().at(i)->getStringValue(), j);
        }
        std::cout << "\n";
    }
}

std::string Table::align(const std::string& str, unsigned colNumber){
    std::string aligned = "|";
    unsigned spacesToAdd = columnLongest.at(colNumber) - str.size();
    int i = 0;
    for(; i < spacesToAdd/2; i++)
        aligned += " ";
    
    aligned += str;

    for(; i < spacesToAdd; i++)
        aligned += " ";
    
    return aligned + "|";
}

Table::~Table(){
    for(TableCol* col : getTableColumns()){
        for(DataType* t : col->getValues()){
            delete t;
        }
        delete col;
    }
}   