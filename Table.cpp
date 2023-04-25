#include "Table.h"

//private методи

void Table::setTableName(std::string newName){
    tableName = newName;
}


//Информацията в fieldsNames трябва да е предварително изтрита
void Table::setFieldsNames(std::string* newFieldsNames, unsigned count){ 
    
    if(count != getFieldsCount()) throw "Changing the number of fields is illegal";
    
    fieldsNames = new std::string[getFieldsCount()];

    for(int i = 0; i < getFieldsCount(); i++)
        fieldsNames[i] = newFieldsNames[i];
}


//Да се разреши ли промяна броя на полетата???
// void Table::setFieldsCount(unsigned newFieldsCount){
//     fieldsCount = newFieldsCount;
// }

void Table::setRows(const std::vector<TableRow>& newRows){
    tableRows = newRows;
}



//public методи

Table::Table(std::string _tableName){
    setTableName(_tableName);
}

Table::Table(std::fstream inputFile){
    
}

std::string Table::getTableName() const{
    return tableName;
}

std::string* Table::getFieldsNames() const{
    return fieldsNames;
}

unsigned Table::getFieldsCount() const{
    return fieldsCount;
}

std::vector<TableRow>& Table::getTableRows() {
    return tableRows;
}

std::vector<TableRow> Table::getTableRowsCopy() const{
    return tableRows;
}

unsigned Table::getRowsCount() const{
    return tableRows.size();
}

Table::~Table(){
    delete []getFieldsNames();
}