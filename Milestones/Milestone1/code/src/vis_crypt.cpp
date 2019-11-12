//
// Created by Hendrik
//

#include "../include/vis_crypt.h"
#include <algorithm>
//#include "vis_crypt.h"

// using namespace std;
// using namespace VCrypt;

// http://www.cplusplus.com/doc/tutorial/pointers/
// https://www.w3schools.com/cpp/cpp_pointers.asp

// https://www.quantstart.com/articles/Matrix-Classes-in-C-The-Header-File
// https://www.quantstart.com/articles/Matrix-Classes-in-C-The-Source-File


std::string menu = "\
Menu\n\n\
\tvisualencrypt encode <source> <result> <key>\n\
\tvisualencrypt decode <image_a> <image_b> <result>\n\
\tvisualencrypt overlay <image_a> <image_b> <result>\n";


XBild::XBild(bool isNBild) : imageMx{360, std::vector<bool>(360, false)}, xLen{360}, yLen{360}, isNBild(isNBild) {}

// create 2D Matrix with x rows filled with y columns each and all elements set to false
XBild::XBild(unsigned int x, unsigned int y, bool isNBild) : imageMx{x, std::vector<bool>(y, false)}, xLen{x}, yLen{y}, isNBild(isNBild) {
    // xLen = x; yLen = y;
    std::cout << "is N Bild: " << isNBild << std::endl;
}

XBild::~XBild() {}

// matrix assignment operation overload template
XBild &XBild::operator=(const XBild &other) {
    imageMx = other.imageMx;
    return *this;
}


// matrix move operation overload assignment template
XBild &XBild::operator=(XBild &&other) noexcept {
    imageMx = std::move(other.imageMx);
    return *this;
}


// read & write
std::vector<bool> &XBild::operator[](unsigned col) {
    if (col > xLen || col < 0)
        throw std::runtime_error("Out of range");

    return this->imageMx[col];
}

// https://isocpp.org/wiki/faq/const-correctness
// https://www.geeksforgeeks.org/function-overloading-and-const-functions/
// https://stackoverflow.com/questions/19237411/const-and-non-const-operator-overloading/19237455#19237455
// read only
const std::vector<bool> &XBild::operator[](unsigned col) const
// subscription operation overload
{
    // error detection
    if (col > this->xLen || col < 0)
        throw std::runtime_error("Out of range");

    return this->imageMx[col];    // second subscription should work as expected
}

//unsigned XBild::get_y_size() const { return this->yLen; }
 unsigned XBild::get_y_size() const { return imageMx.size() > 0 ? imageMx[0].size() : 0; }
//unsigned XBild::get_x_size() const { return this->xLen; }
 unsigned XBild::get_x_size() const { return imageMx.size(); }

// matrix construct to build x*y matrix for the image
NBild::NBild(unsigned int x, unsigned int y) : XBild::XBild(x, y, true) { //, XBild::isNBild{true} {
    // std::string typeOfClass = typeid(this).name();
    // std::string nBildStr = "NBild";
    // std::string cBildStr = "CBild";
    // std::cout << "str compare1: " << typeOfClass << typeOfClass.compare(nBildStr) << typeOfClass.compare(cBildStr) << std::endl;
    // std::cout << "str compare1: " << typeOfClass << typeOfClass.compare(nBildStr) << typeOfClass.compare(cBildStr) << std::endl;
    // std::cout << "str compare2: " << typeOfClass << (typeOfClass == nBildStr) << (typeOfClass == cBildStr) << std::endl;
}

NBild::NBild() : XBild::XBild(true) {}

NBild::~NBild() {}

// matrix construct to build x*y matrix for the image
CBild::CBild(unsigned int x, unsigned int y) : XBild::XBild(x, y, false) {}

CBild::CBild() : XBild::XBild(false) {}

CBild::~CBild() {}

void XBild::printImage() {
    for (int row = 0; row < yLen; row++) {
        for (int col = 0; col < xLen; col++) {
            std::cout << this->imageMx[row][col];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// https://codereview.stackexchange.com/questions/206852/template-matrix-class-second-version
void XBild::importFile(std::string file) {
    std::ifstream isf(file);
    if (!isf.is_open()) throw std::runtime_error("io error while reading: file not found.");

    char elem;
    std::string line; // = "";
    std::vector<bool> elems; // (xLen, false); //(xLen, false);
    // std::vector<std::vector<bool>> elemsLines;

    imageMx.clear(); // this->imageMx.clear();
    // elemsLines.clear();

    // split file by delimitors '\n' and ' '
    // https://stackoverflow.com/questions/37957080/can-i-use-2-or-more-delimiters-in-c-function-getline
    while (std::getline(isf, line, '\n')) {
    std::stringstream lines(line);
    while (std::getline(lines, line, ' ')) {
        elems.clear(); // std::vector<bool> elems;
        std::stringstream lineStream(line); // std::istringstream lineStream(lines);
        while (lineStream >> elem) {
            // if (elem == '\n')
            //     break;
            elems.push_back(elem == '1' || elem == 'A');
        }
        // lineStream.clear();
        // elemsLines.push_back(elems);
        imageMx.push_back(elems);
    }
    }

    // for (int i = 1; i < elemsLines.size(); i++) {
    for (int i = 1; i < imageMx.size(); i++) {
        // if (elemsLines[0].size() != elemsLines[i].size())
        if (imageMx[0].size() != imageMx[i].size())
            throw std::runtime_error("error: image is broken.");
    }
    // set the dimensions from the imported file
    yLen = imageMx.size(); // elemsLines.size();
    xLen = imageMx[0].size(); // elemsLines[0].size();

    isf.close();

    std::cout << "import successful" << std::endl;
    std::cout << "x: " << xLen << " y: " << yLen << std::endl;
}

void XBild::exportFile(std::string file) {
    std::ofstream osf{file};
    if (!osf) throw std::runtime_error("io error while writing: file not found.");
    // https://stackoverflow.com/questions/409348/iteration-over-stdvector-unsigned-vs-signed-index-variable/409396#409396
    for (auto const &line: imageMx) {
        for (auto const &elem: line) {
            // osf << (isNBild ? elem : (elem == 1 ? 'A' : 'B'));
            if (isNBild) {
                osf << elem;
            } else {
                osf << (elem == 1 ? 'A' : 'B');
            }
        }
        osf << std::endl;
    }
    osf.close();
    std::cout << "export successful: " << file << std::endl;
}

// task 2c
// create a random image and provide the size by parameters
// void randomImage(const unsigned int x, const unsigned int y) {}
CBild randomImage(const unsigned int x, const unsigned int y) {

}

// task 2d
// create two methods for encryption and decryption
void decode();

void encode();

// task 2e
// merge two images
// <T>
void merge();


int _main(int argc, const char **argv) {

    std::vector<std::string> options {"encode", "decode", "overlay"};

    if (argc != 5 || options.end() != std::find(options.begin(), options.end(), argv[2])) {
	std::cout << menu << std::endl;
	exit(0);
    }

    switch (argv[2][0]) {
    // case 'e': encodeCode(); break;
    // case 'd': decodeCode(); break;
    // case 'o': overlayCode(); break;
    }

    
    
    NBild imEncoded(303, 89); // bsp_bild_1 303, 89 // 2f_* 360² // inappr 360²
    CBild imDecoded; // CBild imDecoded(360, 360);

//    imEncoded.importFile("../../materials/beispielbild_1.txt");
    imEncoded.importFile("../materials/beispielbild_1.txt");
    imDecoded.importFile("../materials/2f_approval.txt");
//    imEncoded.importFile("Milestones/Milestone1/materials/beispielbild_1.txt");
    imEncoded.exportFile("../materials/beispielbild_1_OUT.txt");
    imDecoded.exportFile("../materials/2f_approval_OUT.txt");

    imEncoded.printImage();
    imDecoded.printImage();

    std::cout << "\n\nEND" << std::endl;

    return 0;
}

