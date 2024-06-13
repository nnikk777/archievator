#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "LZ77.h"

using namespace std;

/**
 * @brief Найти самое длинное совпадение подстроки в скользящем окне.
 * 
 * @param input_string Входная строка для поиска совпадений.
 * @param current_pos Текущая позиция в строке.
 * @param window_size Размер скользящего окна.
 * @param look_ahead_size Размер буфера предсказания.
 * @return Match Структура, содержащая длину и расстояние совпадения.
 */
Match
find_longest_match(const string& input_string, int current_pos, int window_size, int look_ahead_size)
{
    int end_of_string = min(current_pos + look_ahead_size, (int)input_string.length());
    int max_length = 0;
    int max_distance = 0;
    
    for (int i = max(0, current_pos - window_size); i < current_pos; ++i) {
        int length = 0;
        
        while (current_pos + length < end_of_string && input_string[i + length] == input_string[current_pos + length]) {
            length++;
        } 
        
        if (length > max_length) {
            max_length = length;
            max_distance = current_pos - i;
        }
    }
    
    if (max_length > 0) {
        return {max_distance, max_length, '\0'};
    } else {
        return {0, 0, input_string[current_pos]};
    }
}

/**
 * @brief Функция для сжатия строки с использованием алгоритма LZ77.
 * 
 * @param input_string Входная строка для сжатия.
 * @return vector<Match> Вектор структур Match, содержащих данные о сжатии.
 */
vector<Match>
compress(const string& input_string)
{
    int window_size = 100000;  
    int look_ahead_size = 30;  

    vector<Match> result;
    int i = 0;
    while (i < input_string.length()) {
        Match match = find_longest_match(input_string, i, window_size, look_ahead_size);
        if (match.length > 0) {
            result.push_back(match);
            i += match.length;
        } else {
            result.push_back({0, 0, input_string[i]});
            i++;
        }
    }

    return result;
}

/**
 * @brief Функция для декомпрессии данных, сжатых с использованием алгоритма LZ77.
 * 
 * @param compressed_data Вектор структур Match, содержащих сжатые данные.
 * @return string Декомпрессированная строка.
 */
string
decompress(const vector<Match>& compressed_data)
{
    string result;
    for (const auto& match : compressed_data) {
        if (match.length == 0) {
            result += match.next_char;
        } else {
            int start_pos = result.length() - match.distance;
            for (int i = 0; i < match.length; ++i) {
                result += result[start_pos + i];
            }
        }
    }
    return result;
}

/**
 * @brief Функция для декомпрессии строки, сжатой в формате LZ77.
 * 
 * @param compressed_data Строка, содержащая сжатые данные в формате LZ77.
 * @return string Декомпрессированная строка.
 */
string
decompress_2(const string& compressed_data)
{
    string temp = compressed_data;
    string decompressed_string = "";
    while (temp.length() > 0) {
        int distance, length;
        char new_char;
        bool end_of_the_string = false;
        string distance_str, length_str;
        
        int brackets_meet = temp.find(")(");
        if (brackets_meet == -1) {
            brackets_meet = temp.length();
            end_of_the_string = true;
        }
        
        string bracket = temp.substr(0, brackets_meet + 1);
        bracket = bracket.substr(1, bracket.length() - 2);
        int distance_ends = bracket.find(',');
        distance_str = bracket.substr(0, distance_ends);
        distance = stoi(distance_str);
        if (bracket.substr(distance_ends + 1, bracket.length() - distance_ends - 1).find(',') != -1) {
            int length_ends = bracket.substr(distance_ends + 1, bracket.length() - distance_ends - 1).find(',');
            length_str = bracket.substr(distance_ends + 1, length_ends);
            length = stoi(length_str);
            new_char = bracket[length_ends + distance_ends + 2];
            decompressed_string += new_char;
        } else {
            length_str = bracket.substr(distance_ends + 1, bracket.length());
            length = stoi(length_str);
            int start = decompressed_string.length() - distance;
            for (int i = start; i < start + length; i++) {
                decompressed_string += decompressed_string[i];
            }
        }

        if (!end_of_the_string) {
            temp = temp.substr(brackets_meet + 1, temp.length() - 1 - brackets_meet);
        } else {
            break;
        }
    }
    return decompressed_string;
}

/**
 * @brief Функция для конвертации сжатых данных в формат LZ77.
 * 
 * @param compressed_data Вектор структур Match, содержащих сжатые данные.
 * @return string Строка, содержащая сжатые данные в формате LZ77.
 */
string
convert_to_LZ77_format(const vector<Match>& compressed_data)
{
    string converted_data = "";
    string distance, length, next_char;
    for (const auto& el : compressed_data) {
        distance = to_string(el.distance);
        length = to_string(el.length);
        char c = el.next_char;
        if (el.next_char == '\0') {
            converted_data += '(';
            converted_data += distance;
            converted_data += ',';
            converted_data += length;
            converted_data += ')';
        } else {
            converted_data += '(';
            converted_data += distance;
            converted_data += ',';
            converted_data += length;
            converted_data += ',';
            converted_data += c;
            converted_data += ')';
        }
    }
    return converted_data;
}

/**
 * @brief Основная функция для выполнения LZ77 сжатия и декомпрессии.
 * 
 * Считывает строку из файла, выполняет LZ77 сжатие и декомпрессию, 
 * записывает результаты в выходные файлы.
 * 
 * @param path Путь к входному файлу для сжатия.
 */
void
main_compressionLZ77(std::string path)
{
    ifstream file(path);
    stringstream buffer;
    string line;
    while (!file.eof()) {
        getline(file, line);
        buffer << line << "\n";
    }
    fstream file_out("../data_out/data_out.txt");
    stringstream buffer_out;
    string input_string = buffer.str();
    vector<Match> compressed_data = compress(input_string);
    string converted_data = convert_to_LZ77_format(compressed_data);
    line = converted_data;
    if (!file_out.eof()) {
        file_out << line;
    }
    string decompressed = decompress_2(line);
    ofstream decompressed_out("../decompressed_check/decompressed_out.txt");
    if (!decompressed_out.eof()) {
        decompressed_out << decompressed;
    }
    decompressed_out.close();
    file.close();
    file_out.close();
}
