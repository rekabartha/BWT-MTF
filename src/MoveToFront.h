#pragma once
#include <string>

#include <vector>

using namespace std;

class MoveToFront {
private:
    string initial_alphabet;
    string alphabet;

    unsigned int IndexOfChar(char c);
    void MoveCharToFront(unsigned int index);

public:
    MoveToFront(const string& alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789,.?!;:");
    vector<unsigned int> encode(string input);
    string decode(vector<unsigned int> input);
};