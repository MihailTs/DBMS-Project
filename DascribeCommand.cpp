#include "DescribeCommand.h"

DescribeCommand::DescribeCommand(TableMenager* _tableMenager, const std::string _tableName){
    tableMenager = _tableMenager;
    tableName = _tableName;
}

void DescribeCommand::execute(){
    //Проверка за съществуване на файла
    //(1) Намира файла в архива
    //(2) Чете от файла първите два реда
    //(3) Затваря файла
}