#include "Huffman.h"
#include "Commons.h"
#include <queue>
#include <fstream>
#include <iostream>

void Huffman::WriteFrequenciesToFile(string filename)
{
    ofstream fout(filename);
    size_t size = frequencies.size();
    fout << size << endl;
    for (auto const& x : frequencies)
    {
        fout << (int)x.first << " " << x.second << " ";
    }
    fout.close();
}

void Huffman::ReadFrequenciesFromFile(string filename)
{
    ifstream fin(filename);
    size_t size, c, freq;
    fin >> size;
    for (size_t i = 0; i < size; i++)
    {
        fin >> c;
        fin >> freq;
        frequencies[(unsigned char)c] = freq;
    }
    fin.close();
}

void Huffman::ResetValues()
{
    decoded_data.clear();
    encoded_data.clear();
    frequencies.clear();
    codes.clear();
    buffer.reset();
    tree = nullptr;
    index = 0;
}

void Huffman::CalculateFrequencies()
{
    for (auto const& x : decoded_data)
        frequencies[x]++;

    frequencies[255] = 1;
}

void Huffman::CreateTree()
{
    priority_queue<Node*, vector<Node*>, Node::Compare> queue;
    for (auto const& x : frequencies)
        queue.push(new Node(x.first, x.second));

    while (queue.size() > 1)
    {
        Node* left = queue.top();
        queue.pop();
        Node* right = queue.top();
        queue.pop();

        Node* parent = new Node((char)254, left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;

        queue.push(parent);
    }

    tree = queue.top();
    queue.pop();
}

void Huffman::TraverseTree(Node* parent, const string& code_so_far)
{
    if (parent == nullptr)
        return;

    if (parent->symbol != 254) 
        for (auto const& x : code_so_far)
            codes[parent->symbol].push_back(x - '0');

    TraverseTree(parent->left, code_so_far + "0");
    TraverseTree(parent->right, code_so_far + "1");
}

void Huffman::CreateEncodingMap()
{
    TraverseTree(tree, "");
}

void Huffman::ProcessSymbol(unsigned char symbol)
{
    for (size_t i = 0; i < codes[symbol].size(); i++)
    {
        index--;
        buffer[index] = codes[symbol][i];
        if (index == 0)
        {
            encoded_data.push_back(static_cast<unsigned char>(buffer.to_ulong()));
            index = buffer.size();
        }
    }
}

void Huffman::PadByte()
{
    while (index > 0)
    {
        index--;
        buffer[index] = 0;
    }
    encoded_data.push_back(static_cast<unsigned char>(buffer.to_ulong()));
}

void Huffman::CreateEncodedOutput()
{
    index = buffer.size();
    for (auto const& x : decoded_data)
        ProcessSymbol(x);
    ProcessSymbol(255);
    PadByte();
}

void Huffman::CreateDecodedOutput()
{
    Node* p = tree;
    for (auto const& x : encoded_data)
    {
        bitset<8> bits(x);
        for (auto i = 7; i >= 0; i--)
        {
            if (p->symbol != 254)
            {
                if (p->symbol == 255)
                    return;
                decoded_data.push_back(p->symbol);
                p = tree;
            }
            bits[i] ? p = p->right : p = p->left;
        }
    }
}

void Huffman::Encode(const string& input_file, const string& output_file)
{
    ResetValues();
    ReadDataFromFile(input_file, decoded_data);
    CalculateFrequencies();
    CreateTree();
    CreateEncodingMap();
    CreateEncodedOutput();
    WriteFrequenciesToFile(output_file + "ext");
    WriteDataToFile(output_file, encoded_data);
}

void Huffman::Decode(const string& input_file, const string& output_file)
{
    ResetValues();
    ReadDataFromFile(input_file, encoded_data);
    ReadFrequenciesFromFile(input_file + "ext");
    CreateTree();
    CreateDecodedOutput();
    WriteDataToFile(output_file, decoded_data);
}
