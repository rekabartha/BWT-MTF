#pragma once
#include <string>
#include <vector>

using namespace std;

class MoveToFront {
private:
    vector<unsigned char> decoded_data;
    vector<unsigned char> encoded_data;
	vector<unsigned char> alphabet;

	void InitializeAlphabet();
    size_t IndexOfChar(unsigned char c);
    void MoveCharToFront(size_t index);

public:
    void Encode(const string& input_file, const string& output_file);
    void Decode(const string& input_file, const string& output_file);
};