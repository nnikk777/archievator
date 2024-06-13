#pragma ONCE
#include <iostream>
#include <vector>
#include <fstream>
#include <string>


std::vector<std::pair<int, int>> rleCompress(const std::vector<int>& image);
std::vector<int> rleDecompress(const std::vector<std::pair<int, int>>& compressedData);
void main_compressionRLE();
