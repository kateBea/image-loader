#ifndef KT_IMAGE_HH
#define KT_IMAGE_HH

#include <filesystem>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdint>

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
        :   m_FilePath(filePath), m_FileImage(filePath, std::ios::binary), m_Data(nullptr) {
        if (!this->m_FileImage.is_open()) {
            std::cout << "-----------------------------\n";
            std::cout << "Error: Could not open file.\n";
            std::cout << "-----------------------------\n";

        }
        else {
            std::cout << "-----------------------------\n";
            std::cout << "Succes: Could open file succesfully.\n";
            std::cout << "-----------------------------\n";

            this->m_Data = new (std::nothrow) char[getFileSize()];
        }

        
#ifdef _DEBUG
        printSomeStuf();
        std::cout << std::dec << "\nFile size: " << getFileSize() << " bytes\n";
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
        for (int i = 0; i < 10; ++i) {
            unsigned char byte;
            this->m_FileImage >> byte;
            std::cout << std::uppercase << std::hex << static_cast<int>(byte) << ' ';
        }
    }
#endif

    auto getFileSize() -> SizeType {
        // backup previous position
        FileType::pos_type previousPosition = this->m_FileImage.tellg();

        // set read position to end of file and infer size
        this->m_FileImage.seekg(0, std::ios::end);
        SizeType result = this->m_FileImage.tellg();

        // restore read position to the previous position
        this->m_FileImage.seekg(previousPosition);

        return result;
    }


private:
    PathType m_FilePath{};
    FileType m_FileImage{};
    char* m_Data{};


};  // END ImageLoader class

} // END kate NAMESPACE

#endif