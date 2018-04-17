#include "BurrowsWheeler.h"
#include <iostream>
#include <chrono>

int main()
{
    BurrowsWheeler burrows_wheeler;
    string input = "input.txt";
    string output_transform = "encoded_input.txt";
    string output_invert = "inverted_transform.txt";

    cout << "Starting to read ..." << endl;
    auto t1 = std::chrono::high_resolution_clock::now();
    burrows_wheeler.Encode(input, output_transform);
    auto t2 = std::chrono::high_resolution_clock::now();
    cout << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() / 1000.0 << endl;
    cout << "Encoding done!\nStarting to decode ..." << endl;
    burrows_wheeler.Decode(output_transform, output_invert);
    cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - t2).count() / 1000.0 << endl;
    cout << "Decoding done!\n";

    return 0;
}