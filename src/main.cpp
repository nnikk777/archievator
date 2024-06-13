#include <iostream>
#include <cstdio>
#include <sys/stat.h>
#include "LZ77.h"
#include "LZW.h"
#include "RLE.h"

/**
 * @brief Clears the content of a file.
 * 
 * @param filename Name of the file to clear.
 */
void clearFile(const char* filename)
{
    FILE* file = fopen(filename, "w");
    fclose(file);
}

/**
 * @brief Outputs statistics about file sizes.
 * 
 * @param file_name Original file name.
 * @param file_name_new New file name after processing.
 * @param z_name Compressed file name.
 */
void stats(const std::string& file_name, const std::string& file_name_new, const std::string& z_name)
{
    std::ifstream file(file_name, std::ios::binary | std::ios::ate);
    std::ifstream file_new(file_name_new, std::ios::binary | std::ios::ate);
    std::ifstream zip_file(z_name, std::ios::binary | std::ios::ate);
    const char* filePath = z_name.c_str();
    struct stat fileStat;

    if (file.is_open()) {
        std::streamsize size = file.tellg();
        std::cout << "Original file size: " << size << " bytes" << std::endl;
        file.close();
        
        std::streamsize size_new = file_new.tellg();
        std::cout << "New file size: " << size_new << " bytes" << std::endl;
        file_new.close();

        if (stat(filePath, &fileStat) == 0) {
            std::cout << "Pre-compressed file size: " << fileStat.st_size << " bytes" << std::endl;
        }
    }
}

/**
 * @brief Main function that processes user input and performs compression based on the selected method.
 * 
 * @return int Return code.
 */
int main()
{
    while (true) {
        std::cout << "Please enter a command \n 1 - compress using LZ77 \n 2 - compress using LZW \n 3 - compress using RLE \n ";
        std::string command;
        std::cin >> command;

        if (command == "1") {
            std::cout << "Enter the number of data you want to compress\n";
            std::cin >> command;
            std::string filename;
            std::string zip;

            if (command == "1") {
                filename = "../data/data1.txt";
                zip = "../professional_compression/data1.txt";
            } else if (command == "2") {
                filename = "../data/data2.txt";
                zip = "../professional_compression/data2.txt";
            } else if (command == "3") {
                filename = "../data/data3.txt";
                zip = "../professional_compression/data3.txt";
            } else if (command == "4") {
                filename = "../data/data4.txt";
                zip = "../professional_compression/data4.txt";
            } else if (command == "5") {
                filename = "../data/data5.txt";
                zip = "../professional_compression/data5.txt";
            }

            clearFile("../data_out/data_out.txt");
            main_compressionLZ77(filename);
            std::cout << "Compression completed\n";
            stats(filename, "../data_out/data_out.txt", zip);

        } else if (command == "2") {
            std::cout << "Enter the number of data you want to compress\n";
            std::cin >> command;
            std::string filename;
            std::string zip;

            if (command == "1") {
                filename = "../data/data1.txt";
                zip = "../professional_compression/data1.txt";
            } else if (command == "2") {
                filename = "../data/data2.txt";
                zip = "../professional_compression/data2.txt";
            } else if (command == "3") {
                filename = "../data/data3.txt";
                zip = "../professional_compression/data3.txt";
            } else if (command == "4") {
                filename = "../data/data4.txt";
                zip = "../professional_compression/data4.txt";
            } else if (command == "5") {
                filename = "../data/data5.txt";
                zip = "../professional_compression/data5.txt";
            }

            clearFile("../data_out/data_out.txt");
            main_compressionLZW(filename);
            std::cout << "Compression completed\n";
            stats(filename, "../data_out/data_out.txt", zip);

        } else if (command == "3") {
            clearFile("../data_out/output_image.txt");
            stats("../data/rabstol_net_program_brands_29.png", "../data_out/output_image.txt", "../professional_compression/rabstol_net_program_brands_29.png");
            main_compressionRLE();
            std::cout << "Compression completed\n";
        }
    }
}
