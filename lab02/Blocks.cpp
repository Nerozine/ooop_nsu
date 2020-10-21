#include "Blocks.h"


IWorker::~IWorker() {}


ReadFile::ReadFile(std::string &inPath) : input(inPath) {}


std::vector<std::string>* ReadFile::task(std::vector<std::string>* text) {
    using namespace std;
    try {
        if (!input.is_open()) {
            throw invalid_argument("can't open output");
        }
        text = new vector<string>;
        string buf;
        while (!input.eof()) {
            buf.clear();
            getline(input, buf);
            text->emplace_back(buf);
        }
    }
    catch (invalid_argument& ia){
        cerr << ia.what() << endl;
        exit(0);
    }
    return text;
}


ReadFile::~ReadFile() {
    input.close();
}


WriteFile::WriteFile(std::string &outPath) : output(outPath) {}


std::vector<std::string> *WriteFile::task(std::vector<std::string>* text) {
    using namespace std;
    try {
        if (!output.is_open()) {
            throw invalid_argument("can't open output");
        }
        for (int i = 0; i < text->size(); i++) {
            output << (*text)[i] << endl;
        }
    }
    catch (invalid_argument& ia) {
        cerr << ia.what() << endl;
        exit(0);
    }
    delete text;
    text = nullptr;
    return text;
}


WriteFile::~WriteFile() {
    output.close();
}


std::vector<std::string> *Sort::task(std::vector<std::string> *text) {
    std::sort(text->begin(), text->end());
    return text;
}


Replace::Replace(std::string &oldW, std::string &newW) : oldWord(oldW), newWord(newW) {}


std::vector<std::string> *Replace::task(std::vector<std::string> *text) {
    using namespace std;
    regex rx(oldWord);
    for (int i = 0 ; i < text->size(); i++) {
        (*text)[i] = regex_replace((*text)[i], rx, newWord);
    }
    return text;
}

Dump::Dump(std::string &outPath) : output(outPath) {}


std::vector<std::string> *Dump::task(std::vector<std::string> *text) {
    using namespace std;
    try {
        if (!output.is_open()) {
            throw invalid_argument("can't open output for grep");
        }
        for (int i = 0; i < text->size(); i++) {
            output << (*text)[i] << endl;
        }
    }
    catch(invalid_argument& ia) {
        cerr << ia.what() << endl;
        exit(0);
    }
    return text;
}


Grep::Grep(std::string &word) : word(word) {}


std::vector<std::string> *Grep::task(std::vector<std::string> *text) {
    using namespace std;
    auto* newText = new vector<string>;
    regex rx(word);
    for (int i = 0; i < text->size(); i++) {
        if (regex_search((*text)[i], rx)) {
            newText->emplace_back((*text)[i]);
        }
    }
    delete text;
    text = nullptr;
    return newText;
}