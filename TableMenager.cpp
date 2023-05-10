#include "TableMenager.h"
#include <fstream>

TableMenager::TableMenager(const std::string& _archive){
    setArchiveName(_archive);
    
    //зареждане на информацията от архива
    std::ifstream readArchive(getArchiveName());
    if(!readArchive.is_open()) throw std::runtime_error("Could not open file");

    std::string line;
    if(readArchive.good()){
        //Потенциална възможност за грашка при неправилно въведени данни в архива
        while(std::getline(readArchive, line)){
            if(line == "") continue;
            unsigned spacePosition = line.find(" ");
            std::string fileName = line.substr(0, spacePosition);
            std::string fileAddress = line.substr(spacePosition+1);
            Touple t = {fileName, fileAddress};
            tablesInfo.push_back(t);
        }
    }

    readArchive.close();
}

void TableMenager::openTable(const std::string& tableName){
    //Проверява дали таблицата вече е отворена
    //Ако е - return
    for(Table* table : getOpenedTables()){
        if(table->getTableName() == tableName) return;
    }

    //Намира адреса на тблицата в архива
    //Ако не съществува такава таблица - грешка
    int fileIndex = -1;
    unsigned counter = 0;
    for(Touple t : tablesInfo){
        if(t.tableName == tableName){
            fileIndex = counter;
            break;
        }
        counter++;
    }
    if(fileIndex == -1)  throw std::runtime_error("No table with such name!");

    //Ако не - я зарежда и я добавя в списъка с отворените
    Table* table = new Table(tableName, tablesInfo.at(fileIndex).tableAddress);
    openedTables.push_back(table);

}

void TableMenager::setArchiveName(const std::string& _archive){
    archive = _archive;
}

std::string TableMenager::getArchiveName() const{
    return archive;
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
            tablesInfo.at(i).tableAddress = tablesInfo.at(size).tableAddress;
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