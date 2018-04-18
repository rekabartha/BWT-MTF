#include "Commons.h"
#include <fstream>

void ReadDataFromFile(string filename, vector<unsigned char>& data)
{
    ifstream fin(filename, ios::in | ios::binary);
    fin.seekg(0, ios::beg);
    auto start = fin.tellg();
    fin.seekg(0, ios::end);
    auto stop = fin.tellg();
    fin.seekg(0, ios::beg);
    auto size = stop - start;
    const size_t count = (size_t)size;
    data.resize(count);
    fin.read(reinterpret_cast<char*>(&data[0]), count * sizeof(unsigned char));
    fin.close();
}

void WriteDataToFile(string filename, vector<unsigned char>& data)
{
    ofstream fout(filename, ios::out | ios::binary);
    fout.write(reinterpret_cast<const char*>(&data[0]), data.size() * sizeof(unsigned char));
    fout.close();
}