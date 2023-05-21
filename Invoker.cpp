#include "Invoker.h"

Invoker::Invoker(TableManager* _tableManager){
    tableManager = _tableManager;

    command = new ExitCommand(tableManager);
}

Invoker::Invoker(TableManager* _tableManager, const std::string& strCommand){
    tableManager = _tableManager;
    setCommand(strCommand);
}

void Invoker::setCommand(const std::string& strCommand){
    delete getCommand();

    std::string finalCommand = trim(strCommand);
    //strCommand = stripSpaces(strCommand);

    command = factory(finalCommand);
}

ICommand* Invoker::factory(std::string& finalCommand){
    ICommand* command;
    if(toLower(finalCommand).substr(0, 5) == "open "){
        std::string tableName = trim(finalCommand.substr(5));
        command = new OpenCommand(tableManager, tableName);
    }
    else if(toLower(finalCommand).substr(0, 6) == "close "){
        std::string tableName = trim(finalCommand.substr(6));
        command = new CloseCommand(tableManager, tableName);
    }
    else if(toLower(finalCommand) == "exit") {
        command = new ExitCommand(tableManager);
    }
    else if(toLower(finalCommand) == "help") {
        command = new HelpCommand;
    }
    else if(toLower(finalCommand.substr(0, 8)) == "describe "){
        command = new DescribeCommand(tableManager, trim(finalCommand.substr(9)));
    }
    else if(toLower(finalCommand.substr(0, 6)) == "print "){
        command = new PrintTableCommand(tableManager, trim(finalCommand.substr(6)));
    }
    else if(toLower(finalCommand) == "showtables"){
        command = new ShowTablesCommand(tableManager);
    } 
    else if(toLower(finalCommand.substr(0, 7)) == "insert "){
        finalCommand = trim(finalCommand.substr(7));
        std::string tableName = finalCommand.substr(0, finalCommand.find(' '));

        std::vector<std::string> data = splitLine(trim(finalCommand.substr(finalCommand.find(' ')+1)));
        command = new InsertCommand(tableManager, tableName, data);
    }
    else if(toLower(finalCommand.substr(0, 7)) == "rename "){
        finalCommand = trim(finalCommand.substr(6));
        //няма нужда от trim
        std::string oldName = finalCommand.substr(0, finalCommand.find(" "));
        std::string newName = trim(finalCommand.substr(finalCommand.find(" ")));
        command = new RenameCommand(tableManager, oldName, newName);
    }
    else if(toLower(finalCommand.substr(0, 10)) == "addcolumn "){
        finalCommand = trim(finalCommand.substr(10));
        //няма нужда от trim
        std::string tableName = finalCommand.substr(0, finalCommand.find(" "));
        finalCommand = trim(finalCommand.substr(finalCommand.find(" ")));
        std::string fieldName = finalCommand.substr(0, finalCommand.find(" "));
        std::string fieldType = trim(finalCommand.substr(finalCommand.find(" ")));
        command = new AddColumnCommand(tableManager, tableName, fieldName, fieldType);
    }
    else if(toLower(finalCommand.substr(0, 7)) == "select "){
        finalCommand = trim(finalCommand.substr(7));
        //няма нужда от trim
        std::string fieldName = finalCommand.substr(0, finalCommand.find(" "));
        finalCommand = trim(finalCommand.substr(finalCommand.find(" ")));
        //Ако value е стринг с кавички и възможен интервал м/у тях се налага
        //по-точна обработка
        int index = 0;
        std::string value = removeParentheses(getFirstValue(trim(finalCommand), &index));
        std::string tableName = trim(finalCommand.substr(index+1));
        command = new SelectCommand(tableManager, tableName, fieldName, value);
    }
    else if(toLower(finalCommand.substr(0, 7)) == "export "){
        finalCommand = trim(finalCommand.substr(7));
        std::string tableName = finalCommand.substr(0, finalCommand.find(" "));
        std::string fileAddress = removeParentheses(trim(finalCommand.substr(finalCommand.find(" "))));
        command = new ExportCommand(tableManager, tableName, fileAddress);
    }
    else if(toLower(finalCommand.substr(0, 5)) == "save "){
        command = new SaveCommand(tableManager, trim(finalCommand.substr(5)));
    }
    else if(toLower(finalCommand.substr(0, 7)) == "saveas "){
        finalCommand = trim(finalCommand.substr(7));
        std::string tableName = finalCommand.substr(0, finalCommand.find(" "));
        std::string fileAddress = removeParentheses(trim(finalCommand.substr(finalCommand.find(" "))));
        command = new SaveAsCommand(tableManager, tableName, fileAddress);
    }
    else if(toLower(finalCommand.substr(0, 7)) == "import "){
        finalCommand = trim(finalCommand.substr(7));
        std::string tableName = finalCommand.substr(0, finalCommand.find(" "));
        std::string fileAddress = removeParentheses(trim(finalCommand.substr(finalCommand.find(" "))));
        command = new ImportCommand(tableManager, tableName, fileAddress);
    }
    else if(toLower(finalCommand.substr(0, 7)) == "delete "){
        finalCommand = trim(finalCommand.substr(7));
        std::string tableName = finalCommand.substr(0, finalCommand.find(" "));
        finalCommand = trim(finalCommand.substr(finalCommand.find(" ")));
        std::string searchField = finalCommand.substr(0, finalCommand.find(" "));
        std::string value = removeParentheses(trim(finalCommand.substr(finalCommand.find(" "))));
        command = new DeleteCommand(tableManager, tableName, searchField, value);
    }
    else if(toLower(finalCommand.substr(0, 6)) == "count "){
        finalCommand = trim(finalCommand.substr(6));
        std::string tableName = finalCommand.substr(0, finalCommand.find(" "));
        finalCommand = trim(finalCommand.substr(finalCommand.find(" ")));
        std::string searchField = finalCommand.substr(0, finalCommand.find(" "));
        std::string value = removeParentheses(trim(finalCommand.substr(finalCommand.find(" "))));
        command = new CountCommand(tableManager, tableName, searchField, value);
    }
    else if(toLower(finalCommand.substr(0, 7)) == "update "){
        finalCommand = trim(finalCommand.substr(7));
        std::string tableName = finalCommand.substr(0, finalCommand.find(" "));
        finalCommand = trim(finalCommand.substr(finalCommand.find(" ")));
        std::string searchField = finalCommand.substr(0, finalCommand.find(" "));
        finalCommand = trim(finalCommand.substr(finalCommand.find(" ")));
        int ind = 0;
        std::string searchValue = removeParentheses(getFirstValue(trim(finalCommand), &ind));
        finalCommand = trim(finalCommand.substr(ind+1));  
        std::string targetField = finalCommand.substr(0, finalCommand.find(" "));
        finalCommand = trim(finalCommand.substr(finalCommand.find(" ")));
        std::string targetValue = finalCommand;
        command = new UpdateCommand(tableManager, tableName, searchField, searchValue, targetField, targetValue);
    }
    else if(toLower(finalCommand.substr(0, 11)) == "inner join "){
        finalCommand = trim(finalCommand.substr(11));
        std::string table1 = finalCommand.substr(0, finalCommand.find(" "));
        finalCommand = trim(finalCommand.substr(finalCommand.find(" ")));
        std::string field1 = finalCommand.substr(0, finalCommand.find(" "));
        finalCommand = trim(finalCommand.substr(finalCommand.find(" ")));
        std::string table2 = finalCommand.substr(0, finalCommand.find(" "));
        finalCommand = trim(finalCommand.substr(finalCommand.find(" ")));
        std::string field2 = finalCommand.substr(0, finalCommand.find(" "));
        finalCommand = trim(finalCommand.substr(finalCommand.find(" ")));
        std::string newTableName = finalCommand;
        command = new InnerJoinCommand(tableManager, table1, field1, table2, field2, newTableName);
    }
    else if(toLower(finalCommand.substr(0, 9)) == "agregate "){
        finalCommand = trim(finalCommand.substr(9));
        std::string tableName = finalCommand.substr(0, finalCommand.find(" "));
        finalCommand = trim(finalCommand.substr(finalCommand.find(" ")));
        std::string searchField = finalCommand.substr(0, finalCommand.find(" "));
        finalCommand = trim(finalCommand.substr(finalCommand.find(" ")));
        int ind = 0;
        std::string searchValue = removeParentheses(getFirstValue(trim(finalCommand), &ind));
        finalCommand = trim(finalCommand.substr(ind+1));  
        std::string targetField = finalCommand.substr(0, finalCommand.find(" "));
        finalCommand = trim(finalCommand.substr(finalCommand.find(" ")));
        std::string operation = finalCommand;
        command = new AgregateCommand(tableManager, tableName, searchField, searchValue, targetField, operation);
    }

    else throw std::invalid_argument("The command you entered is not a valid command!");

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
    delete []getCommand();
}
