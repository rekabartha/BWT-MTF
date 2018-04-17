#include <algorithm>
#include "MoveToFront.h"
#include "Commons.h"

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
    ReadDataFromFile(input_file, decoded_data);
    alphabet = initial_alphabet;
    auto length = decoded_data.size();
    encoded_data.resize(length);

    for (auto i = 0; i < length; i++)
    {
        auto index = IndexOfChar(decoded_data[i]);
        encoded_data[i] = index;
        MoveCharToFront(index);
    }

    WriteDataToFile(output_file, encoded_data);
}

void MoveToFront::Decode(const string& input_file, const string& output_file)
{
    ReadDataFromFile(input_file, encoded_data);
    alphabet = initial_alphabet;
    auto length = encoded_data.size();
    decoded_data.resize(length);

    for (auto i = 0; i < length; i++)
    {
        auto index = encoded_data[i];
        decoded_data[i] = alphabet[index];
        MoveCharToFront(index);
    }

    WriteDataToFile(output_file, decoded_data);
}
