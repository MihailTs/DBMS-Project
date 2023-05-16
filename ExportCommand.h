#include "ICommand.h"

class ExportCommand : public ICommand{

    private:
        TableManager* tableManager;
        std::string tableName;
        std::string fileAddress;

    public:
        ExportCommand(TableManager*, const std::string&, const std::string&);

        void execute();
};