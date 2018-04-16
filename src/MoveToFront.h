#pragma once
#include <string>
#include <vector>

using namespace std;

class MoveToFront {
private:
    string decoded_data;
    vector<unsigned char> encoded_data;
    string initial_alphabet;
    string alphabet;

    void ReadDecodedDataFromFile(string filename);
    void WriteEncodedDataToFile(string filename);
    void ReadEncodedDataFromFile(string filename);
    void WriteDecodedDataToFile(string filename);
    unsigned int IndexOfChar(char c);
    void MoveCharToFront(unsigned int index);

public:
    MoveToFront(const string& alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789,.?!;:");
    void Encode(const string& input_file, const string& output_file);
    void Decode(const string& input_file, const string& output_file);
};