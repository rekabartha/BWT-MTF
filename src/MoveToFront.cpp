#include <algorithm>
#include "MoveToFront.h"

MoveToFront::MoveToFront(const string & input, const string & alphabet) : input(input), alphabet(alphabet), output(input.length())
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

vector<unsigned int> MoveToFront::GetTransformedInput()
{
    auto length = output.size();

    for (auto i = 0; i < length; i++)
    {
        auto index = IndexOfChar(input[i]);
        output[i] = index;
        MoveCharToFront(index);
    }

    return output;
}
