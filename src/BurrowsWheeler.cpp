#include "BurrowsWheeler.h"
#include <algorithm>

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

BurrowsWheeler::BurrowsWheeler(const string& input)
{
    this->input = input;
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

    for (auto rotation : suffixes)
        suff_indexes.push_back(rotation.GetIndex());

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

string BurrowsWheeler::GetTransformedInput()
{
    return GetLastColumn(GetSuffixVector());
}