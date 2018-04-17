#include "BurrowsWheeler.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <omp.h>
#include <map>

bool Compare(const BurrowsWheeler::Rotation& r1, const BurrowsWheeler::Rotation& r2)
{
    return r1.suffix < r2.suffix;
}

vector<int> BurrowsWheeler::GetSuffixVector()
{
    int length = input.length();
    vector<Rotation> suffixes(length);

    string_view text = string_view(input);

#pragma omp parallel for
    for (int i = 0; i < length; i++)
    {
        suffixes[i].index = i;
        suffixes[i].suffix = text.substr(i, length - i);
    }

    sort(suffixes.begin(), suffixes.end(), Compare);

    vector<int> suff_indexes(length);

#pragma omp parallel for
    for (int i = 0; i < length; i++)
    {
        if (suffixes[i].suffix == input)
            index = i;
        suff_indexes[i] = suffixes[i].index;
    }

    return suff_indexes;
}

string BurrowsWheeler::GetLastColumn(const vector<int>& suff_indexes)
{
    int length = suff_indexes.size();
    string result;
    vector<char> characters(length);

#pragma omp parallel for
    for (int i = 0; i < length; i++)
    {
        int j = suff_indexes[i] - 1;
        if (j < 0)
            j += length;

        characters[i] = input[j];
    }

    for (int i = 0; i < length; i++)
        result += characters[i];

    return result;
}

void BurrowsWheeler::Encode(const string& input_filename, const string& output_filename)
{
    ifstream f(input_filename);
/*    copy_n(istreambuf_iterator<char>(f.rdbuf()), 900000, back_inserter(this->input));*/
    this->input.assign(istreambuf_iterator<char>(f), istreambuf_iterator<char>());
    f.close();
    this->input.push_back(0);
    cout << "Starting to encode ..." << endl;

    this->index = -1;
    ofstream g(output_filename);
    g << GetLastColumn(GetSuffixVector());
    g.close();
}

void BurrowsWheeler::Decode(const string& input_filename, const string& output_filename)
{
    string encoded_input;
    ifstream f(input_filename);
    encoded_input.assign(istreambuf_iterator<char>(f), istreambuf_iterator<char>());
    f.close();

    auto length = input.length();
    string sorted = encoded_input;
    sort(sorted.begin(), sorted.end());

    auto it = unique(sorted.begin(), sorted.end());
    sorted.erase(distance(sorted.begin(), it));

    map< char, vector<int> > map_of_indexes;

    for (size_t i = 0; i < sorted.length(); i++)
        map_of_indexes.insert(pair< char, vector<int> >(sorted[i], NULL));

    for (size_t i = 0; i < length; i++)
        map_of_indexes[encoded_input[i]].push_back(i);

    vector<int> l_shift;
    l_shift.reserve(length);

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

    result.pop_back();

    ofstream g(output_filename);
    g << result;
    g.close();
}