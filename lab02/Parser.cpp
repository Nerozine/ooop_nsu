#include "Parser.h"


std::vector<std::string>* Parser::readWorkflow(std::ifstream &workflow) {
    // returns vector, which contains commands in 0 -- n-2 idxs and order (as a non parsed string) in n-1 idx;
    using namespace std;
    auto* lines = new vector<string>();
    vector<int> order;

    try {
        if (!workflow.is_open()) {
            throw invalid_argument("can't open workflow file");
        }
        if (workflow.eof()) {
            throw invalid_argument("empty workflow file");
        }

        string tmp;
        getline(workflow, tmp);

        if (tmp != "desc") {
            throw invalid_argument("invalid format: first line must be desc");
        }

        tmp.clear();

        while(tmp != "csed") {
            tmp.clear();
            getline(workflow, tmp);
            lines->emplace_back(tmp);

            if (workflow.eof()) {
                throw invalid_argument("invalid format: no csed");
            }
        }

        lines->pop_back();
        if (lines->empty()) {
            throw invalid_argument("no commands in workflow");
        }

        tmp.clear();
        getline(workflow, tmp);
        regex rx("^([1-9][0-9]*|0)((\\s->\\s([1-9][0-9]*|0))*)(\\s->\\s([1-9][0-9]*|0))$");
        if (!regex_match(tmp, rx)) {
            throw invalid_argument("incorrect order format in workflow");
        }
        lines->emplace_back(tmp);
    }
    catch(invalid_argument& i) {
        cerr << i.what() << endl;
        exit(0);
    }

    return lines;
}


std::vector<int>* Parser::getOrder(std::vector<std::string> *lines) {
    using namespace std;
    auto* parsedOrder = new vector<int>();

    stringstream s(lines->at(lines->size() - 1));
    string tmp;
    int number = 0;

    while (!s.eof()) {
        s >> number;
        parsedOrder->push_back(number);
        s >> tmp;
    }

    lines->pop_back();

    return parsedOrder;
}



std::map<int, IWorker*>* Parser::parseBlocks(std::vector<std::string> *commands) {
    using namespace std;
    // only parsing commands
    map<int, IWorker*>* parsedCommands = new map<int, IWorker*>();
    try {
        int number;
        string commandName;
        for (int i = 0; i < commands->size(); i++) {
            commandName.clear();
            stringstream s((*commands)[i]);
            s >> number >> commandName >> commandName; // n = commandname...
            if (commandName == "readfile") {
                string inPath;
                s >> inPath;
                ReadFile *r = new ReadFile(inPath);
                parsedCommands->insert(make_pair(number, r));
                continue;
            }
            if (commandName == "writefile") {
                string outPath;
                s >> outPath;
                WriteFile *w = new WriteFile(outPath);
                parsedCommands->insert(make_pair(number, w));
                continue;
            }
            if (commandName == "grep") {
                string word;
                s >> word;
                Grep *g = new Grep(word);
                parsedCommands->insert(make_pair(number, g));
                continue;
            }
            if (commandName == "sort") {
                Sort *ss = new Sort();
                parsedCommands->insert(make_pair(number, ss));
                continue;
            }
            if (commandName == "replace") {
                string a, b;
                s >> a >> b;
                Replace *r = new Replace(a,b);
                parsedCommands->insert(make_pair(number, r));
                continue;
            }
            if (commandName == "dump") {
                string outPath;
                s >> outPath;
                Dump *d = new Dump(outPath);
                parsedCommands->insert(make_pair(number, d));
                continue;
            }
        }
    }
    catch (invalid_argument &a){
        cerr << a.what() << endl;
        exit(0);
    }
    return parsedCommands;
}