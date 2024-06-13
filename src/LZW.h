#pragma ONCE 
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;


vector<int> compressLZW(const std::string& input);
std::string convert_to_string (std::vector<int> compressed);
std::vector<int> convert_to_vector (std::string compressed_str);
std::string decompressLZW(const std::vector<int>& compressed);
void main_compressionLZW(std::string filename);

