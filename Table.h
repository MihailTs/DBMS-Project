#include <string>
#include <vector>
#include "TableRow.h"

class Table{

    private:
        //Име на таблицата
        std::string tableName;        

        /*
            Типове на полетата
        */

        //Имена на полетата (колоните) и броят им
        std::string* fieldsNames;
        unsigned fieldsCount;

        //Записи (редове)
        std::vector<TableRow> tableRows; 


        void setTableName(std::string);

        void setFieldsNames(std::string*, unsigned);

        //?
        //void setFieldsCount(unsigned);
        //?

        void setRows(const std::vector<TableRow>&);


    public:
    
        //Празна таблица само с име
        Table(std::string);

        //Таблица по файл
        Table(std::fstream);

        std::string getTableName() const;

        std::string* getFieldsNames() const;

        unsigned getFieldsCount() const;

        std::vector<TableRow>& getTableRows();

        std::vector<TableRow> getTableRowsCopy() const;

        unsigned getRowsCount() const;

        ~Table();
};