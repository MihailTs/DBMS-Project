#include "DescribeCommand.h"

DescribeCommand::DescribeCommand(Table* _table){
    table = _table;
}

void DescribeCommand::execute(){
    for(std::string type : table->getFieldsTypes())
        std::cout << type << " ";
}