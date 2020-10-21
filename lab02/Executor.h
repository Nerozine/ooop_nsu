#ifndef OOOP_NSU_EXECUTOR_H
#define OOOP_NSU_EXECUTOR_H
#include "Blocks.h"

class Executor {
public:
    static void execute(std::map<int, IWorker*>* blocks, std::vector<int>* order, bool commandLineI, bool commandLineO,
            std::string& commandLineInPath, std::string& commandLineOutPath);
};
#endif //OOOP_NSU_EXECUTOR_H
