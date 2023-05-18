#include "ICommand.h"

class SaveAsCommand : public ICommand{

    private:
        TableManager* tableManager;
        std::string tableName;
        std::string saveAddress;

    public:

        SaveAsCommand(TableManager*, const std::string&, const std::string&);

        void execute();

};