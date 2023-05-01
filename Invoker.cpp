#include "Invoker.h"

Invoker::Invoker(){
    //Някаква стойност по подразбиране
    // setCommand(new ExitCommand);
}

Invoker::Invoker(const ICommand& _command){
    // setCommand(_command);
}

// Invoker::Invoker(std::string _command){
//     setCommand(_command);
// }

// // void setCommand(std::string _command){

// //     //
// //     //От каталог на командите и техните съответни класове
// //     ///////////
// //     //////////
// //     /////////
// //     ////////
// // }


void Invoker::setCommand(const ICommand& _command){
    //command = ;
}

ICommand& Invoker::getCommand(){
    return *command;
}