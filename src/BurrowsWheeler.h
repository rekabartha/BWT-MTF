#pragma once
#include <string>
#include <string_view>
#include <vector>
using namespace std;

class BurrowsWheeler
{
    string input;

    class Rotation
    {
        int index;
        string_view suffix;

    public:
        int GetIndex() const;
        void SetIndex(int);
        string_view GetSuffix() const;
        void SetSuffix(const string_view&);
    };

    vector<int> GetSuffixVector();
    string GetLastColumn(const vector<int>&);

public:
    friend bool Compare(const Rotation&, const Rotation&);
    BurrowsWheeler(const string&);
    string GetTransformedInput();
};