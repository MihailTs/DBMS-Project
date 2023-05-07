#include "TableMenager.h"

TableMenager::TableMenager(const std::string& _archive){
    setArchiveName(_archive);
}

void TableMenager::openTable(const std::string& tableName){
    //Проверява дали таблицата вече е отворена
    //Ако е - return
    for(Table* table : getOpenedTables()){
        if(table->getTableName() == tableName) return;
    }


    //Ако не - я зарежда и я добавя в списъка с отворените

}

void TableMenager::setArchiveName(const std::string& _archive){
    archive = _archive;
}

Table* TableMenager::getTable(const std::string& tableName){
    openTable(tableName);
    for(Table* table: getOpenedTables()){
        if(table->getTableName() == tableName) return table;
    }
    throw "Getting table failed!";
    return nullptr;
}

std::vector<Table*>& TableMenager::getOpenedTables(){
    return openedTables;
}

TableMenager::~TableMenager(){
    for(Table* t: openedTables)
        delete t;
}