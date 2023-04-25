#include <iostream>

class DataType{

    public:

        getValue();

        friend std::ostream& operator<<(std::ostream&, const DataType&);
};