#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include "TableField.h"
#include "DataType.h"
#include "String.h"
#include "Null.h"
#include "Double.h"
#include "Integer.h"


class Table{

    private:    

        std::string tableName;

        unsigned fieldsCount;

        std::vector<TableField*> fields;

        //Най-дългите стойности в колоните
        std::vector<int> fieldLongest;

        void setFieldsNames(const std::vector<std::string>&);

        void setFieldsTypes(const std::vector<std::string>&);

        void setFieldsCount(unsigned);

        //Създава нова "променлива" по подадена стойност и тип
        DataType* factory(const std::string&, const std::string&);

        //Връща вектор от низове, разделяйки реда според ','
        std::vector<std::string> splitLine(const std::string&);

        //подравнява низ отляво и отдясно с цел по-добро визуално представяне
        std::string align(const std::string&, unsigned);

        //разделител за рефовете при принтиране на таблица
        std::string makeLineSeparator();

        //Превръща стринг обратно в прочетения вид (прочетен файл)
        //на всяка \ или " добавя отпред "\"(символът)
        std::string toWritable(const std::string&);

        std::string removeParentheses(const std::string&);

        //проверява дали подаденият ни е име на валиден тип
        bool isValidType(const std::string&);

        //премахва интервалите в началото и края на низа
        std::string trim(const std::string&);

    public:

        //празна таблица (този конструктор не се използва)
        Table(const std::string&);

        //Таблица по име и адрес на файл
        Table(const std::string&, const std::string&);

        unsigned getFieldsCount();

        unsigned getRecordsCount();

        //връща всички полета на таблицата
        std::vector<TableField*>& getTableFields();

        std::string getTableName();

        void setTableName(const std::string&);

        //изпълнява print
        void printTable();

        //изпълнява describe
        void describe();

        //изпълнява insert
        void insertRecord(const std::vector<std::string>&);

        //име, тип
        void addField(const std::string&, const std::string&);

        //име на полето желана стойност
        void select(const std::string&, const std::string&);

        //записва таблицата във файла с подадения адрес
        void writeToFile(const std::string&);

        //Изтрива всички записи в които полето (първи аргумент) има дадената стойност (втори аргумент)
        void deleteValues(const std::string&, const std::string&);

        //изпънява count
        unsigned countValues(const std::string&, const std::string&);

        //изпълнява update
        void update(const std::string&, const std::string&, const std::string&, const std::string&);

        //изпълнява agregate
        void agregate(const std::string&, const std::string&, const std::string&, const std::string&);

        //намира номера на поле с дадено име
        unsigned findFieldIndex(const std::string&);

        DataType* sum(DataType*, DataType*);

        DataType* product(DataType*, DataType*);

        DataType* maximum(DataType*, DataType*);

        DataType* minimum(DataType*, DataType*);

        ~Table();
};