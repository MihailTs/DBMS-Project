#pragma once
#include <vector>
#include <string>
#include "Table.h"

class TableMenager{

    private:
        
        //Адрес по default
        std::string archive = "archive.txt";
        std::vector<Table*> openedTables;

    public:

        //Приема името на архивния файл
        TableMenager(const std::string&);

        void setArchiveName(const std::string&);

        //име на таблица
        void openTable(const std::string&);

        Table* getTable(const std::string&);

        ~TableMenager();

};