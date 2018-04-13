#pragma once
#include <string>

#include <vector>

using namespace std;

class MoveToFront {
private:
    string input;
    vector<unsigned int> output;
    string alphabet;

    unsigned int IndexOfChar(char c);
    void MoveCharToFront(unsigned int index);
    
public:
    MoveToFront(const string& input, const string& alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789,.?!;:");
    vector<unsigned int> GetTransformedInput();
};