#include <kt_image.h>
#include <iostream>
#include <string>

int main(int, char**) {
    std::string dir{};
    std::cout << "Enter image source path: ";
    std::cin >> dir;
    kate::ImageLoader img(dir.c_str());
    
    img.outFileData("out");

    return 0;
}