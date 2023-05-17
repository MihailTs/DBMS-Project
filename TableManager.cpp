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
            getTablesInfo().push_back(t);
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
    for(Touple t : getTablesInfo()){
        if(t.tableName == tableName){
            fileIndex = counter;
            break;
        }
        counter++;
    }
    if(fileIndex == -1)  throw std::runtime_error("No table with such name!");

    //Ако не - я зарежда и я добавя в списъка с отворените
    Table* table = new Table(tableName, getTablesInfo().at(fileIndex).tableAddress);
    openedTables.push_back(table);

}

void TableManager::setArchiveName(const std::string& _archive){
    archive = _archive;
}

std::string TableManager::getArchiveName() const{
    return archive;
}

void TableManager::showTables(){
    
    if(getTablesInfo().empty()) return;

    unsigned longest = 0;
    for(Touple t : getTablesInfo()){
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
    for(Touple t : getTablesInfo()){
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
    getTablesInfo().push_back(t);
}

void TableManager::removeTableInfo(const std::string& _name){
    //Разменя изтриваната с последната
    unsigned i = 0;
    unsigned size = getTablesInfo().size();

    for(Touple t : getTablesInfo()){
        if(t.tableName == _name){
            getTablesInfo().at(i).tableName = getTablesInfo().at(size).tableName;
            getTablesInfo().at(i).tableAddress = getTablesInfo().at(size).tableAddress;
            getTablesInfo().pop_back();
            return;
        }
        i++;
    }
}

void TableManager::renameInArchive(const std::string& oldName, const std::string& newName){
    
    std::ifstream readArchive(getArchiveName());
    if(!readArchive.is_open()) throw std::runtime_error("Could not open file");
    	
    //Записване на старите данни от архива
    std::vector<std::string> contents;
    std::string line;
    if(readArchive.good()){

        std::string line;

        while(std::getline(readArchive, line)){
            contents.push_back(line);
        }
    }

    readArchive.close();

    //Презаписване на останалите данни в архива
    std::ofstream writeArchive(getArchiveName());
    if(!writeArchive.is_open()) throw std::runtime_error("Could not open file");

    if(writeArchive.good()){

        for(std::string fline : contents){
            if(fline.substr(0, fline.find(" ")) == oldName){
                writeArchive << newName << " " << fline.substr(fline.find(" ")+1) << "\n";
            }
            else writeArchive << fline << "\n";
        }
    }
    writeArchive.close();
}

void TableManager::renameTable(const std::string& oldName, const std::string& newName){

    //Преименуване в списъка с файловете
    //и в архива
    //Референция, за да се запази промяната в оригиналния списък
    for(Touple& t : getTablesInfo()){
        if(t.tableName == oldName) {
            t.tableName = newName;
            renameInArchive(oldName, newName);
        }
    }

    //Преименуване в списъка с отворените таблици
    for(Table* table : openedTables){
        if(table->getTableName() == oldName) table->setTableName(newName);
    }

}

Table* TableManager::getTable(const std::string& tableName){
    openTable(tableName);
    for(Table* table: getOpenedTables()){
        if(table->getTableName() == tableName) return table;
    }
    return nullptr;
}

std::vector<TableManager::Touple>& TableManager::getTablesInfo(){
    return tablesInfo;
}

std::vector<Table*>& TableManager::getOpenedTables(){
    return openedTables;
}

//Проверява дали съществува таблица с такова име независимо дали е отворена или не
bool TableManager::contains(const std::string& _tableName){
    for(Touple t : getTablesInfo()){
        if(t.tableName == _tableName) return true;
    }
    return false;
}

void TableManager::saveTable(const std::string& _tableName){
    //Ако таблицата не е отворена, значи по нея не са правени промени,
    //тоест не правим нищо
    bool opened = false;
    for(Table* t : getOpenedTables()){
        if(t->getTableName() == _tableName) opened = true;
    }
    if(!opened) return;


    std::string tableAddres;
    for(Touple t : getTablesInfo()){
        if(t.tableName == _tableName) tableAddres == tableAddres;
    }


}

TableManager::~TableManager(){
    for(Table* t: openedTables)
        delete t;
}