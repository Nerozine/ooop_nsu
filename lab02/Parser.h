#ifndef OOOP_NSU_PARSER_H
#define OOOP_NSU_PARSER_H
#include "Blocks.h"


class Parser {
public:
    static std::vector<std::string>* readWorkflow(std::ifstream &workflow);
    static std::vector<int>* getOrder(std::vector<std::string> *lines);
    static std::map<int, IWorker*>* parseBlocks(std::vector<std::string> *commands);
};


#endif //OOOP_NSU_PARSER_H
