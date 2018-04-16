#include <iostream>
#include <fstream>
#include "MoveToFront.h"
#include "Huffman.h"

using namespace std;

int main() {
    MoveToFront mtf;
    Huffman h;

    ofstream f("input.txt");
    f << "bananaaa";
    f.close();

    mtf.Encode("input.txt", "mtfencoded");
    h.Encode("mtfencoded", "hencoded");
    mtf.Decode("mtfencoded", "mtfdecoded.txt");

    return 0;
}