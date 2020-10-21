#include "Validator.h"


void Validator::workflowCommandsNumberIsCorrect(std::vector<std::string> *commands, std::vector<int> *order) {
    if (commands->size() != order->size()) {
        std::cerr << "the number of commands doesn't match the number of commands in the execution order" << endl;
        exit(0);
    }
}


void Validator::workflowNoRepeatsInOrder(std::vector<int> *parsedOrder) {
    using namespace std;
    map<int, int> test;
    for (int i = 0; i < parsedOrder->size(); i++) {
        if (test[(*parsedOrder)[i]] != 0) {
            cerr << "commands in order of execution are repeated" << endl;
            exit(0);
        }
        test[(*parsedOrder)[i]]++;
    }
}


void Validator::checkCommandSyntax(std::vector<std::string> *commands) {
    using namespace std;
    regex formOneArgRx("^(([1-9][0-9]*)|0)\\s=\\s(grep|readfile|writefile|dump)\\s(\\S+)$");
    regex formZeroArgRx("^(([1-9][0-9]*)|0)\\s=\\s(sort)$");
    regex formTwoArgRx("^(([1-9][0-9]*)|0)\\s=\\s(replace)\\s(\\S+)\\s(\\S+)$");
    try {
        for (int i = 0; i < commands->size(); i++) {
            if (!(regex_match((*commands)[i], formOneArgRx) || regex_match((*commands)[i], formTwoArgRx) ||
                    regex_match((*commands)[i], formZeroArgRx))) {
                throw invalid_argument("incorrect command syntax in workflow");
            }
        }
    }
    catch(invalid_argument& ia) {
        cerr << ia.what() << endl;
        exit(0);
    }
}


void Validator::checkConformityOrderCommands(std::map<int, IWorker*>* blocks, std::vector<int>* order) {
    using namespace std;
    try {
        for (int i = 0; i < order->size(); i++) {
            if (blocks->find((*order)[i]) == blocks->end()) {
                throw invalid_argument("no " + to_string((*order)[i]) + " found in workflow commands");
            }
        }
    }
    catch(invalid_argument& ia) {
        cerr << ia.what() << endl;
        exit(0);
    }
}


void Validator::checkInputOutput(std::map<int, IWorker*>* blocks, std::vector<int>* order,
        bool commandLineI, bool commandLineO) {
    using namespace std;
    try {
        if (!commandLineI) {
            if (!dynamic_cast<ReadFile *>((*blocks)[order->at(0)])) {
                throw invalid_argument("first command must be readfile");
            }
        }
        if (!commandLineO) {
            if (!dynamic_cast<WriteFile *>((*blocks)[order->at(order->size() - 1)])) {
                throw invalid_argument("last command must be writefile");
            }
        }

        for (int i = 0; i < order->size() - 1; i++) {
            if (dynamic_cast<ReadFile *>((*blocks)[(*order)[i]])) {
                if (commandLineI) {
                    throw invalid_argument("readfile repeat at " + to_string((*order)[i]));
                }
                else {
                    commandLineI = true;
                }
            }
            if (dynamic_cast<WriteFile *>((*blocks)[(*order)[i]])) {
                if (commandLineO) {
                    throw invalid_argument("writefile repeat at " + to_string((*order)[i]));
                }
                else {
                    commandLineO = true;
                }
            }
        }
    }
    catch(invalid_argument& ia){
        cerr << ia.what() << endl;
        exit(0);
    }
}