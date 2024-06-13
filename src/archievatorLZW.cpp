#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include "LZW.h"

/**
 * @brief Функция сжатия строки методом LZW.
 * 
 * @param input Входная строка для сжатия.
 * @return std::vector<int> Вектор сжатых целочисленных значений.
 */
std::vector<int> compressLZW(const std::string& input) {
    std::unordered_map<std::string, int> dictionary;
    std::vector<int> compressed;

    for (int i = 0; i < 256; ++i) {
        dictionary[std::string(1, char(i))] = i;
    }

    std::string current;
    for (char symbol : input) {
        std::string next = current + symbol;
        if (dictionary.find(next) != dictionary.end()) {
            current = next;
        } else {
            compressed.push_back(dictionary[current]);
            dictionary[next] = dictionary.size();
            current = std::string(1, symbol);
        }
    }

    if (!current.empty()) {
        compressed.push_back(dictionary[current]);
    }

    return compressed;
}

/**
 * @brief Функция преобразования вектора сжатых значений в строку.
 * 
 * @param compressed Вектор сжатых значений.
 * @return std::string Строка, представляющая сжатые значения.
 */
std::string convert_to_string(std::vector<int> compressed) {
    std::string compressed_str;
    for (int i = 0; i < compressed.size(); i++) {
        compressed_str += std::string(1, char(compressed[i]));
        compressed_str += ' ';
    }
    return compressed_str;
}

/**
 * @brief Функция преобразования строки сжатых значений в вектор целых чисел.
 * 
 * @param compressed_str Строка сжатых значений.
 * @return std::vector<int> Вектор целых чисел, представляющих сжатые значения.
 */
std::vector<int> convert_to_vector(std::string compressed_str) {
    std::vector<int> compressed;
    std::string index_str;
    int index;
    for (int i = 0; i < compressed_str.length(); i++) {
        if (char(compressed_str[i]) != ' ') {
            index_str += char(compressed_str[i]);
        } else {
            compressed.push_back(std::stoi(index_str));
            index_str = "";
        }
    }
    return compressed;
}

/**
 * @brief Функция декомпрессии строки методом LZW.
 * 
 * @param compressed Вектор сжатых значений для декомпрессии.
 * @return std::string Раскодированная строка.
 */
std::string decompressLZW(const std::vector<int>& compressed) {
    std::unordered_map<int, std::string> dictionary;
    std::string decompressed;

    for (int i = 0; i < 256; ++i) {
        dictionary[i] = std::string(1, char(i));
    }

    std::string previous(1, char(compressed[0]));
    decompressed += previous;

    for (size_t i = 1; i < compressed.size(); ++i) {
        std::string current;
        int code = compressed[i];

        if (dictionary.find(code) != dictionary.end()) {
            current = dictionary[code];
        } else if (code == dictionary.size()) {
            current = previous + previous[0];
        }

        decompressed += current;
        dictionary[dictionary.size()] = previous + current[0];
        previous = current;
    }

    return decompressed;
}

/**
 * @brief Основная функция для сжатия и декомпрессии файла методом LZW.
 * 
 * @param filename Имя файла для сжатия.
 */
void main_compressionLZW(std::string filename) {
    std::ifstream file(filename);
    std::ofstream file_out("../data_out/data_out.txt");
    std::string line;
    std::stringstream buffer;

    while (!file.eof()) {
        getline(file, line);
        buffer << line << '\n';
    }

    std::string input = buffer.str();
    std::vector<int> compressed = compressLZW(input);
    std::string compressed_string = convert_to_string(compressed);

    if (!file_out.eof()) {
        file_out << compressed_string;
    }

    file.close();
    file_out.close();

    std::string decompressed = decompressLZW(compressed);
    std::ofstream decompressed_out("../decompressed_check/decompressed_out.txt");

    if (!decompressed_out.eof()) {
        decompressed_out << decompressed;
    }

    decompressed_out.close();
}
