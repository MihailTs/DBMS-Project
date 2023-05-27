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

        std::string tablesFolder = "Tables/";

        //Съхраняваме данните от архива, за да не се налага многократно четене
        std::vector<Touple> tablesInfo;

        void removeTableInfo(const std::string&);

        void setArchiveName(const std::string&);

        std::string getTablesFolder();

        std::string getArchiveName() const;

        void renameInArchive(const std::string&, const std::string&);

        //Форматира стринга така, че да има опреената дължина
        std::string align(const std::string&, unsigned);

        //Връща името на файл (без разширението) по подаден адрес
        //Пример - "D:\Data\Table.csv" -> "Table"
        std::string extractName(const std::string&);

        std::string generateUniqueFileName(const std::string&);

    public:

        //Приема името на архивния файл
        TableManager(const std::string&);

        //По име на таблица
        void openTable(const std::string&);

        void showTables();

        //По име на таблица
        bool contains(const std::string&);

        //По име на таблица
        Table* getTable(const std::string&);

        std::vector<Table*>& getOpenedTables();

        std::vector<Touple>& getTablesInfo();

        //Ново име, старо име
        void renameTable(const std::string&, const std::string&);

        //По име на таблица
        void saveTable(const std::string&);

        //Име и адрес
        void addTableInfo(const std::string&, const std::string&);

        //Име и адрес
        void addTableToArchive(const std::string&, const std::string&);
        
        //Име и адрес
        void importTable(const std::string&, const std::string&);

        //По име на таблица
        void closeTable(const std::string&);

        //По име на таблица
        bool isOpened(const std::string&);

        //Таблица1, поле1, таблица2, поле2, име на новата таблица
        void innerJoin(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&);

        //По име на таблица
        void dropTable(const std::string&);

        ~TableManager();

};