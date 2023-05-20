#include "Table.h"
#include <stdexcept>

Table::Table(const std::string& _tableName, const std::string& fileAddres){

    setTableName(_tableName);

    //отвряне на файла
    std::ifstream file(fileAddres);
    if(!file.is_open()) throw std::runtime_error("Could not open the table!");

    std::string line;
    if(file.good()){
        
        //Задаване на типовете
        std::getline(file, line);
        if(line.empty()) throw std::runtime_error("Error! Can not read table data!");
        std::vector<std::string> types = splitLine(line);

        //Задаване на имената на полетата
        std::getline(file, line);
        if(line.empty()) throw std::runtime_error("Error! Can not read table data!");
        std::vector<std::string> names = splitLine(line);

        //Проверка дали броят на подадените имена е различен от броя на типовете
        unsigned tempFieldsCount = names.size();
        if(tempFieldsCount != types.size())
            throw std::invalid_argument("Error! Number of types and field names does not match!");


        setFieldsCount(tempFieldsCount);

        //Добавяне на колоните и добавяне на дължините на имената на колоните
        for(int i = 0; i < tempFieldsCount; i++){
            if(!isValidType(types.at(i))) throw std::invalid_argument("|" + types.at(i) + "| is not a valid type!");
            if(names.at(i).find(" ") != std::string::npos) throw std::invalid_argument("Field names can not contain spaces!");

            TableField* tC = new TableField(types.at(i), names.at(i));
            getTableFields().push_back(tC);
            fieldLongest.push_back(names.at(i).size());
        }

        //Добавяне на стойностите към колоните
        while(std::getline(file, line)){
            std::vector<std::string> rowValues = splitLine(line);
            insertRecord(rowValues);    
        }   
    }

    file.close();
}

void Table::setTableName(const std::string& _tableName){
    tableName = _tableName;
}

void Table::setFieldsCount(unsigned _fieldsCount){
    fieldsCount = _fieldsCount;
}

void Table::setFieldsNames(const std::vector<std::string>& _newNames){
    int i = 0;
    for(TableField* tc : getTableFields()){
        tc->setType(_newNames.at(i));
        i++;
    }
}

void Table::setFieldsTypes(const std::vector<std::string>& _newTypes){
    int i = 0;
    for(TableField* tc : getTableFields()){
        tc->setType(_newTypes.at(i));
        i++;
    }
}

unsigned Table::getFieldsCount(){
    return fieldsCount;
}

unsigned Table::getRowsCount(){
    return getTableFields().at(0)->getValuesCount();
}

std::string Table::getTableName(){
    return tableName;
}

std::vector<TableField*>& Table::getTableFields(){
    return fields;
}

std::vector<std::string> Table::splitLine(const std::string& line){
    bool quotes = false;
    std::vector<std::string> splLine;
    std::string currentString = "";

    for(char c : line){
        if(c == '\"') quotes = !quotes;
        if(c == ',' && !quotes) {
            splLine.push_back(trim(currentString));
            currentString = "";   
            continue;
        }
        currentString += c;
    }

    splLine.push_back(trim(currentString));
    return splLine;
}

void Table::describe(){

    if(getFieldsCount() == 0) return;

    //Подобно на printTable()

    //В началото на редовете се добавят "Field" и "Type"

    std::string lineSeparator = "+-------";

    for(int i = 0; i < getFieldsCount(); i++){
        lineSeparator += "+";
        int len = std::max(getTableFields().at(i)->getName().size(), getTableFields().at(i)->getType().size());
        std::string temp(len+2, '-');
        lineSeparator += temp;
    }
    lineSeparator += "+";

    std::cout << lineSeparator << "\n";
    
    std::cout << "| Type  ";

    for(TableField* field : getTableFields()){
        std::cout << align(field->getType(), std::max(field->getType().size(), field->getName().size()));
    }

    std::cout << "|\n" << lineSeparator << "\n";
    
    std::cout << "| Field ";

    int fieldNumber = 0;
    for(TableField* field : getTableFields()){
        std::cout << align(field->getName(), std::max(getTableFields().at(fieldNumber)->getType().size(), field->getName().size()));
        fieldNumber++;
    }
    
    std::cout << "|\n" << lineSeparator;
}

void Table::printTable(){

    //Първо се изгражда разделителя за редове
    //Извеждат се имената на полетата, а после и един по един - редовете
    //В края на всеки ред се добавя |

    std::string lineSeparator = makeLineSeparator();

    std::cout << lineSeparator << "\n";

    int i = 0;
    for(TableField* field : getTableFields()){
        std::cout << align(field->getName(), fieldLongest.at(i));
        i++;
    }
    if(i != 0) std::cout << "|";
    else return;

    std::cout << "\n" << lineSeparator << "\n";

    for(int j = 0; j < getRowsCount(); j++){
        for(int k = 0; k < getFieldsCount(); k++){
            std::cout << align(getTableFields().at(k)->getValues().at(j)->getStringValue(), fieldLongest.at(k));
        }
        std::cout << "|\n";
    }

    std::cout << lineSeparator << "\n";
}

std::string Table::makeLineSeparator(){
    std::string lineSeparator;

    for(int len : fieldLongest){
        lineSeparator += "+";
        std::string temp(len+2, '-');
        lineSeparator += temp;
    }
    lineSeparator += "+";

    return lineSeparator;
}

std::string Table::align(const std::string& str, unsigned maxLength){
    std::string aligned = "| ";
    unsigned spacesToAdd = maxLength - str.size();
    int i = 0;
    for(; i < spacesToAdd/2; i++)
        aligned += " ";
    
    aligned += str;

    for(; i < spacesToAdd; i++)
        aligned += " ";
    
    return aligned + " ";
}

void Table::insertRecord(const std::vector<std::string>& values){
    if(values.size() < getFieldsCount()) throw std::invalid_argument("Invalid number of arguments!");

    //ТОЗИ МЕТОД ДА НЕ СЕ ПРОМЕНЯ!!!
    int i = 0;
    for(std::string value : values){
        DataType* temp = factory(value, getTableFields().at(i)->getType());
        getTableFields().at(i)->addValue(temp); 
        //ТУК Е ВАЖНО ДА Е ТОЧНО temp->getStringValue().size(), а не value.size()!       
        if(temp->getStringValue().size() > fieldLongest.at(i)) fieldLongest.at(i) = temp->getStringValue().size();
        i++;
    }
}

DataType* Table::factory(const std::string& value, const std::string& type){
    DataType* product;
    
    if(value == "") product = new Null(type);
    else if(type == "int")
        product = new Integer(value);
    else if(type == "double")
        product = new Double(value);
    else if(type == "string")
        product = new String(value);
    else throw std::invalid_argument(type + " is not a data valid type!");
    
    return product;
}

void Table::addField(const std::string& _name, const std::string& _type){
    fieldLongest.push_back(_name.size());
    TableField* newField = new TableField(_type, _name);

    DataType* value;
    for(int i = 0; i < getRowsCount(); i++){
        value = factory("", _type);
        newField->addValue(value);
        if(value->getStringValue().size() > fieldLongest.at(getFieldsCount()-1)) fieldLongest.at(getFieldsCount()-1) = value->getStringValue().size();
    }


    getTableFields().push_back(newField);
    fieldsCount++;
}

void Table::select(const std::string& fieldName, const std::string& value){
    unsigned fNum = 0;
    //Намира номера на полето, за да имаме директен достъп до това поле (fNum)
    for(TableField* field : getTableFields()){
        if(fieldName == field->getName()) break;
        fNum++;
    }
    if(fNum >= getFieldsCount()) throw std::invalid_argument(fieldName + " is not a name of a field in " + tableName);

    std::string lineSeparator = makeLineSeparator();
    
    std::cout << lineSeparator << "\n";

    //Принтира горната част на таблицата
    int i = 0;
    for(TableField* field : getTableFields()){
        std::cout << align(field->getName(), fieldLongest.at(i));
        i++;
    }
    if(i != 0) std::cout << "|";
    else return;

    std::cout << "\n" << lineSeparator << "\n";

    for(int i = 0; i < getRowsCount(); i++){
        //Проверява за равнство на полетата и отпечатва реда
        if(getTableFields().at(fNum)->getValues().at(i)->equals(value)){
            int fieldN = 0;
            for(TableField* tc : getTableFields()){
                std::cout << align(tc->getValues().at(i)->getStringValue(), fieldLongest.at(fieldN));    
                fieldN++;
            }
            std::cout << "|\n" << lineSeparator << "\n";
        }
    }

}

void Table::writeToFile(const std::string& fileAddress){
    std::ofstream file(fileAddress);
    for(int i = 0; i < getFieldsCount(); i++)
        file << getTableFields().at(i)->getType() << ((i != getFieldsCount()-1)? ",":"");

    file << "\n";

    for(int i = 0; i < getFieldsCount(); i++)
        file << getTableFields().at(i)->getName() << ((i != getFieldsCount()-1)? ",":"");

    file << "\n";

    for(int i = 0; i < getRowsCount(); i++){
        for(int j = 0; j < getFieldsCount(); j++){
            if(getTableFields().at(j)->getValues().at(i)->getTypeName() == "string") 
                file << toWritable(getTableFields().at(j)->getValues().at(i)->getStringValue());
            else file << getTableFields().at(j)->getValues().at(i)->getStringValue();
            if(j < getFieldsCount()-1) file << ",";
        }
        file << "\n";   
    }

    file.close();
}

std::string Table::toWritable(const std::string& str){
    std::string copyStr = str;

    for(int i = 0; i < copyStr.size(); i++){
        if(copyStr.at(i) == '\"' || copyStr.at(i) == '\\') {
            std::string t = "\\";
            copyStr.insert(i, t);
            //Ако няма i++ става безкраен цикъл
            i++;
        }
    }
    
    copyStr = "\"" + copyStr + "\"";

    return copyStr;
}

void Table::deleteValues(const std::string& searchField, const std::string& value){
    unsigned fieldIndex = findFieldIndex(searchField);
    if(fieldIndex >= getFieldsCount()) throw std::invalid_argument("No field called " + searchField + " found in the table!");

    std::string newValue = value;
    if(getTableFields().at(fieldIndex)->getType() == "string") newValue = removeParentheses(value);
    

    for(int i = 0; i < getRowsCount(); i++){
        if(i >= getTableFields().at(fieldIndex)->getValuesCount()) break;
        if(getTableFields().at(fieldIndex)->getValues().at(i)->getStringValue() == newValue){
            for(TableField* tf : getTableFields()){
                tf->getValues().erase(tf->getValues().begin()+i);
    	        tf->setValuesCount(tf->getValuesCount()-1);
            }
            i--;
        }
    }
}

unsigned Table::countValues(const std::string& searchField, const std::string& value){
    unsigned fieldIndex = findFieldIndex(searchField);
    if(fieldIndex >= getFieldsCount()) throw std::invalid_argument("No field called " + searchField + " found in the table!");

    unsigned count = 0;
    for(int i = 0; i < getRowsCount(); i++){
        if(getTableFields().at(fieldIndex)->getValues().at(i)->getStringValue() == removeParentheses(value))
            count++;
    }

    return count;
}

void Table::update(const std::string& searchField, const std::string& searchValue, const std::string& targetField, const std::string& targetValue){
    unsigned searchIndex = findFieldIndex(searchField);
    if(searchIndex >= getFieldsCount()) throw std::invalid_argument("No field called " + searchField + " found in the table!");

    unsigned targetIndex = findFieldIndex(targetField);
    if(targetIndex >= getFieldsCount()) throw std::invalid_argument("No field called " + targetField + " found in the table!");


    for(int i = 0; i < getRowsCount(); i++){
        if(getTableFields().at(searchIndex)->getValues().at(i)->getStringValue() == removeParentheses(searchValue)){
            getTableFields().at(targetIndex)->getValues().at(i) = factory(targetValue, getTableFields().at(targetIndex)->getType());
        }
    }

}



unsigned Table::findFieldIndex(const std::string& fieldName){
    unsigned fieldIndex = 0;
    for(TableField* tf : getTableFields()){
        if(tf->getName() == fieldName) break;
        fieldIndex++;
    }
    return fieldIndex;
}

std::string Table::removeParentheses(const std::string& str){
    if(str.at(0) == '\"') return str.substr(1, str.size()-2);
    else return str;
}

bool Table::isValidType(const std::string& _type){
    return _type == "string" || _type == "int" || _type == "double";
}

std::string Table::trim(const std::string& str){

    std::string trim = "";
    unsigned leftSpaces = 0;
    unsigned rightSpaces = 0;
    
    int i = 0;
    while(i < str.size() && (str.at(i) == ' ' || str.at(i) == '\t')) i++;
    leftSpaces = i;

    i = str.size()-1;
    while(i >= 0 && (str.at(i) == ' ' || str.at(i) == '\t')) i--;
    rightSpaces = i;

    if(leftSpaces > rightSpaces) return trim;

    trim = str.substr(leftSpaces, rightSpaces-leftSpaces+1);
    return trim;
}

Table::~Table(){
    for(TableField* field : getTableFields()){
        delete field;
    }
}   

