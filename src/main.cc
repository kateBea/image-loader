#include <iostream>
#include <string>

#include <image.h>

int main(int, char**) {
    std::string dir{};
    std::cout << "Enter image source path: ";
    std::cin >> dir;

    std::cout << "File source path: " << dir << '\n';
    kate::ImageLoader img(dir.c_str());
    
    img.outFileData("out");

    return 0;
}