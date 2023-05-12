#include "TableManager.h"
#include <fstream>
#include <algorithm>

TableManager::TableManager(const std::string& _archive){
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

void TableManager::openTable(const std::string& tableName){
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

void TableManager::setArchiveName(const std::string& _archive){
    archive = _archive;
}

std::string TableManager::getArchiveName() const{
    return archive;
}

void TableManager::showTables(){
    
    if(tablesInfo.empty()) return;

    unsigned longest = 0;
    for(Touple t : tablesInfo){
        unsigned len = t.tableName.size();
        if(len > longest) longest = len;
    }

    
    std::string lineSeparator = "+";
    std::string temp(longest, '-');
    lineSeparator += temp + "+";
    
    std::cout << lineSeparator << "\n";

    std::cout << align("Tables", std::max(6, (int)longest)) << "\n";

    std::cout << lineSeparator << "\n";

    int elementIndex = 0;
    for(Touple t : tablesInfo){
        std::cout << align(t.tableName, longest) << "\n";
        elementIndex++;
    }

    std::cout << lineSeparator;
}

std::string TableManager::align(const std::string& str, unsigned longest){
    std::string aligned = "|";
    unsigned spacesToAdd = longest - str.size();
    int i = 0;
    for(; i < spacesToAdd/2; i++)
        aligned += " ";
    
    aligned += str;

    for(; i < spacesToAdd; i++)
        aligned += " ";
    
    return aligned + "|";
}

void TableManager::addTableInfo(const std::string& _name, const std::string& _addres){
    Touple t = {_name, _addres};
    tablesInfo.push_back(t);
}

void TableManager::removeTableInfo(const std::string& _name){
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

Table* TableManager::getTable(const std::string& tableName){
    openTable(tableName);
    for(Table* table: getOpenedTables()){
        if(table->getTableName() == tableName) return table;
    }
    throw "Getting table failed!";
    return nullptr;
}

std::vector<Table*>& TableManager::getOpenedTables(){
    return openedTables;
}

TableManager::~TableManager(){
    for(Table* t: openedTables)
        delete t;
}