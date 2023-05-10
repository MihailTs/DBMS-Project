#pragma once
#include <vector>
#include <string>
#include "Table.h"

class TableMenager{

    private:
        
        struct Touple{
            std::string tableName;
            std::string tableAddres;
        };


        //Архив по default
        std::string archive = "archive.txt";
        std::vector<Table*> openedTables;

        //Съхраняваме данните от архива, за да не се налага многократно четене
        std::vector<Touple> tablesInfo;

        void addTableInfo(const std::string&, const std::string&);

        void removeTableInfo(const std::string&);

    public:

        //Приема името на архивния файл
        TableMenager(const std::string&);

        void setArchiveName(const std::string&);

        //име на таблица
        void openTable(const std::string&);

        Table* getTable(const std::string&);

        std::vector<Table*>& getOpenedTables();

        ~TableMenager();

};