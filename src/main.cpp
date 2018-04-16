#include "BurrowsWheeler.h"
#include <iostream>

int main()
{
    BurrowsWheeler burrows_wheeler;
    string input = "input.txt";
    string output_transform = "encoded_input.txt";
    string output_invert = "inverted_transform.txt";

    cout << "Starting to encode ..." << endl;
    burrows_wheeler.Encode(input, output_transform);
    cout << "Encoding done!\nStarting to decode ..." << endl;
    burrows_wheeler.Decode(output_transform, output_invert);
    cout << "Decoding done!\n";

    return 0;
}