#pragma once
#include <string>
#include <vector>
#include <map>
#include <bitset>

using namespace std;

class Node {
public:
    unsigned char symbol;
    int frequency;
    Node* left;
    Node* right;

    Node(char symbol, int frequency) : symbol(symbol), frequency(frequency), left(nullptr), right(nullptr) {}

    class Compare
    {
    public:
        bool operator() (Node* first, Node* second)
        {
            return (first->frequency > second->frequency);
        }
    };
};

class Huffman {
private:
    vector<unsigned char> decoded_data;
    vector<unsigned char> encoded_data;
    map<unsigned char, int> frequencies;
    map<unsigned char, vector<bool>> codes;
    Node* tree;

    bitset<8> buffer;
    int index;

    void WriteFrequenciesToFile(string filename);
    void ReadFrequenciesFromFile(string filename);
    void ResetValues();
    void CalculateFrequencies();
    void CreateTree();
    void TraverseTree(Node* parent, const string& code_so_far);
    void CreateEncodingMap();
    void ProcessSymbol(unsigned char symbol);
    void PadByte();
    void CreateEncodedOutput();
    void CreateDecodedOutput();

public:
    void Encode(const string& input_file, const string& output_file);
    void Decode(const string& input_file, const string& output_file);
};