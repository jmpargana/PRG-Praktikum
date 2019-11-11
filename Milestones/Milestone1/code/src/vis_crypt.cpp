//
// Created by Hendrik
//

#include "../include/vis_crypt.h"
//#include "vis_crypt.h"

// using namespace std;
// using namespace VCrypt;

// https://www.quantstart.com/articles/Matrix-Classes-in-C-The-Header-File
// https://www.quantstart.com/articles/Matrix-Classes-in-C-The-Source-File

XBild::XBild() {}

// create 2D Matrix with x rows filled with y columns each and all elements set to false
XBild::XBild(unsigned int x, unsigned int y) : imageMx{x, std::vector<bool>(y, false)} {
    xLen = x;
    yLen = y;
}
//XBild::XBild(unsigned int x, unsigned int y) {
//    imageMx.resize(x);
//    for (unsigned row = 0; row < imageMx.size(); row++) {
//        imageMx[row].resize(y, false);
//    }
//    xLen = x; yLen = y;
//}

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


// unsigned XBild::get_x_size() const { return imageMx.size(); }
// unsigned XBild::get_y_size() const { return imageMx[0].size(); }
unsigned XBild::get_x_size() const { return this->xLen; }

unsigned XBild::get_y_size() const { return this->yLen; }

// matrix construct to build x*y matrix for the image
NBild::NBild(unsigned int x, unsigned int y) : XBild::XBild(x, y) {}

NBild::NBild() : XBild::XBild() {}

NBild::~NBild() {}

// matrix construct to build x*y matrix for the image
CBild::CBild(unsigned int x, unsigned int y) : XBild::XBild(x, y) {}

CBild::CBild() : XBild::XBild() {}

CBild::~CBild() {}

void XBild::printImage() {
    for (int row = 0; row < yLen; row++) {
        for (int col = 0; col < xLen; col++) {
            std::cout << this->imageMx[row][col];
        }
        std::cout << std::endl;
    }
}

// https://codereview.stackexchange.com/questions/206852/template-matrix-class-second-version
void XBild::importFile(std::string file) {
    std::ifstream isf(file);
    if (!isf.is_open()) throw std::runtime_error("io error while reading: file not found.");

    char elem;
    std::string lines; // = "";
    std::vector<bool> elems; // (xLen, false); //(xLen, false);

    imageMx.clear(); // this->imageMx.clear();

    while (std::getline(isf, lines)) {
        elems.clear(); // std::vector<bool> elems;
        std::stringstream lineStream(lines); // std::istringstream lineStream(lines);
        while (lineStream >> elem) {
            elems.push_back(elem == '1' || elem == 'A');
        }
        // lineStream.clear();
        imageMx.push_back(elems);
    }

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
            osf << elem;
        }
        osf << std::endl;
    }
    osf.close();
    std::cout << "export successful: " << file << std::endl;
}

// task 2c
// create a random image and provide the size by parameters
void randomImage(const unsigned int x, const unsigned int y) {}

// task 2d
// create two methods for encryption and decryption
void decode();

void encode();

// task 2e
// merge two images
// <T>
void merge();


int main(int argc, const char **argv) {
    // NBild imEncoded(303, 89); // bsp_bild_1 303, 89 // 2f_* 360² // inappr 360²
    XBild imEncoded(303, 89); // bsp_bild_1 303, 89 // 2f_* 360² // inappr 360²
    CBild imDecoded;

//    imEncoded.importFile("../../materials/beispielbild_1.txt");
    imEncoded.importFile("../materials/beispielbild_1.txt");
//    imEncoded.importFile("Milestones/Milestone1/materials/beispielbild_1.txt");
    imEncoded.exportFile("../materials/beispielbild_1_OUT.txt");

    // std::cout << imEncoded.printImage() << std::endl;
    imEncoded.printImage();
    std::cout << "\n\nEND" << std::endl;

    return 0;
}

