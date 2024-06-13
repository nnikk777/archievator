#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;


struct Match {
    int distance;
    int length;
    char next_char;
};
Match find_longest_match(const string& input_string, int current_pos, int window_size, int look_ahead_size);
vector<Match> compress(const string& input_string);
string decompress(const vector<Match>& compressed_data);
string decompress_2(const string& compressed_data);
string convert_to_LZ77_format(const vector<Match> & compressed_data);\
void main_compressionLZ77(std::string path);