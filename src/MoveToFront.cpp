#include <algorithm>
#include <fstream>
#include "MoveToFront.h"

MoveToFront::MoveToFront(const string & alphabet) : initial_alphabet(alphabet)
{
}

void MoveToFront::ReadDecodedDataFromFile(string filename)
{
    ifstream fin(filename);
    fin >> decoded_data;
    fin.close();
}

void MoveToFront::WriteEncodedDataToFile(string filename)
{
    ofstream fout(filename, ios::out | ios::binary);
    fout.write(reinterpret_cast<const char*>(&encoded_data[0]), encoded_data.size() * sizeof(unsigned char));
    fout.close();
}

void MoveToFront::ReadEncodedDataFromFile(string filename)
{
    ifstream fin(filename, ios::out | ios::binary);
    fin.seekg(0, std::ios::beg);
    int start = fin.tellg();
    fin.seekg(0, std::ios::end);
    int stop = fin.tellg();
    fin.seekg(0, std::ios::beg);
    int size = stop - start;
    const size_t count = size;
    encoded_data.resize(count);
    fin.read(reinterpret_cast<char*>(&encoded_data[0]), count * sizeof(unsigned char));
    fin.close();
}

void MoveToFront::WriteDecodedDataToFile(string filename)
{
    ofstream fout(filename);
    fout << decoded_data;
    fout.close();
}

unsigned int MoveToFront::IndexOfChar(char c)
{
    auto length = alphabet.length();

    for (auto i = 0; i < length; i++)
    {
        if (c == alphabet[i]) return i;
    }

    throw exception("Character not found in the alphabet.");
}

void MoveToFront::MoveCharToFront(unsigned int index)
{
    auto first = alphabet.begin();
    auto middle = alphabet.begin() + index;
    auto last = next(alphabet.begin() + index);
    rotate(first, middle, last);
}

void MoveToFront::Encode(const string& input_file, const string& output_file)
{
    ReadDecodedDataFromFile(input_file);
    alphabet = initial_alphabet;
    auto length = decoded_data.size();
    encoded_data.resize(length);

    for (auto i = 0; i < length; i++)
    {
        auto index = IndexOfChar(decoded_data[i]);
        encoded_data[i] = index;
        MoveCharToFront(index);
    }

    WriteEncodedDataToFile(output_file);
}

void MoveToFront::Decode(const string& input_file, const string& output_file)
{
    ReadEncodedDataFromFile(input_file);
    alphabet = initial_alphabet;
    auto length = encoded_data.size();
    decoded_data.resize(length);

    for (auto i = 0; i < length; i++)
    {
        auto index = encoded_data[i];
        decoded_data[i] = alphabet[index];
        MoveCharToFront(index);
    }

    WriteDecodedDataToFile(output_file);
}
