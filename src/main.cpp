#include "Huffman.h"
#include "MoveToFront.h"
#include "BurrowsWheeler.h"
#include <iostream>
#include <iomanip>
#include <chrono>

using namespace std;

string BWT_Encode(BurrowsWheeler& bwt, const string& input)
{
    cout << "\nBWT encoding... ";
    cout << setw(10);
    bwt.Encode(input, "bwtencoded");

    return "bwtencoded";
}

string MTF_Encode(MoveToFront& mtf, const string& input)
{
    cout << "MTF encoding... ";
    cout << setw(10);
    mtf.Encode(input, "mtfencoded");

    return "mtfencoded";
}

string Huffman_Encode(Huffman& h, const string& input)
{
    cout << "Huffman encoding... ";
    cout << setw(6);
    h.Encode(input, "hencoded");

    return "hencoded";
}

void Opt1_Encode(BurrowsWheeler& bwt, Huffman& h, const string& input)
{
    auto start = chrono::high_resolution_clock::now();

    string output = BWT_Encode(bwt, input);
    auto bwt_encoded = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(bwt_encoded - start).count() / 1000.0 << " s" << endl;

    Huffman_Encode(h, output);
    auto huffman_encoded = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(huffman_encoded - bwt_encoded).count() / 1000.0 << " s" << endl;

    cout << "Total time: ";
    cout << setw(14);
    cout << chrono::duration_cast<chrono::milliseconds>(huffman_encoded - start).count() / 1000.0 << " s" << endl;
}

void Opt2_Encode(MoveToFront& mtf, Huffman& h, const string& input)
{
    auto start = chrono::high_resolution_clock::now();

    string output = MTF_Encode(mtf, input);
    auto mtf_encoded = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(mtf_encoded - start).count() / 1000.0 << " s" << endl;

    Huffman_Encode(h, output);
    auto huffman_encoded = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(huffman_encoded - mtf_encoded).count() / 1000.0 << " s" << endl;

    cout << "Total time: ";
    cout << setw(14);
    cout << chrono::duration_cast<chrono::milliseconds>(huffman_encoded - start).count() / 1000.0 << " s" << endl;
}

void Opt3_Encode(BurrowsWheeler& bwt, MoveToFront& mtf, Huffman& h, const string& input)
{
    auto start = chrono::high_resolution_clock::now();

    string output = BWT_Encode(bwt, input);
    auto bwt_encoded = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(bwt_encoded - start).count() / 1000.0 << " s" << endl;

    output = MTF_Encode(mtf, output);
    auto mtf_encoded = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(mtf_encoded - bwt_encoded).count() / 1000.0 << " s" << endl;

    Huffman_Encode(h, output);
    auto huffman_encoded = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(huffman_encoded - mtf_encoded).count() / 1000.0 << " s" << endl;

    cout << "Total time: ";
    cout << setw(14);
    cout << chrono::duration_cast<chrono::milliseconds>(huffman_encoded - start).count() / 1000.0 << " s" << endl;
}

void Opt4_Encode(Huffman& h, const string& input)
{
    auto start = chrono::high_resolution_clock::now();

    Huffman_Encode(h, input);
    auto huffman_encoded = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(huffman_encoded - start).count() / 1000.0 << " s" << endl;

    cout << "Total time: ";
    cout << setw(14);
    cout << chrono::duration_cast<chrono::milliseconds>(huffman_encoded - start).count() / 1000.0 << " s" << endl;
}

string BWT_Decode(BurrowsWheeler& bwt, const string& input)
{
    cout << "BWT decoding... ";
    cout << setw(10);
    bwt.Decode(input, "bwtdecoded");

    return "bwtdecoded";
}

string MTF_Decode(MoveToFront& mtf, const string& input)
{
    cout << "MTF decoding... ";
    cout << setw(10);
    mtf.Decode(input, "mtfdecoded");

    return "mtfdecoded";
}

string Huffman_Decode(Huffman& h, const string& input)
{
    cout << "Huffman decoding... ";
    cout << setw(6);
    h.Decode(input, "hdecoded");

    return "hdecoded";
}

void Opt1_Decode(BurrowsWheeler& bwt, Huffman& h, const string& input)
{
    auto start = chrono::high_resolution_clock::now();

    string output = Huffman_Decode(h, input);
    auto huffman_decoded = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(huffman_decoded - start).count() / 1000.0 << " s" << endl;

    BWT_Decode(bwt, output);
    auto bwt_decoded = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(bwt_decoded - huffman_decoded).count() / 1000.0 << " s" << endl;
}

void Opt2_Decode(MoveToFront& mtf, Huffman& h, const string& input)
{
    auto start = chrono::high_resolution_clock::now();

    string output = Huffman_Decode(h, input);
    auto huffman_decoded = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(huffman_decoded - start).count() / 1000.0 << " s" << endl;

    MTF_Decode(mtf, output);
    auto mtf_decoded = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(mtf_decoded - huffman_decoded).count() / 1000.0 << " s" << endl;

}

void Opt3_Decode(BurrowsWheeler& bwt, MoveToFront& mtf, Huffman& h, const string& input)
{
    auto start = chrono::high_resolution_clock::now();

    string output = Huffman_Decode(h, input);
    auto huffman_decoded = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(huffman_decoded - start).count() / 1000.0 << " s" << endl;

    output = MTF_Decode(mtf, output);
    auto mtf_decoded = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(mtf_decoded - huffman_decoded).count() / 1000.0 << " s" << endl;

    BWT_Decode(bwt, output);
    auto bwt_decoded = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(bwt_decoded - mtf_decoded).count() / 1000.0 << " s" << endl;
}

void Opt4_Decode(Huffman& h, const string& input)
{
    auto start = chrono::high_resolution_clock::now();
    Huffman_Decode(h, input);
    auto huffman_decoded = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(huffman_decoded - start).count() / 1000.0 << " s" << endl;
}

void Menu()
{
    BurrowsWheeler bwt;
    MoveToFront mtf;
    Huffman h;

    int option_1, option_2;
    string input;
    cout << "Please select your intent of use!\n1. Encode text file\n2. Decode text file\n";
    cin >> option_1;

    cout << "\nWhich transform(s) to use?\n(In case of decoding, please select the option which was used in the encoding phase)\n\n";
    cout << "1. Burrows-Wheeler\n2. Move to front\n3. Burrows-Wheeler & Move to front\n4. None of the above\n";
    cin >> option_2;

    switch (option_1)
    {
    case 1:
        cout << "Please specify the file name: ";
        cin >> input;
        switch (option_2)
        {
        case 1:
            Opt1_Encode(bwt, h, input);
            break;
        case 2:
            Opt2_Encode(mtf, h, input);
            break;
        case 3:
            Opt3_Encode(bwt, mtf, h, input);
            break;
        case 4:
            Opt4_Encode(h, input);
            break;
        default:
            break;
        }
        break;
    case 2:
        cout << "Please specify the file name: ";
        cin >> input;
        switch (option_2)
        {
        case 1:
            Opt1_Decode(bwt, h, input);
            break;
        case 2:
            Opt2_Decode(mtf, h, input);
            break;
        case 3:
            Opt3_Decode(bwt, mtf, h, input);
            break;
        case 4:
            Opt4_Decode(h, input);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

int main() {

    Menu();

    return 0;
}