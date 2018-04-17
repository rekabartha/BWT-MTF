#include <iostream>
#include <fstream>
#include "MoveToFront.h"
#include "Huffman.h"
#include "BurrowsWheeler.h"

using namespace std;

int main() {
    BurrowsWheeler bwt;
    MoveToFront mtf;
    Huffman h;

    cout << "BWT encoding...\n";
    bwt.Encode("input.txt", "bwtencoded");
    cout << "MTF encoding...\n";
    mtf.Encode("bwtencoded", "mtfencoded");
    cout << "Huffman encoding...\n";
    h.Encode("mtfencoded", "hencoded");
    cout << "Huffman decoding...\n";
    h.Decode("hencoded", "hdecoded");
    cout << "MTF decoding...\n";
    mtf.Decode("hdecoded", "mtfdecoded");
    cout << "BWT decoding...\n";
    bwt.Decode("mtfdecoded", "output.txt");

    return 0;
}