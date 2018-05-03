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

string Huffman_Encode(Huffman& h, const string& input, const string& original_input)
{
    cout << "Huffman encoding... ";
    cout << setw(6);
    h.Encode(input, original_input + ".huf");

    return original_input + ".huf";
}

void Opt1_Encode(MoveToFront& mtf, Huffman& h, const string& input)
{
    auto start = chrono::high_resolution_clock::now();
    string input_no_ext = input;
    input_no_ext.erase(input_no_ext.size() - 4, 4);

    string output = MTF_Encode(mtf, input);
    auto mtf_encoded = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(mtf_encoded - start).count() / 1000.0 << " s" << endl;

    Huffman_Encode(h, output, input_no_ext);
    auto huffman_encoded = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(huffman_encoded - mtf_encoded).count() / 1000.0 << " s" << endl;

    cout << "Total time: ";
    cout << setw(14);
    cout << chrono::duration_cast<chrono::milliseconds>(huffman_encoded - start).count() / 1000.0 << " s" << endl;

    remove(output.c_str());
}

void Opt2_Encode(BurrowsWheeler& bwt, MoveToFront& mtf, Huffman& h, const string& input)
{
    auto start = chrono::high_resolution_clock::now();
    string input_no_ext = input;
    input_no_ext.erase(input_no_ext.size() - 4, 4);

    string output = BWT_Encode(bwt, input);
    string to_delete;
    auto bwt_encoded = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(bwt_encoded - start).count() / 1000.0 << " s" << endl;

    to_delete = output;
    output = MTF_Encode(mtf, output);
    auto mtf_encoded = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(mtf_encoded - bwt_encoded).count() / 1000.0 << " s" << endl;

    remove(to_delete.c_str());

    Huffman_Encode(h, output, input_no_ext);
    auto huffman_encoded = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(huffman_encoded - mtf_encoded).count() / 1000.0 << " s" << endl;

    cout << "Total time: ";
    cout << setw(14);
    cout << chrono::duration_cast<chrono::milliseconds>(huffman_encoded - start).count() / 1000.0 << " s" << endl;

    remove(output.c_str());
}

void Opt3_Encode(Huffman& h, const string& input)
{
    auto start = chrono::high_resolution_clock::now();
    string input_no_ext = input;
    input_no_ext.erase(input_no_ext.size() - 4, 4);

    Huffman_Encode(h, input, input_no_ext);
    auto huffman_encoded = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(huffman_encoded - start).count() / 1000.0 << " s" << endl;

    cout << "Total time: ";
    cout << setw(14);
    cout << chrono::duration_cast<chrono::milliseconds>(huffman_encoded - start).count() / 1000.0 << " s" << endl;
}

string BWT_Decode(BurrowsWheeler& bwt, const string& input, const string& original_input)
{
    cout << "BWT decoding... ";
    cout << setw(10);
    bwt.Decode(input, original_input + "_encoded_bwt");

    return original_input + "_encoded_bwt";
}

string MTF_Decode(MoveToFront& mtf, const string& input, const string& original_input)
{
    cout << "MTF decoding... ";
    cout << setw(10);
    mtf.Decode(input, original_input + "_encoded_mtf");

    return original_input + "_encoded_mtf";
}

string Huffman_Decode(Huffman& h, const string& input, const string& original_input)
{
    cout << "Huffman decoding... ";
    cout << setw(6);
    h.Decode(input, original_input + "_encoded_huf");

    return original_input + "_encoded_huf";
}

void Opt1_Decode(MoveToFront& mtf, Huffman& h, const string& input)
{
    auto start = chrono::high_resolution_clock::now();
    string input_no_ext = input;
    input_no_ext.erase(input_no_ext.size() - 4, 4);

    string output = Huffman_Decode(h, input, input_no_ext);
    auto huffman_decoded = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(huffman_decoded - start).count() / 1000.0 << " s" << endl;

    string old_name = MTF_Decode(mtf, output, input_no_ext);
    string new_name = old_name;
    new_name.erase(old_name.size() - 4, 4);
    new_name += ".txt";
    auto mtf_decoded = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(mtf_decoded - huffman_decoded).count() / 1000.0 << " s" << endl;

    cout << "Total time: ";
    cout << setw(14);
    cout << chrono::duration_cast<chrono::milliseconds>(mtf_decoded - start).count() / 1000.0 << " s" << endl;

    remove(input.c_str());
    remove(input_no_ext.c_str());
    remove(output.c_str());

    rename(old_name.c_str(), new_name.c_str());
}

void Opt2_Decode(BurrowsWheeler& bwt, MoveToFront& mtf, Huffman& h, const string& input)
{
    auto start = chrono::high_resolution_clock::now();
    string input_no_ext = input;
    input_no_ext.erase(input_no_ext.size() - 4, 4);

    string output = Huffman_Decode(h, input, input_no_ext);
    string to_delete;
    auto huffman_decoded = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(huffman_decoded - start).count() / 1000.0 << " s" << endl;

    to_delete = output;
    output = MTF_Decode(mtf, output, input_no_ext);
    auto mtf_decoded = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(mtf_decoded - huffman_decoded).count() / 1000.0 << " s" << endl;

    remove(to_delete.c_str());

    string old_name = BWT_Decode(bwt, output, input_no_ext);
    string new_name = old_name;
    new_name.erase(old_name.size() - 4, 4);
    new_name += ".txt";
    auto bwt_decoded = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(bwt_decoded - mtf_decoded).count() / 1000.0 << " s" << endl;

    cout << "Total time: ";
    cout << setw(14);
    cout << chrono::duration_cast<chrono::milliseconds>(bwt_decoded - start).count() / 1000.0 << " s" << endl;

    remove(input.c_str());
    remove(input_no_ext.c_str());
    remove(output.c_str());

    rename(old_name.c_str(), new_name.c_str());
}

void Opt3_Decode(Huffman& h, const string& input)
{
    auto start = chrono::high_resolution_clock::now();
    string input_no_ext = input;
    input_no_ext.erase(input_no_ext.size() - 4, 4);

    string old_name = Huffman_Decode(h, input, input_no_ext);
    string new_name = old_name;
    new_name.erase(old_name.size() - 4, 4);
    new_name += ".txt";
    auto huffman_decoded = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(huffman_decoded - start).count() / 1000.0 << " s" << endl;

    cout << "Total time: ";
    cout << setw(14);
    cout << chrono::duration_cast<chrono::milliseconds>(huffman_decoded - start).count() / 1000.0 << " s" << endl;

    remove(input.c_str());
    remove(input_no_ext.c_str());

    rename(old_name.c_str(), new_name.c_str());
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
    cout << "1. Move to front\n2. Burrows-Wheeler & Move to front\n3. None of the above\n";
    cin >> option_2;

    switch (option_1)
    {
    case 1:
        cout << "\nPlease specify the file name: ";
        cin >> input;
        input += ".txt";
        switch (option_2)
        {
        case 1:
            Opt1_Encode(mtf, h, input);
            break;
        case 2:
            Opt2_Encode(bwt, mtf, h, input);
            break;
        case 3:
            Opt3_Encode(h, input);
            break;
        default:
            break;
        }
        break;
    case 2:
        cout << "\nPlease specify the file name: ";
        cin >> input;
        input += ".huf";
        switch (option_2)
        {
        case 1:
            Opt1_Decode(mtf, h, input);
            break;
        case 2:
            Opt2_Decode(bwt, mtf, h, input);
            break;
        case 3:
            Opt3_Decode(h, input);
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