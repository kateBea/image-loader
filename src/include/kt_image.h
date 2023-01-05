#ifndef KT_IMAGE_HH
#define KT_IMAGE_HH

#include <filesystem>
#include <cstdio>
#include <iostream>
#include <fstream>

// just make simple image loader to load
// the image in the repo for now
// i.e. support for .png files
namespace kate {
class ImageLoader {
public:
    ImageLoader(std::filesystem::path filePath) 
        :   m_FilePath(filePath), m_FileImage(filePath, std::ios::binary) {
        if (this->m_FileImage.is_open()) {
            std::cout << "-----------------------------\n";
            std::cout << "Error: Could not open file.\n";
            std::cout << "-----------------------------\n";
        }
        else {
            std::cout << "-----------------------------\n";
            std::cout << "Succes: Could open file succesfully.\n";
            std::cout << "-----------------------------\n";
        }

        std::wcout << "Path source: [ " << this->m_FilePath.c_str() << " ]\n";
    }   

    auto getFilePath() const -> const std::filesystem::path& {
        return m_FilePath;
    }


private:
    std::filesystem::path m_FilePath{};
    std::ifstream m_FileImage{};

};  // END ImageLoader class

} // END kate NAMESPACE

#endif