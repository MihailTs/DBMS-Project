#include <string>
#include <vector>
#include "TableRow.h"

class Table{

    private:
        //Име на таблицата
        std::string tableName;        

        //Имена, типове и брой на колоните
        std::string* fieldsNames;
        std::vector<std::string> fieldsTypes;
        unsigned fieldsCount;

        //Записи (редове)
        std::vector<TableRow> tableRows; 


        void setTableName(std::string);

        void setFieldsNames(std::string*, unsigned);

        //?
        //void setFieldsCount(unsigned);
        //?

        //void setCols(const std::vector<TableCol>&);


    public:
    
        //Празна таблица само с име
        Table(std::string);

        //Таблица по файл
        Table(std::fstream);

        std::string getTableName() const;

        std::string* getFieldsNames() const;

        std::vector<std::string>& getFieldsTypes() const;

        unsigned getFieldsCount() const;



        std::vector<TableRow>& getTableRows();

        std::vector<TableRow> getTableRowsCopy();

        unsigned getRowsCount() const;

        ~Table();
};