#include "TableRow.h"

TableRow::TableRow(){
    setFieldsCount(0);
}

void TableRow::setFieldsCount(unsigned cnt){
    fieldsCount = cnt;
}

std::vector<DataType*> TableRow::getFieldsValues() const{
    return fieldsValues;
}

unsigned TableRow::getFieldsCount(){
    return fieldsCount;
}

//Добавя нова стойност в края на реда
void TableRow::addFieldValue(DataType* fieldValue){
    getFieldsValues().push_back(fieldValue);
    setFieldsCount(getFieldsCount()+1);
}

// std::ostream& operator<<(std::ostream& file, const TableRow& row){
//     ////
// }

