#pragma once
#include <map>
#include <vector>
#include <bitset>
#include <string>

using namespace std;

class Huffman {
private:
    class Node {
    public:
        unsigned char symbol;
        size_t frequency;
        Node* left;
        Node* right;

        Node(unsigned char symbol, size_t frequency) : symbol(symbol), frequency(frequency), left(nullptr), right(nullptr) {}

        class Compare
        {
        public:
            bool operator() (Node* first, Node* second)
            {
                return (first->frequency > second->frequency);
            }
        };
    };

    vector<unsigned char> decoded_data;
    vector<unsigned char> encoded_data;
    map<unsigned char, size_t> frequencies;
    Node* tree;
    map<unsigned char, vector<bool>> codes;

    bitset<8> buffer;
    size_t index;

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