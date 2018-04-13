#include <algorithm>
#include "MoveToFront.h"

MoveToFront::MoveToFront(const string & alphabet) : initial_alphabet(alphabet)
{
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

vector<unsigned int> MoveToFront::encode(string input)
{
    alphabet = initial_alphabet;
    auto length = input.size();
    vector<unsigned int> output(length);

    for (auto i = 0; i < length; i++)
    {
        auto index = IndexOfChar(input[i]);
        output[i] = index;
        MoveCharToFront(index);
    }

    return output;
}
string MoveToFront::decode(vector<unsigned int> input)
{
    alphabet = initial_alphabet;
    auto length = input.size();
    string output(length, '0');

    for (auto i = 0; i < length; i++)
    {
        auto index = input[i];
        output[i] = alphabet[index];
        MoveCharToFront(index);
    }

    return output;
}
