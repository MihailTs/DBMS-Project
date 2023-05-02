#include <string>
#include <vector>
#include <stdexcept>
#include <fstream>
#include "TableCol.h"

class Table{

    private:    

        //Имена, типове и брой на колоните
        std::vector<std::string> fieldsNames;
        std::vector<std::string> fieldsTypes;
        unsigned fieldsCount;

        std::vector<TableCol> columns;

        void setFieldsNames(const std::vector<std::string>&);

        void setFieldsTypes(const std::vector<std::string>&);

        //Връща вектор от низове, разделяйки реда според ','
        std::vector<std::string> splitLine(const std::string&);

    public:
    
        //Таблица по адрес на файл
        Table(const std::string&);

        std::vector<std::string>& getFieldsNames();

        const std::vector<std::string>& getFieldsTypes() const;

        unsigned getFieldsCount() const;

        std::vector<TableCol>& getTableColumns();

        unsigned getRowsCount() const;

};