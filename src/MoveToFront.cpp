#include "Commons.h"
#include "MoveToFront.h"
#include <algorithm>

void MoveToFront::InitializeAlphabet()
{
    alphabet.clear();
    for (unsigned char i = 0; i < 253; i++)
        alphabet.push_back(i);
}

size_t MoveToFront::IndexOfChar(unsigned char c)
{
    size_t length = alphabet.size();

    for (size_t i = 0; i < length; i++)
        if (c == alphabet[i])
            return i;

    throw exception("Character not found in the alphabet.");
}

void MoveToFront::MoveCharToFront(size_t index)
{
    auto first = alphabet.begin();
    auto middle = alphabet.begin() + index;
    auto last = next(alphabet.begin() + index);
    rotate(first, middle, last);
}

void MoveToFront::Encode(const string& input_file, const string& output_file)
{
    ReadDataFromFile(input_file, decoded_data);
    InitializeAlphabet();
    size_t length = decoded_data.size();
    encoded_data.resize(length);

    for (size_t i = 0; i < length; i++)
    {
        size_t index = IndexOfChar(decoded_data[i]);
        encoded_data[i] = (unsigned char)index;
        MoveCharToFront(index);
    }

    WriteDataToFile(output_file, encoded_data);
}

void MoveToFront::Decode(const string& input_file, const string& output_file)
{
    ReadDataFromFile(input_file, encoded_data);
    InitializeAlphabet();
    size_t length = encoded_data.size();
    decoded_data.resize(length);

    for (size_t i = 0; i < length; i++)
    {
        size_t index = encoded_data[i];
        decoded_data[i] = alphabet[index];
        MoveCharToFront(index);
    }

    WriteDataToFile(output_file, decoded_data);
}
