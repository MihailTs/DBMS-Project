#pragma once
#include <vector>
#include <string>
#include "Table.h"

class TableManager{

    private:
        
        struct Touple{
            std::string tableName;
            std::string tableAddress;
        };


        //Архив по default
        std::string archive = "archive.txt";
        std::vector<Table*> openedTables;

        //Съхраняваме данните от архива, за да не се налага многократно четене
        std::vector<Touple> tablesInfo;

        void addTableInfo(const std::string&, const std::string&);

        void removeTableInfo(const std::string&);

        void setArchiveName(const std::string&);

        std::string getArchiveName() const;

        std::string align(const std::string&, unsigned);

    public:

        //Приема името на архивния файл
        TableManager(const std::string&);

        //име на таблица
        void openTable(const std::string&);

        void showTables();

        //Име на таблица
        bool contains(const std::string&);

        Table* getTable(const std::string&);

        std::vector<Table*>& getOpenedTables();

        ~TableManager();

};