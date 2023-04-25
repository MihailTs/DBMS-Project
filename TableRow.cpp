#include "TableRow.h"


TableRow::TableRow(){
    fieldsCount = 0;
}

void TableRow::setFieldsCount(unsigned cnt){
    fieldsCount = cnt;
}

std::vector<DataType> TableRow::getFieldsValues() const{
    return fieldsValues;
}

unsigned TableRow::getFieldsCount(){
    return fieldsCount;
}

//adds another value to the end of the row
void TableRow::addFieldValue(const DataType& fieldValue){
    getFieldsValues().push_back(fieldValue);
    setFieldsCount(getFieldsCount()+1);
}

std::ostream& operator<<(std::ostream& file, const TableRow& row){
    ////
}

