#pragma once
#include <string>
#include <vector>
#include <string_view>

using namespace std;

class BurrowsWheeler
{
	class Rotation
	{
	public:
		size_t index;
		string_view suffix;
	};

	size_t index;
    string input;

    vector<size_t> GetSuffixVector();
    string GetLastColumn(const vector<size_t>&);
	friend bool Compare(const Rotation&, const Rotation&);

public:
    void Encode(const string&, const string&);
    void Decode(const string&, const string&);
};