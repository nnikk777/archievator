#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "LZW.h"
#include "LZ77.h"
#include "RLE.h"
#include <stdexcept>



TEST_CASE("LZ77"){
    std::string compressed = "(0,0,t)(0,0,e)(0,0,s)(3,1)";
	CHECK(decompress_2(compressed) == "test");

    SUBCASE("Compression and Decompression with Large Input") {
        std::string input_string(1000, 'a'); // 1000 times the character 'a'
        std::vector<Match> compressed_data = compress(input_string);
        std::string converted_data = convert_to_LZ77_format(compressed_data);
        std::string decompressed_string = decompress_2(converted_data);

        CHECK(input_string == decompressed_string);
    }

    SUBCASE("Basic Compression and Decompression") {
        std::string input_string = "abracadabra";
        std::vector<Match> compressed_data = compress(input_string);
        std::string converted_data = convert_to_LZ77_format(compressed_data);
        std::string decompressed_string = decompress_2(converted_data);

        CHECK(input_string == decompressed_string);
    }

    SUBCASE("Compression and Decompression with Repeated Patterns") {
        std::string input_string = "abababababab";
        std::vector<Match> compressed_data = compress(input_string);
        std::string converted_data = convert_to_LZ77_format(compressed_data);
        std::string decompressed_string = decompress_2(converted_data);

        CHECK(input_string == decompressed_string);
    }
}


TEST_CASE("LZW compression tests") {
    SUBCASE("Basic compression") {
        std::string input = "AB";
        std::vector<int> expected = {65, 66};
        std::vector<int> compressed = compressLZW(input);
        CHECK(compressed == expected);
    }

    SUBCASE("Single character input") {
        std::string input = "A";
        std::vector<int> expected = {65};
        std::vector<int> compressed = compressLZW(input);
        CHECK(compressed == expected);
    }

}

TEST_CASE("RLE Compression and Decompression Tests") {
    SUBCASE("Basic Compression and Decompression") {
        std::vector<int> image = {1, 1, 1, 2, 2, 3, 4, 5, 5, 5};
        std::vector<std::pair<int, int>> compressed = rleCompress(image);
        std::vector<int> decompressed = rleDecompress(compressed);

        CHECK(decompressed.size() == image.size());
    }

    SUBCASE("Compression and Decompression with Large Input") {
        std::vector<int> image(1000, 1); // 1000 times the pixel value 1
        std::vector<std::pair<int, int>> compressed = rleCompress(image);
        std::vector<int> decompressed = rleDecompress(compressed);

        CHECK(decompressed == image);
    }
}
