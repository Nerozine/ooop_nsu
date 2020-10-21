#ifndef OOOP_NSU_VALIDATOR_H
#define OOOP_NSU_VALIDATOR_H
#include "Blocks.h"


class Validator {
public:
    static void workflowCommandsNumberIsCorrect(std::vector<std::string> *commands, std::vector<int> *order);
    static void workflowNoRepeatsInOrder(std::vector<int> *order);
    static void checkCommandSyntax(std::vector<std::string> *commands);
    static void checkConformityOrderCommands(std::map<int, IWorker*>* blocks, std::vector<int>* order);
    static void checkInputOutput(std::map<int, IWorker*>* blocks, std::vector<int>* order,
            bool commandLineI, bool commandLineO);
};


#endif //OOOP_NSU_VALIDATOR_H
