#include "Executor.h"

void Executor::execute(std::map<int, IWorker *> *blocks, std::vector<int> *order, bool commandLineI, bool commandLineO,
        std::string& inPath, std::string& outPath) {
    using namespace std;
    vector<string>* text = nullptr;
    if (commandLineI) {
        text = ReadFile(inPath).task(text);
    }
    for(int i = 0; i < order->size(); i++) {
        if (dynamic_cast<Replace*>((*blocks)[(*order)[i]])) {
            text = dynamic_cast<Replace*>((*blocks)[(*order)[i]])->task(text);
            delete (*blocks)[(*order)[i]];
            continue;
        }
        if (dynamic_cast<Grep*>((*blocks)[(*order)[i]])) {
            text = dynamic_cast<Grep*>((*blocks)[(*order)[i]])->task(text);
            delete (*blocks)[(*order)[i]];
            continue;
        }
        if (dynamic_cast<Sort*>((*blocks)[(*order)[i]])) {
            text = dynamic_cast<Sort*>((*blocks)[(*order)[i]])->task(text);
            delete (*blocks)[(*order)[i]];
            continue;
        }
        if (dynamic_cast<Dump*>((*blocks)[(*order)[i]])) {
            text = dynamic_cast<Dump*>((*blocks)[(*order)[i]])->task(text);
            delete (*blocks)[(*order)[i]];
            continue;
        }
        if (dynamic_cast<ReadFile*>((*blocks)[(*order)[i]])) {
            text = dynamic_cast<ReadFile*>((*blocks)[(*order)[i]])->task(text);
            delete (*blocks)[(*order)[i]];
            continue;
        }
        if (dynamic_cast<WriteFile*>((*blocks)[(*order)[i]])) {
            text = dynamic_cast<WriteFile*>((*blocks)[(*order)[i]])->task(text);
            delete (*blocks)[(*order)[i]];
            continue;
        }
    }
    if (commandLineO) {
        text = WriteFile(outPath).task(text);
    }
}