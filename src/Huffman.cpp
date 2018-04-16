#include "Huffman.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <bitset>

using namespace std;

void Huffman::ReadDataFromFile(string filename)
{
    ifstream fin(filename, ios::out | ios::binary);
    fin.seekg(0, std::ios::beg);
    int start = fin.tellg();
    fin.seekg(0, std::ios::end);
    int stop = fin.tellg();
    fin.seekg(0, std::ios::beg);
    int size = stop - start;
    const size_t count = size;
    decoded_data.resize(count);
    fin.read(reinterpret_cast<char*>(&decoded_data[0]), count * sizeof(unsigned char));
    fin.close();
}

void Huffman::WriteDataToFile(string filename)
{
    ofstream fout(filename, ios::out | ios::binary);
    fout.write(reinterpret_cast<const char*>(&encoded_data[0]), encoded_data.size() * sizeof(unsigned char));
    fout.close();
}

void Huffman::CalculateFrequencies()
{
    for (auto const& x : decoded_data)
    {
        frequencies[x]++;
    }
    frequencies[255] = 1;
}

void Huffman::CreateTree()
{
    priority_queue<Node*, vector<Node*>, Node::Compare> queue;
    for (auto const& x : frequencies) queue.push(new Node(x.first, x.second));

    while (queue.size() > 1)
    {
        Node* left = queue.top();
        queue.pop();
        Node* right = queue.top();
        queue.pop();

        Node* parent = new Node('#', left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;

        queue.push(parent);
    }

    tree = queue.top();
    queue.pop();

    /*
    std::priority_queue<Node*, vector<Node*>, Node::Compare> temp = queue;
    while (!temp.empty()) {
        Node* a = temp.top();
        std::cout << (int)a->symbol << ":: " << a->frequency << std::endl;
        temp.pop();
    }
    */
}

void Huffman::TraverseTree(Node* parent, const string& code_so_far)
{
    if (parent == nullptr) return;

    if (parent->symbol != '#')
    {
        for (auto const& x : code_so_far) codes[parent->symbol].push_back(x - '0');
    }

    TraverseTree(parent->left, code_so_far + "0");
    TraverseTree(parent->right, code_so_far + "1");
}

void Huffman::CreateOutput()
{
    index = buffer.size();
    for (auto const& x : decoded_data) ProcessSymbol(x);
    ProcessSymbol(255);
    PadByte();
}

void Huffman::ProcessSymbol(unsigned char symbol)
{
    for (auto i = 0; i < codes[symbol].size(); i++)
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

void Huffman::CreateEncodingMap()
{
    TraverseTree(tree, "");
}

void Huffman::Encode(const string& input_file, const string& output_file)
{
    ReadDataFromFile(input_file);
    CalculateFrequencies();
    CreateTree();
    CreateEncodingMap();
    CreateOutput();
    WriteDataToFile(output_file);

    cout << "Data from file:\n";
    for (auto const& x : decoded_data) cout << (int)x << " ";
    cout << endl << endl;

    cout << "Frequencies:\n";
    for (auto const& x : frequencies) cout << (int)x.first << ": " << x.second  << endl;
    cout << endl;

    cout << "Codes:\n";
    for (auto const& x : codes)
    {
        cout << (int)x.first << ": ";
        for (auto const& y : x.second) cout << y;
        cout << endl;
    }
    cout << endl;

    cout << "Output:\n";
    for (auto const& x : encoded_data) cout << (int)x << " ";
    cout << endl << endl;
}

void Huffman::Decode(const string& input_file, const string& output_file)
{
}
