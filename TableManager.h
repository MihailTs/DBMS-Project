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

        //име на таблица
        void openTable(const std::string&);

        void showTables();

        //Име на таблица
        bool contains(const std::string&);

        Table* getTable(const std::string&);

        std::vector<Table*>& getOpenedTables();

        std::vector<Touple>& getTablesInfo();

        //ново име, старо име
        void renameTable(const std::string&, const std::string&);

        //име на таблицата
        void saveTable(const std::string&);

        void addTableInfo(const std::string&, const std::string&);

        void addTableToArchive(const std::string&, const std::string&);

        void importTable(const std::string&, const std::string&);

        void closeTable(const std::string&);

        bool isOpened(const std::string&);

        void innerJoin(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&);

        void dropTable(const std::string&);

        ~TableManager();

};