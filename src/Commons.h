#pragma once
#include <string>
#include <vector>

using namespace std;

void ReadDataFromFile(string filename, vector<unsigned char>& data);
void WriteDataToFile(string filename, vector<unsigned char>& data);
