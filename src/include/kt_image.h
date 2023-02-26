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

    /**
     * Creates an image loader out of the passed directory
     *
     *@param filePath Path to the image source
     * */
    explicit ImageLoader(const PathType& filePath)
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

    /**
     * Destroys the Image Loader
     *
     * */
    ~ImageLoader() {
        delete[] this->m_Data;
    }

    /**
     * Returns the path of the image source loaded
     *
     * @return Path to image loaded
     * */
    NODISCARD
    auto getFilePath() const -> const PathType& {
        return m_FilePath;
    }

    /**
     * Writes the contents of the loaded image to the file
     * indicated by outputFilePath
     *
     * @param outputFilePath Path to out file
     * */
    auto outFileData(const PathType& outputFilePath) -> void {
        // creates the file if it doesn't exist, if
        // it does, it empties it first
        OutFileType file(outputFilePath, std::ios::binary | std::ios::trunc);

        if (file.is_open()) {
            for (SizeType it = 0; it < this->m_FileSize; ++it)
                file << this->m_Data[it];
        }
    }

#ifdef _DEBUG
    /**
     * Prints contents of the loaded file to standard output
     *
     * */
    auto printSomeStuff() -> void {
        for (SizeType position = 0; position < 10; ++position)
            std::cout << std::uppercase << std::hex <<
                static_cast<std::uint32_t>(this->m_Data[position]) << ' ';
    }
#endif



private:
    /**
     * Returns the size in bytes of the file passed as parameter
     *
     * @param file File to process
     * @return size of the file
     * */
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

    /**
     * Returns a std::pair containing the bytes of the file with
     * filePath source path and its size
     *
     * @param filePath File source path
     * @return and std::pair with contents of the file as bytes and its size
     *
     * */
    static auto getData(const PathType& filePath) -> std::pair<unsigned char*, SizeType> {
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

    // File source path
    PathType m_FilePath{};

    // File size in bytes
    SizeType m_FileSize{};

    // Contents of the file
    unsigned char* m_Data{};


};  // END ImageLoader class

} // END kate NAMESPACE

#endif