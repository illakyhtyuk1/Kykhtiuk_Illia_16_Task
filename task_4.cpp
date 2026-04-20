#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

vector<string> splitWords(const string& sentence) {
    vector<string> words;
    stringstream ss(sentence);
    string word;
    while (ss >> word) {
        if (!word.empty() && word.back() == '.') {
            word.pop_back();
        }
        words.push_back(word);
    }
    return words;
}

string mergeSentences(const string& s1, const string& s2) {
    vector<string> words1 = splitWords(s1);
    vector<string> words2 = splitWords(s2);
    string result = "";
    size_t i = 0;

    while (i < words1.size() || i < words2.size()) {
        if (i < words1.size()) {
            result += words1[i] + " ";
        }
        if (i < words2.size()) {
            result += words2[i] + " ";
        }
        i++;
    }

    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }
    result += ".";
    return result;
}

int main() {
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");

    if (!inputFile.is_open()) {
        cerr << "Error: Could not open input.txt" << endl;
        return 1;
    }

    vector<string> sentences;
    string line;

    while (getline(inputFile, line)) {
        if (!line.empty()) {
            sentences.push_back(line);
        }
    }
    inputFile.close();

    int n = sentences.size();
    vector<string> processedSentences;

    for (int i = 0; i < n / 2; ++i) {
        string merged = mergeSentences(sentences[i], sentences[n - 1 - i]);
        processedSentences.push_back(merged);
    }

    if (n % 2 != 0) {
        processedSentences.push_back(sentences[n / 2]);
    }

    for (const auto& s : processedSentences) {
        outputFile << s << endl;
    }

    outputFile.close();
    cout << "Processing complete. Check output.txt" << endl;

    return 0;
}
