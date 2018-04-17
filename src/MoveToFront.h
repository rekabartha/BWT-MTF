#pragma once
#include <string>
#include <vector>

using namespace std;

class MoveToFront {
private:
    vector<unsigned char> decoded_data;
    vector<unsigned char> encoded_data;
    string initial_alphabet;
    string alphabet;

    unsigned int IndexOfChar(char c);
    void MoveCharToFront(unsigned int index);

public:
	MoveToFront(const string& alphabet = "\1abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 \r\n\t,.?!;:'&#()*[]\"-\\$%\'+-/<>=@^_|~") : initial_alphabet(alphabet) {}
    void Encode(const string& input_file, const string& output_file);
    void Decode(const string& input_file, const string& output_file);
};