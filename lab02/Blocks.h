#ifndef OOOP_NSU_IWORKER_H
#define OOOP_NSU_IWORKER_H
#include <vector>
#include <iostream>
#include <fstream>
#include <regex>
#include <map>


class IWorker {
public:
    virtual std::vector<std::string>* task(std::vector<std::string>* text) = 0;
    virtual ~IWorker();
};

class ReadFile : public IWorker {
private:
    std::ifstream input;
public:
    explicit ReadFile(std::string &inPath);
    virtual std::vector<std::string>* task(std::vector<std::string>* text) override;
    ~ReadFile() override;
};

class WriteFile : public IWorker {
private:
    std::ofstream output;
public:
    explicit WriteFile(std::string &outPath);
    virtual std::vector<std::string>* task(std::vector<std::string>* text) override;
    ~WriteFile() override;
};

class Grep : public IWorker {
private:
    std::string word;
public:
    explicit Grep(std::string& word);
    virtual std::vector<std::string>* task(std::vector<std::string>* text) override;
};

class Sort : public IWorker {
public:
    virtual std::vector<std::string>* task(std::vector<std::string>* text) override;
};

class Replace : public IWorker {
private:
    std::string oldWord;
    std::string newWord;
public:
    explicit Replace(std::string &oldW, std::string &newW);
    virtual std::vector<std::string>* task(std::vector<std::string>* text) override;
};

class Dump : public IWorker {
private:
    std::ofstream output;
public:
    explicit Dump(std::string &outPath);
    virtual std::vector<std::string>* task(std::vector<std::string>* text) override;
};

#endif //OOOP_NSU_IWORKER_H
