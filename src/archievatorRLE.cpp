#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "RLE.h"

/**
 * @brief Функция для RLE сжатия.
 * 
 * @param image Входной вектор с изображением.
 * @return std::vector<std::pair<int, int>> Вектор пар, представляющих сжатые данные.
 */
std::vector<std::pair<int, int>> rleCompress(const std::vector<int>& image) {
    std::vector<std::pair<int, int>> compressedData;
    if (image.empty()) return compressedData;

    int prevPixel = image[0];
    int runLength = 1;

    for (int i = 1; i < image.size(); ++i) {
        if (image[i] < prevPixel + 20 && image[i] > prevPixel - 20) {
            runLength++;
        } else {
            compressedData.push_back({prevPixel, runLength});
            prevPixel = image[i];
            runLength = 1;
        }
    }
    compressedData.push_back({prevPixel, runLength});
    return compressedData;
}

/**
 * @brief Функция для RLE декомпрессии.
 * 
 * @param compressedData Вектор пар, представляющих сжатые данные.
 * @return std::vector<int> Декомпрессированный вектор с изображением.
 */
std::vector<int> rleDecompress(const std::vector<std::pair<int, int>>& compressedData) {
    std::vector<int> decompressedImage;
    for (const auto& pair : compressedData) {
        decompressedImage.insert(decompressedImage.end(), pair.second, pair.first);
    }
    return decompressedImage;
}

/**
 * @brief Основная функция для выполнения RLE сжатия и декомпрессии.
 * 
 * Считывает изображение из файла, выполняет RLE сжатие и декомпрессию, 
 * записывает результаты в выходные файлы.
 */
void main_compressionRLE() {
    std::ifstream file("image_in_array.txt");
    std::string pixel{""};
    int height, width;
    std::string first_str;
    getline(file, first_str);
    std::string height_str{""}, width_str{""};
    bool flag = true;
    
    for (int i = 0; i < first_str.length(); i++) {
        if (first_str[i] != ' ' && flag) {
            height_str += first_str[i];
        } else if (first_str[i] == ' ') {
            flag = false;
        } else if (first_str[i] != '\n' && !flag) {
            width_str += first_str[i];
        }
    }
    
    height = 1600;
    width = 2560;
    std::vector<int> image_in_array;
    int pixel_value = 0;
    
    while (!file.eof()) {
        getline(file, pixel);
        if (pixel != "") {
            pixel_value = std::stoi(pixel);
            image_in_array.push_back(pixel_value);
        }
    }
    
    std::vector<std::pair<int, int>> compressed = rleCompress(image_in_array);
    std::vector<int> decompressed = rleDecompress(compressed);
    
    std::ofstream file_out("../data_out/output_image.txt");
    std::string image{""};
    
    for (int i = 0; i < compressed.size(); i++) {
        if (compressed[i].second != 1) {
            image += std::to_string(compressed[i].first);
            image += ',';
            image += std::to_string(compressed[i].second);
            image += ' ';
        } else {
            image += std::to_string(compressed[i].first);
            image += ' ';
        }
    }
    
    file_out << image;
    file_out.close();
    file.close();
    
    std::ofstream image_decompressed("decompressed_image_in_arrayx.txt");
    std::string new_pixel{""};
    std::string size;
    size = std::to_string(height);
    size += ' ';
    size += std::to_string(width);
    size += '\n';
    
    image_decompressed << size;
    
    for (int i = 0; i < decompressed.size(); i++) {
        new_pixel = std::to_string(decompressed[i]);
        new_pixel += '\n';
        image_decompressed << new_pixel;
    }
    
    image_decompressed.close();
}
