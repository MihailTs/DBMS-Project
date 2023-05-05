#include "TableMenager.h"

TableMenager::TableMenager(const std::string& _archive){
    setArchiveName(_archive);
}

void TableMenager::openTable(const std::string& tableName){
    //Проверява дали таблицата вече е отворена
    //Ако е - return
    //Ако не е зарежда таблицата и я добавя в списъка с отворените
}

void TableMenager::setArchiveName(const std::string& _archive){
    archive = _archive;
}

Table* TableMenager::getTable(const std::string& tableName){
    openTable(tableName);
    for(Table* table: openedTables){
        if(table->getTableName() == tableName) return table;
    }
    throw "Getting table failed!";
    return nullptr;
}

TableMenager::~TableMenager(){
    for(Table* t: openedTables)
        delete t;
}