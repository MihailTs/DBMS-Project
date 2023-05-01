#include <vector>
#include <fstream>
#include "DataType.h"

class TableRow{

    private:

        //данните във всяка клетка от записа
        std::vector<DataType*> fieldsValues;
        unsigned fieldsCount;

        void setFieldsCount(unsigned);

    public:

        TableRow();

        std::vector<DataType*> getFieldsValues() const;

        unsigned getFieldsCount();

        //adds another value to the end of the row
        void addFieldValue(DataType*);

        // friend std::ostream& operator<<(std::ostream&, const TableRow&);

};