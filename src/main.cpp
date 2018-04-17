#include <iostream>
#include <fstream>
#include "MoveToFront.h"
#include "Huffman.h"

using namespace std;

int main() {
    MoveToFront mtf;
    Huffman h;

    cout << "MTF encoding...\n";
    mtf.Encode("input.txt", "mtfencoded");
    cout << "Huffman encoding...\n";
    h.Encode("mtfencoded", "hencoded");
    cout << "Huffman decoding...\n";
    h.Decode("hencoded", "hdecoded");
    cout << "MTF decoding...\n";
    mtf.Decode("hdecoded", "output.txt");

    return 0;
}