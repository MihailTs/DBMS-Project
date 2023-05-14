#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include "TableCol.h"
#include "DataType.h"
#include "String.h"
#include "Integer.h"
#include "Double.h"
#include "Null.h"


class Table{

    private:    

        std::string tableName;

        //Имена, типове и брой на колоните
        std::vector<std::string> fieldsNames;
        std::vector<std::string> fieldsTypes;
        unsigned fieldsCount;

        std::vector<TableCol*> columns;

        //Най-дългите стойности в колоните
        std::vector<int> columnLongest;

        void setFieldsNames(const std::vector<std::string>&);

        void setFieldsTypes(const std::vector<std::string>&);

        void setFieldsCount(unsigned);

        DataType* factory(const std::string&, const std::string&);

        //Връща вектор от низове, разделяйки реда според ','
        std::vector<std::string> splitLine(const std::string&);

        std::string align(const std::string&, unsigned);

    public:
    
        //Таблица по име и адрес на файл
        Table(const std::string&, const std::string&);

        std::vector<std::string>& getFieldsNames();

        std::vector<std::string>& getFieldsTypes();

        unsigned getFieldsCount();

        unsigned getRowsCount();

        std::vector<TableCol*>& getTableColumns();

        std::string getTableName();

        void setTableName(const std::string&);

        void printTable();

        void describe();

        void insertRecord(const std::vector<std::string>&);

        //име, тип
        void addField(const std::string&, const std::string&);

        ~Table();
};