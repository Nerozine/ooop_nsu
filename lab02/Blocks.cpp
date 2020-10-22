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
    regex rx_m("\\s" + oldWord + "\\s");
    regex rx_s("^(" + oldWord + "\\s)");
    regex rx_e("(\\s" + oldWord + ")$");
    for (int i = 0 ; i < text->size(); i++) {
        (*text)[i] = regex_replace((*text)[i], rx_m, " " + newWord + " ");
        (*text)[i] = regex_replace((*text)[i], rx_e, " " + newWord);
        (*text)[i] = regex_replace((*text)[i], rx_s, newWord + " ");
    }
    return text;
}

Dump::Dump(std::string &outPath) : output(outPath) {}


std::vector<std::string> *Dump::task(std::vector<std::string> *text) {
    using namespace std;
    try {
        if (!output.is_open()) {
            throw invalid_argument("can't open output for dump");
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
    regex rx_m("\\s" + word + "\\s");
    regex rx_s("^(" + word + "\\s)");
    regex rx_e("(\\s" + word + ")$");
    for (int i = 0; i < text->size(); i++) {
        if (regex_search((*text)[i], rx_m)) {
            newText->emplace_back((*text)[i]);
            continue;
        }
        if (regex_search((*text)[i], rx_s)) {
            newText->emplace_back((*text)[i]);
            continue;
        }
        if (regex_search((*text)[i], rx_e)) {
            newText->emplace_back((*text)[i]);
            continue;
        }
    }
    delete text;
    text = nullptr;
    return newText;
}