#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <map>
#include <cmath>


bool isSuitableSym(char symbol) {
    return isalpha(symbol) || isdigit(symbol);
}


int splitLine(const std::string& line, std::map <std::string, int>& myMap)  {

    using namespace std;

    int countWordInLine = 0;
    int startPosSubStr = 0;
    bool isSubStr = false;
    string word;

    for (int i = 0; i < line.length(); i++) {
        if (isSuitableSym(line[i])) {
            if (!isSubStr) {
                startPosSubStr = i;
            }
            isSubStr = true;
        }
        else if (isSubStr) {
            word = line.substr(startPosSubStr, i - startPosSubStr);
            myMap[word]++;
            word.clear();
            isSubStr = false;
            countWordInLine++;
        }
    }

    if (isSubStr) {
        word = line.substr(startPosSubStr, line.length() - startPosSubStr);
        myMap[word]++;
        countWordInLine++;
    }

    return countWordInLine;
}


std::list <std::pair<std::string, int>> createList(std::map<std::string, int>& myMap) {

    using namespace std;

    list <pair <string, int>> myList;

    for (int size = myMap.size(); size > 0; size--) {
        int maxValue = 0;
        string mostFreqStr;

        for (auto& it : myMap) {
            if (it.second > maxValue) {
                maxValue = it.second;
                mostFreqStr = it.first;
            }
        }

        myList.emplace_back(make_pair(mostFreqStr, maxValue));
        myMap.erase(mostFreqStr);
    }

    return myList;
}


void writeTable(const std::list <std::pair <std::string, int>>& myList, std::ofstream& out, long long totalWords) {

    using namespace std;

    out << "word" <<  ","
        << "frequency" << ","
        << "frequency(in%)" << endl;

    for (auto& it : myList) {
        double freqInPercent = static_cast<double>(it.second) / static_cast<double>(totalWords);
        out << it.first << ","
            << it.second << ","
            << round(freqInPercent * 100) << endl;
    }
}


int main(int argc, char* argv[]) {

    if (argc != 3) {
        std::cout << "Wrong number of parameters" << std::endl;
        return 0;
    }

    std::ifstream in;
    in.open(argv[1]);
    if (!in.is_open()){
        // Error opening input
        std::cout << "Error while opening input file: " << argv[1] << std::endl;
        return 0;
    }

    std::ofstream out;
    out.open(argv[2]);
    if (!out.is_open()) {
        // Error opening output
        std::cout << "Error while opening output file: " << argv[2] << std::endl;
        return 0;
    }

    std::map <std::string, int> myMap;
    long long totalWords = 0;

    while (true) {
        if (in.eof()) {
            break;
        }

        std::string line;
        getline(in, line);
        totalWords += splitLine(line, myMap);
    }

    in.close();

    std::list <std::pair<std::string, int>> myList = createList(myMap);
    writeTable(myList, out, totalWords);

    myList.clear();
    out.close();

    return 0;
}
