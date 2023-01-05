#ifndef KT_IMAGE_HH
#define KT_IMAGE_HH

#include <filesystem>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdint>
#include <utility>

// just make simple image loader to load
// the image in the repo for now
// i.e. support for .png files
namespace kate {
class ImageLoader {
public:
    using SizeType = std::size_t;
    using PathType = std::filesystem::path;
    using FileType = std::ifstream;
    ImageLoader(std::filesystem::path filePath) 
        :   m_FilePath(filePath), m_Data(nullptr) {
        auto temp = getData(filePath);
        this->m_Data = temp.first;
        this->m_FileSize = temp.second;

        if (!this->m_Data) {
            std::cerr << "-----------------------------\n";
            std::cerr << "Error: Could not open file.\n";
            std::cerr << "-----------------------------\n";

        }
        else {
            std::cerr << "-----------------------------\n";
            std::cerr << "Succes: Could open file succesfully.\n";
            std::cerr << "-----------------------------\n";

        }

        
#ifdef _DEBUG
        printSomeStuf();
        
#endif
    }  

    ~ImageLoader() {
        delete[] this->m_Data;
    }

    auto getFilePath() const -> const std::filesystem::path& {
        return m_FilePath;
    }

#ifdef _DEBUG
    auto printSomeStuf() -> void {  
        std::cout << std::endl;
        auto temp = this->m_Data;
        for (SizeType position = 0; position < 10; ++position) {
            std::cout << std::uppercase << std::hex << static_cast<int>(*(temp + position)) << ' ';
           
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

    std::pair<char*, SizeType> getData(std::filesystem::path filePath) {
        std::pair<char*, SizeType> result = std::make_pair(nullptr, 0);
        FileType temp(filePath, std::ios::binary);
        try {
            result.second = getFileSize(temp);
            result.first = new char[result.second];
        }
        catch (...) {
            std::cerr << "Could not allocate memory for getData()...\n";
        }

        if (result.first) {
            for (SizeType index = 0; index < result.second; ++index) {
                temp.seekg(index);
                unsigned char byte = temp.peek();
                *(result.first + index) = byte;

            }
        }

        return result;
    }

    PathType m_FilePath{};
    SizeType m_FileSize{};
    char* m_Data{};


};  // END ImageLoader class

} // END kate NAMESPACE

#endif