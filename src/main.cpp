#include "Huffman.h"
#include "MoveToFront.h"
#include "BurrowsWheeler.h"
#include <iostream>
#include <chrono>

using namespace std;

int main() {
    BurrowsWheeler bwt;
    MoveToFront mtf;
    Huffman h;

	auto start = chrono::high_resolution_clock::now();
    cout << "BWT encoding...\n";
    bwt.Encode("large_input.txt", "bwtencoded");
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
	auto stop = chrono::high_resolution_clock::now();
	cout << chrono::duration_cast<chrono::milliseconds>(stop - start).count() / 1000.0 << endl;

    return 0;
}