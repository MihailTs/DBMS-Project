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

    //Намира адреса на тблицата в архива
    //Ако не съществува такава таблица - грешка




    //Table t = new Table(tableName, );


    //Ако не - я зарежда и я добавя в списъка с отворените

}

void TableMenager::setArchiveName(const std::string& _archive){
    archive = _archive;
}

void TableMenager::addTableInfo(const std::string& _name, const std::string& _addres){
    Touple t = {_name, _addres};
    tablesInfo.push_back(t);
}

void TableMenager::removeTableInfo(const std::string& _name){
    //Разменя изтриваната с последната
    unsigned i = 0;
    unsigned size = tablesInfo.size();

    for(Touple t : tablesInfo){
        if(t.tableName == _name){
            tablesInfo.at(i).tableName = tablesInfo.at(size).tableName;
            tablesInfo.at(i).tableAddres = tablesInfo.at(size).tableAddres;
            tablesInfo.pop_back();
            return;
        }
        i++;
    }
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