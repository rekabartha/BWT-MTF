#include "BurrowsWheeler.h"
#include <algorithm>
#include <set>
#include <map>
#include <fstream>

bool Compare(const BurrowsWheeler::Rotation& r1, const BurrowsWheeler::Rotation& r2)
{
    return r1.GetSuffix() < r2.GetSuffix();
}

int BurrowsWheeler::Rotation::GetIndex() const
{
    return index;
}

void BurrowsWheeler::Rotation::SetIndex(int index)
{
    this->index = index;
}

string_view BurrowsWheeler::Rotation::GetSuffix() const
{
    return suffix;
}

void BurrowsWheeler::Rotation::SetSuffix(const string_view& suffix)
{
    this->suffix = suffix;
}

vector<int> BurrowsWheeler::GetSuffixVector()
{
    auto length = input.length();
    vector<Rotation> suffixes(length);

    for (size_t i = 0; i < length; i++)
    {
        suffixes[i].SetIndex((int)i);
        suffixes[i].SetSuffix(string_view(input).substr(i, length - i));
    }

    sort(suffixes.begin(), suffixes.end(), Compare);

    vector<int> suff_indexes;

    for (size_t i = 0; i < length; i++)
    {
        if ((string)suffixes[i].GetSuffix() == input)
            index = i;
        suff_indexes.push_back(suffixes[i].GetIndex());
    }

    return suff_indexes;
}

string BurrowsWheeler::GetLastColumn(const vector<int>& suff_indexes)
{
    auto length = suff_indexes.size();
    string result;

    for (size_t i = 0; i < length; i++)
    {
        int j = suff_indexes[i] - 1;
        if (j < 0)
            j += length;

        result += input.substr(j, 1);
    }

    return result;
}

void BurrowsWheeler::Encode(const string& input_filename, const string& output_filename)
{
    ifstream f(input_filename);
    f >> this->input;
    f.close();
    this->index = -1;
    ofstream g(output_filename);
    g << GetLastColumn(GetSuffixVector());
    g.close();
}

void BurrowsWheeler::Decode(const string& input_filename, const string& output_filename)
{
    string encoded_input;
    ifstream f(input_filename);
    f >> encoded_input;
    f.close();

    auto length = input.length();
    string sorted = encoded_input;
    sort(sorted.begin(), sorted.end());

    set<char> unique(sorted.begin(), sorted.end());
    map< char, vector<int> > map_of_indexes;

    for (auto element : unique)
        map_of_indexes.insert(pair< char, vector<int> >(element, NULL));

    for (size_t i = 0; i < length; i++)
        map_of_indexes[encoded_input[i]].push_back(i);

    vector<int> l_shift;

    for (auto element : map_of_indexes)
        for (auto value : element.second)
            l_shift.push_back(value);

    string result;
    int x = index;

    for (size_t i = 0; i < length; i++)
    {
        x = l_shift[x];
        result += encoded_input[x];
    }

    ofstream g(output_filename);
    g << result;
    g.close();
}