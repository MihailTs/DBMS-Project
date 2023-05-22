#include "TableManager.h"
#include <fstream>
#include <algorithm>

TableManager::TableManager(const std::string& _archive){

    setArchiveName(_archive);
    
    //зареждане на информацията от архива
    std::ifstream readArchive(getArchiveName());
    if(!readArchive.is_open()) throw std::runtime_error("Could not open archive file");

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
    if(fileIndex == -1)  throw std::runtime_error("No table called \"" + tableName + "\" found!");

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
    for(Touple t : getTablesInfo()){
        if(t.tableName == _name) throw std::runtime_error("Table names have to be unique!");
    }

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


    std::string tableAddress;
    for(Touple t : getTablesInfo()){
        if(t.tableName == _tableName) {
            tableAddress = t.tableAddress;
        }
    }

    for(Table* table : getOpenedTables()){
        if(table->getTableName() == _tableName) table->writeToFile(tableAddress);
    }

}

void TableManager::addTableToArchive(const std::string& _tableName, const std::string& _tableAddress){
    std::ofstream archive(getArchiveName());
    for(Touple t : getTablesInfo())
        archive << t.tableName << " " << t.tableAddress << "\n";

    archive << _tableName << " " << _tableAddress;
    archive.close();
}

//Създава се локално копие на подадения файл в папката с таблици на проекта
//Приема се че файлът е текстов с подходящия формат (.txt или .csv)
void TableManager::importTable(const std::string& _tableName, const std::string& _tableAddress){
    for(Touple t : getTablesInfo()){
        if(t.tableName == _tableName) throw std::invalid_argument("The name " + _tableName + " is already taken!");
    }

    std::ifstream readFile(_tableAddress);

    std::string fileName = extractName(_tableAddress);
    fileName = "Tables/" + fileName;
    //Ако това име за файл вече е заето се генерира ново

    fileName = generateUniqueFileName(fileName);

    addTableToArchive(_tableName, fileName);
    addTableInfo(_tableName, fileName);

    std::ofstream writeFile(fileName); 

    std::string line;
    while(std::getline(readFile, line)){
        writeFile << line << "\n";
    }

    writeFile.close();
    readFile.close();


    //Това служи за проверка в случай, че файлът на таблицата име невалидни данни, типове или синтаксис
    openTable(_tableName);
    closeTable(_tableName);
}

std::string TableManager::generateUniqueFileName(const std::string& fileNamePref){

    std::string fileName;

    std::string extension = ".csv";
    int extra = -1;

    bool uniqueName = false;    
    while(!uniqueName){
        int i = 0;
        extra++;
        for(Touple t : getTablesInfo()){
            if(extra == 0)
                if((fileNamePref + extension) == t.tableAddress) break;
            else if((fileNamePref + "(" + std::to_string(extra) + ")" + extension) == t.tableAddress) break;
            if(i == getTablesInfo().size()-1) uniqueName = true;
            i++;
        }
    }

    fileName = fileNamePref + ((extra==0)? "":("(" + std::to_string(extra) + ")")) + extension;
    return fileName;
}

std::string TableManager::extractName(const std::string& _fileAddress){
    std::string fileName;
    bool toAppend = false;
    for(int i = _fileAddress.size()-1; i >= 0; i--){
        if(_fileAddress.at(i) == '\\') break;
        if(toAppend) fileName = _fileAddress.at(i) + fileName;
        if(_fileAddress.at(i) == '.') toAppend = true;
    }
    return fileName;
}

void TableManager::closeTable(const std::string& _tableName){
    int i = 0;
    for(Table* t : getOpenedTables()){
        if(t->getTableName() == _tableName){
            delete t;
            getOpenedTables().erase(getOpenedTables().begin()+i);
        }
        i++;
    }
}

bool TableManager::isOpened(const std::string& _tableName){
    for(Table* t : getOpenedTables()){
        if(t->getTableName() == _tableName) return true;
    }
    return false;
}

void TableManager::innerJoin(const std::string& table1, const std::string& field1, const std::string& table2, const std::string& field2, const std::string& newTableName){
    Table* t1 = getTable(table1);
    Table* t2 = getTable(table2);
    
    unsigned fieldIndex1 = t1->findFieldIndex(field1);
    unsigned fieldIndex2 = t2->findFieldIndex(field2);

    if(t1->getTableFields().at(fieldIndex1)->getType() != t2->getTableFields().at(fieldIndex2)->getType())
        throw std::invalid_argument("Can not join tables on fields of different type!");

    Table* joinedTable = new Table(newTableName);


    //Не е решен проблемът двусмислието на имената на полетата
    //(две полета в joinedTable може да имат еднакви имена)
    for(TableField* tf : t1->getTableFields())
        joinedTable->addField(t1->getTableName() + "." + tf->getName(), tf->getType());


    for(TableField* tf : t2->getTableFields())
        joinedTable->addField(t2->getTableName() + "." + tf->getName(), tf->getType());


    //Проверява всяка двойка редове, дали да бъде добавена в joinedTable
    for(int i = 0; i < t1->getRowsCount(); i++){
        for(int j = 0; j < t2->getRowsCount(); j++){
            if(t1->getTableFields().at(fieldIndex1)->getValues().at(i)->getStringValue() == 
                        t2->getTableFields().at(fieldIndex2)->getValues().at(j)->getStringValue()){
                
                std::vector<std::string> values;
                for(TableField* tf : t1->getTableFields())
                if(tf->getType()=="string") {
                    values.push_back("\"" + tf->getValues().at(i)->getStringValue() + "\"");

                }else if(tf->getValues().at(i)->getStringValue() == "NULL") {
                    values.push_back("");
                }else {
                    values.push_back(tf->getValues().at(i)->getStringValue());
                }

                for(TableField* tf : t2->getTableFields())
                    if(tf->getType()=="string") {
                        values.push_back("\"" + tf->getValues().at(j)->getStringValue() + "\"");
                    }else if(tf->getValues().at(j)->getStringValue() == "NULL") {
                        values.push_back("");
                    }else{
                        values.push_back(tf->getValues().at(j)->getStringValue());
                    }  

                joinedTable->insertRecord(values);
            }
        }
    }
    
    //Записва информацията за таблицата в архива и в нов файл
    //Отваря таблицата за ползване
    std::string fileAddress = "Tables/" + generateUniqueFileName(newTableName);
    addTableInfo(newTableName, fileAddress);
    addTableToArchive(newTableName, fileAddress);
    openedTables.push_back(joinedTable);
    joinedTable->writeToFile(fileAddress);

}

TableManager::~TableManager(){
    for(Table* t: openedTables)
        delete t;
}