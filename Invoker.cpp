#include "Invoker.h"

Invoker::Invoker(TableManager* _tableManager){
    tableManager = _tableManager;
    commandSuccess = false;
}

Invoker::Invoker(TableManager* _tableManager, const std::string& strCommand){
    tableManager = _tableManager;
    commandSuccess = false;
    setCommand(strCommand);
}

void Invoker::setCommand(const std::string& strCommand){
    if(commandSuccess)
        delete getCommand();

    commandSuccess = false;

    std::string finalCommand = trim(strCommand);

    command = factory(finalCommand);
}

ICommand* Invoker::factory(std::string& finalCommand){
        ICommand* command;
        if(toLower(finalCommand).substr(0, 5) == "open "){
            std::string tableName;
            try{
                tableName = trim(finalCommand.substr(5));
            }catch(std::exception& e){
                throw std::invalid_argument("The command you entered is not a valid command!");
            }
            command = new OpenCommand(tableManager, tableName);
        }
        else if(toLower(finalCommand).substr(0, 6) == "close "){
            std::string tableName;
            try{
                tableName = trim(finalCommand.substr(6));
            }catch(std::exception& e){
                throw std::invalid_argument("The command you entered is not a valid command!");
            }
            command = new CloseCommand(tableManager, tableName);
        }
        else if(toLower(finalCommand) == "exit") {
            command = new ExitCommand(tableManager);
        }
        else if(toLower(finalCommand) == "help") {
            command = new HelpCommand;
        }
        else if(toLower(finalCommand.substr(0, 9)) == "describe "){
            try{
                finalCommand = trim(finalCommand.substr(8));
            }catch(std::exception& e){
                throw std::invalid_argument("The command you entered is not a valid command!");
            }
            command = new DescribeCommand(tableManager, finalCommand);
        }
        else if(toLower(finalCommand.substr(0, 6)) == "print "){
            try{
                finalCommand = trim(finalCommand.substr(6));
            }catch(std::exception& e){
                throw std::invalid_argument("The command you entered is not a valid command!");
            }
            command = new PrintTableCommand(tableManager, finalCommand);
        }
        else if(toLower(finalCommand) == "showtables"){
            command = new ShowTablesCommand(tableManager);
        } 
        else if(toLower(finalCommand.substr(0, 7)) == "insert "){
            std::string tableName;
            std::vector<std::string> data;
            try{
                finalCommand = trim(finalCommand.substr(7));
                tableName = finalCommand.substr(0, finalCommand.find(' '));
                data = splitLine(trim(finalCommand.substr(finalCommand.find(' ')+1)));
            }catch(std::exception& e){
                throw std::invalid_argument("The command you entered is not a valid command!");
            }
            command = new InsertCommand(tableManager, tableName, data);
        }
        else if(toLower(finalCommand.substr(0, 7)) == "rename "){
            std::string oldName;
            std::string newName;
            try{
                finalCommand = trim(finalCommand.substr(6));
                //няма нужда от trim
                oldName = finalCommand.substr(0, finalCommand.find(" "));
                newName = trim(finalCommand.substr(finalCommand.find(" ")));
            }catch(std::exception& e){
                throw std::invalid_argument("The command you entered is not a valid command!");
            }
            command = new RenameCommand(tableManager, oldName, newName);
        }
        else if(toLower(finalCommand.substr(0, 10)) == "addcolumn "){
            std::string tableName;
            std::string fieldName;
            std::string fieldType;
            try{
                finalCommand = trim(finalCommand.substr(10));
                //няма нужда от trim
                tableName = finalCommand.substr(0, finalCommand.find(" "));
                finalCommand = trim(finalCommand.substr(finalCommand.find(" ")));
                fieldName = finalCommand.substr(0, finalCommand.find(" "));
                fieldType = trim(finalCommand.substr(finalCommand.find(" ")));
                if(fieldType != "int" && fieldType != "string" && fieldType != "double") 
                    throw std::invalid_argument(fieldType + " is not a valid data type!");
            }catch(std::invalid_argument& ia){
                throw std::invalid_argument(ia.what());
            }
            catch(std::exception& e){
                throw std::invalid_argument("The command you entered is not a valid command!");
            }
            command = new AddColumnCommand(tableManager, tableName, fieldName, fieldType);
        }
        else if(toLower(finalCommand.substr(0, 7)) == "select "){
            std::string fieldName;
            std::string value;
            std::string tableName;
            try{
                finalCommand = trim(finalCommand.substr(7));
                //няма нужда от trim
                fieldName = finalCommand.substr(0, finalCommand.find(" "));
                finalCommand = trim(finalCommand.substr(finalCommand.find(" ")));
                //Ако value е стринг с кавички и възможен интервал м/у тях се налага
                //по-точна обработка
                int index = 0;
                value = removeParentheses(getFirstValue(trim(finalCommand), &index));
                tableName = trim(finalCommand.substr(index+1));
            }catch(std::exception& e){
                throw std::invalid_argument("The command you entered is not a valid command!");
            }
            command = new SelectCommand(tableManager, tableName, fieldName, value);
        }
        else if(toLower(finalCommand.substr(0, 7)) == "export "){
            std::string tableName;
            std::string fileAddress;
            try{
                finalCommand = trim(finalCommand.substr(7));
                tableName = finalCommand.substr(0, finalCommand.find(" "));
                fileAddress = removeParentheses(trim(finalCommand.substr(finalCommand.find(" "))));
            }catch(std::exception& e){
                throw std::invalid_argument("The command you entered is not a valid command!");
            }
            command = new ExportCommand(tableManager, tableName, fileAddress);
        }
        else if(toLower(finalCommand.substr(0, 5)) == "save "){
            try{
                finalCommand = trim(finalCommand.substr(5));
            }catch(std::exception& e){
                throw std::invalid_argument("The command you entered is not a valid command!");
            }
            command = new SaveCommand(tableManager, finalCommand);
        }
        else if(toLower(finalCommand.substr(0, 7)) == "saveas "){
            std::string tableName;
            std::string fileAddress;
            try{
                finalCommand = trim(finalCommand.substr(7));
                tableName = finalCommand.substr(0, finalCommand.find(" "));
                fileAddress = removeParentheses(trim(finalCommand.substr(finalCommand.find(" "))));
            }catch(std::exception& e){
                throw std::invalid_argument("The command you entered is not a valid command!");
            }
            command = new SaveAsCommand(tableManager, tableName, fileAddress);
        }
        else if(toLower(finalCommand.substr(0, 7)) == "import "){
            std::string tableName;
            std::string fileAddress;
            try{
                finalCommand = trim(finalCommand.substr(7));
                tableName = finalCommand.substr(0, finalCommand.find(" "));
                fileAddress = removeParentheses(trim(finalCommand.substr(finalCommand.find(" "))));
            }catch(std::exception& e){
                throw std::invalid_argument("The command you entered is not a valid command!");
            }
            command = new ImportCommand(tableManager, tableName, fileAddress);
        }
        else if(toLower(finalCommand.substr(0, 7)) == "delete "){
            std::string tableName;
            std::string searchField;
            std::string value;
            try{
                finalCommand = trim(finalCommand.substr(7));
                tableName = finalCommand.substr(0, finalCommand.find(" "));
                finalCommand = trim(finalCommand.substr(finalCommand.find(" ")));
                searchField = finalCommand.substr(0, finalCommand.find(" "));
                value = removeParentheses(trim(finalCommand.substr(finalCommand.find(" "))));
            }catch(std::exception& e){
                throw std::invalid_argument("The command you entered is not a valid command!");
            }
            command = new DeleteCommand(tableManager, tableName, searchField, value);
        }
        else if(toLower(finalCommand.substr(0, 6)) == "count "){
            std::string tableName;
            std::string searchField;
            std::string value;
            try{
                finalCommand = trim(finalCommand.substr(6));
                tableName = finalCommand.substr(0, finalCommand.find(" "));
                finalCommand = trim(finalCommand.substr(finalCommand.find(" ")));
                searchField = finalCommand.substr(0, finalCommand.find(" "));
                value = removeParentheses(trim(finalCommand.substr(finalCommand.find(" "))));
            }catch(std::exception& e){
                throw std::invalid_argument("The command you entered is not a valid command!");
            }
            command = new CountCommand(tableManager, tableName, searchField, value);
        }
        else if(toLower(finalCommand.substr(0, 7)) == "update "){
            std::string tableName;
            std::string searchField;
            std::string searchValue;
            std::string targetField;
            std::string targetValue;
            try{
                finalCommand = trim(finalCommand.substr(7));
                tableName = finalCommand.substr(0, finalCommand.find(" "));
                finalCommand = trim(finalCommand.substr(finalCommand.find(" ")));
                searchField = finalCommand.substr(0, finalCommand.find(" "));
                finalCommand = trim(finalCommand.substr(finalCommand.find(" ")));
                int ind = 0;
                searchValue = removeParentheses(getFirstValue(trim(finalCommand), &ind));
                finalCommand = trim(finalCommand.substr(ind+1));  
                targetField = finalCommand.substr(0, finalCommand.find(" "));
                finalCommand = trim(finalCommand.substr(finalCommand.find(" ")));
                targetValue = finalCommand;
            }catch(std::exception& e){
                throw std::invalid_argument("The command you entered is not a valid command!");
            }
            command = new UpdateCommand(tableManager, tableName, searchField, searchValue, targetField, targetValue);
        }
        else if(toLower(finalCommand.substr(0, 11)) == "inner join "){
            std::string table1;
            std::string field1;
            std::string table2;
            std::string field2;
            std::string newTableName;
            try{
                finalCommand = trim(finalCommand.substr(11));
                table1 = finalCommand.substr(0, finalCommand.find(" "));
                finalCommand = trim(finalCommand.substr(finalCommand.find(" ")));
                field1 = finalCommand.substr(0, finalCommand.find(" "));
                finalCommand = trim(finalCommand.substr(finalCommand.find(" ")));
                table2 = finalCommand.substr(0, finalCommand.find(" "));
                finalCommand = trim(finalCommand.substr(finalCommand.find(" ")));
                field2 = finalCommand.substr(0, finalCommand.find(" "));
                finalCommand = trim(finalCommand.substr(finalCommand.find(" ")));
                newTableName = finalCommand;
            }catch(std::exception& e){
                throw std::invalid_argument("The command you entered is not a valid command!");
            }
            command = new InnerJoinCommand(tableManager, table1, field1, table2, field2, newTableName);
        }
        else if(toLower(finalCommand.substr(0, 9)) == "agregate "){
            std::string tableName;
            std::string searchField;
            std::string searchValue;
            std::string targetField;
            std::string operation;
            try{
                finalCommand = trim(finalCommand.substr(9));
                tableName = finalCommand.substr(0, finalCommand.find(" "));
                finalCommand = trim(finalCommand.substr(finalCommand.find(" ")));
                searchField = finalCommand.substr(0, finalCommand.find(" "));
                finalCommand = trim(finalCommand.substr(finalCommand.find(" ")));
                int ind = 0;
                searchValue = removeParentheses(getFirstValue(trim(finalCommand), &ind));
                finalCommand = trim(finalCommand.substr(ind+1));  
                targetField = finalCommand.substr(0, finalCommand.find(" "));
                finalCommand = trim(finalCommand.substr(finalCommand.find(" ")));
                operation = finalCommand;
            }catch(std::exception& e){
                throw std::invalid_argument("The command you entered is not a valid command!");
            }
            command = new AgregateCommand(tableManager, tableName, searchField, searchValue, targetField, operation);
        }
        else if(toLower(finalCommand.substr(0, 5)) == "drop "){
            std::string tableName;
            try{
                tableName = trim(finalCommand.substr(finalCommand.find(" ")));
                command = new DropTableCommand(tableManager, tableName);
            }catch(std::exception& e){
                throw std::invalid_argument("The command you entered is not a valid command!");
            }
        }

        else throw std::invalid_argument("The command you entered is not a valid command!");

    commandSuccess = true;
    return command;
}

ICommand* Invoker::getCommand(){
    return command;
}

std::vector<std::string> Invoker::splitLine(const std::string& line){
    bool quotes = false;
    std::vector<std::string> splLine;
    std::string currentString = "";

    for(char c : line){
        if(c == '\"') quotes = !quotes;
        //Тук е разликата със splitLine на Table
        if(c == ' ' && !quotes) {
            splLine.push_back(currentString);
            currentString = "";   
            continue;
        }
        currentString += c;
    }

    splLine.push_back(currentString);
    return splLine;
}

std::string Invoker::trim(const std::string& str){

    std::string trim = "";
    unsigned leftSpaces = 0;
    unsigned rightSpaces = 0;
    
    int i = 0;
    while(i < str.size() && (str.at(i) == ' ' || str.at(i) == '\t')) i++;
    leftSpaces = i;

    i = str.size()-1;
    while(i >= 0 && (str.at(i) == ' ' || str.at(i) == '\t')) i--;
    rightSpaces = i;

    if(leftSpaces > rightSpaces) return trim;

    trim = str.substr(leftSpaces, rightSpaces-leftSpaces+1);
    return trim;
}

std::string Invoker::toLower(const std::string& str){
    std::string lowerStr = "";

    for(int i = 0; i < str.size(); i++){
        if(str.at(i) >= 'A' && str.at(i) <= 'Z') lowerStr += str.at(i) - ('A' - 'a');
        else lowerStr += str.at(i);
    }
    return lowerStr;
}

std::string Invoker::getFirstValue(const std::string& str, int* index){
    std::string value = "";
    bool par = false;
    for(int i = 0; i < str.size(); i++){
        *index = i;
        if(str.at(i) == '\"' && !par) par = true;
        else if(str.at(i) == '\"' && par) {
            value += str.at(i);
            break;
        } 
        else if(str.at(i) == ' ' && !par) break;

        value += str.at(i);
    }

    return value;
}

std::string Invoker::removeParentheses(const std::string& str){
    if(str.at(0) == '\"') return str.substr(1, str.size()-2);
    else return str;
}

Invoker::~Invoker(){
    delete getCommand();
}
