#ifndef KT_IMAGE_HH
#define KT_IMAGE_HH

// C++ STD Library
#include <filesystem>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdint>
#include <utility>
#include <string_view>

// Extensions
#include "tools.h"

// just make simple image loader to load
// the image in the repo for now
// i.e. support for .png files
namespace kate {
class ImageLoader {
public:
    using SizeType = std::size_t;
    using PathType = std::filesystem::path;
    using FileType = std::ifstream;
    using OutFileType = std::ofstream;
    
    explicit ImageLoader(const std::filesystem::path& filePath)
        :   m_FilePath(filePath), m_FileSize(), m_Data(nullptr) {
        auto temp = getData(filePath);
        this->m_Data = temp.first;
        this->m_FileSize = temp.second;

        if (!this->m_Data) {
            std::cerr << "--------------------------\n";
            std::cerr << "Error: Could not open file\n";
            std::cerr << "--------------------------\n";

        }
        else {
            std::cerr << "-------------------------------------\n";
            std::cerr << "Success: Could open file successfully\n";
            std::cerr << "-------------------------------------\n";

        }

        
#ifdef _DEBUG
        printSomeStuff();
        
#endif
    }  

    ~ImageLoader() {
        delete[] this->m_Data;
    }

    NODISCARD
    auto getFilePath() const -> const std::filesystem::path& {
        return m_FilePath;
    }

    auto outFileData(const std::filesystem::path& outputFilePath) -> void {
        // creates the file if it doesn't exist, if
        // it does, it empties it first
        OutFileType file(outputFilePath, std::ios::binary | std::ios::trunc);

        if (file.is_open()) {
            for (SizeType it = 0; it < this->m_FileSize; ++it)
                file << this->m_Data[it];
        }
    }

#ifdef _DEBUG
    auto printSomeStuff() -> void {
        std::cout << std::endl;
        for (SizeType position = 0; position < 10; ++position) {
            unsigned short out = this->m_Data[position];
            std::cout << std::uppercase << std::hex << out << ' ';
           
        }
    }
#endif



private:
    static auto getFileSize(FileType& file) -> SizeType {
        // backup previous position
        FileType::pos_type previousPosition = file.tellg();

        // set read position to end of file and infer size
        file.seekg(0, std::ios::end);
        SizeType result = file.tellg();

        // restore read position to the previous position
        file.seekg(previousPosition);

        return result;
    }

    static auto getData(const std::filesystem::path& filePath) -> std::pair<unsigned char*, SizeType> {
        std::pair<unsigned char*, SizeType> result = std::make_pair(nullptr, 0);
        FileType temp(filePath, std::ios::binary);
        try {
            result.second = getFileSize(temp);
            result.first = new unsigned char[result.second];
        }
        catch (...) {
            std::cerr << "Could not allocate memory for getData()...\n";
        }

        if (result.first != nullptr) {
            for (SizeType index = 0; index < result.second; ++index) {
                temp.seekg(index);
                unsigned char byte = temp.peek();
                result.first[index] = byte;

            }
        }

        return result;
    }

    PathType m_FilePath{};
    SizeType m_FileSize{};
    unsigned char* m_Data{};


};  // END ImageLoader class

} // END kate NAMESPACE

#endif