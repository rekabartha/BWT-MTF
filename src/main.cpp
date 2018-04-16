#include "BurrowsWheeler.h"
#include <iostream>

int main()
{
    BurrowsWheeler burrows_wheeler("banana#");
    cout << burrows_wheeler.GetTransformedInput() << endl;

    return 0;
}