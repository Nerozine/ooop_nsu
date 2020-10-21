#include "Parser.h"
#include "Validator.h"
#include "Blocks.h"
#include "Executor.h"


int main(int argc, char *argv[]) {
    using namespace std;
    ifstream workflow;
    bool commandLineI = false;
    bool commandLineO = false;
    string inPath;
    string outPath;

    try {
        if (argc < 2) {
            throw invalid_argument("too few command line parameters");
        }
        if (argc > 2) {
            if (argc > 6) {
                throw invalid_argument("too many command line parameters");
            }
            if (argc == 3 || argc == 5) {
                throw invalid_argument("incorrect amount of parameters");
            }
            if (string(argv[2]) != "-i" && string(argv[2]) != "-o") {
                throw invalid_argument("incorrect command line parametr on position 2: " + string(argv[2]));
            }
            else {
                if (string(argv[2]) == "-i") {
                    inPath = argv[3];
                    commandLineI = true;
                }
                else {
                    outPath = argv[3];
                    commandLineO = true;
                }
            }
            if (argc > 4) {
                if (string(argv[4]) != "-i" && string(argv[4]) != "-o") {
                    throw invalid_argument("incorrect command line parametr on position 2: " + string(argv[2]));
                }
                else {
                    if (string(argv[4]) == "-i") {
                        inPath = argv[5];
                        commandLineI = true;
                    }
                    else {
                        outPath = argv[5];
                        commandLineO = true;
                    }
                }
            }
        }
        workflow.open(argv[1]);
        if (workflow.peek() == ifstream::traits_type::eof()) {
            throw invalid_argument(string(argv[1]) +" is empty");
        }
    }
    catch(invalid_argument& ia) {
        cerr << ia.what() << endl;
        exit(0);
    }

    vector<string>* text = Parser::readWorkflow(workflow);
    vector<int>* order = Parser::getOrder(text);

    Validator::workflowCommandsNumberIsCorrect(text, order);
    Validator::workflowNoRepeatsInOrder(order);
    Validator::checkCommandSyntax(text);

    map<int, IWorker*>* blocks = Parser::parseBlocks(text, order);

    Validator::checkConformityOrderCommands(blocks, order);
    Validator::checkInputOutput(blocks, order, commandLineI, commandLineO);

    Executor::execute(blocks, order, commandLineI, commandLineO, inPath, outPath);

    delete order;
    delete text;
    delete blocks;
    workflow.close();
    return 0;
};