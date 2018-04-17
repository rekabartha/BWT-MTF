#pragma once
#include <string_view>
#include <string>
#include <vector>
using namespace std;

class BurrowsWheeler
{
    string input;
    int index;

    class Rotation
    {
    public:
        int index;
        string_view suffix;
    };

    vector<int> GetSuffixVector();
    string GetLastColumn(const vector<int>&);

public:
    friend bool Compare(const Rotation&, const Rotation&);
    void Encode(const string&, const string&);
    void Decode(const string&, const string&);
};