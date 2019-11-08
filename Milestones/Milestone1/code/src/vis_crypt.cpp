//
// Created by Hendrik
//

#include "../include/vis_crypt.h"
// #include "vis_crypt.h"

// using namespace VCrypt;

VCrypt::XBild::XBild() {}

// TODO: fill ImageMx with 0s or maybe with noise or maybe with data
VCrypt::XBild::XBild(unsigned int x, unsigned int y) : imageMx{x, std::vector<bool>(y)} {}

VCrypt::XBild::~XBild() {}

VCrypt::NBild::NBild(unsigned int x, unsigned int y) : VCrypt::XBild::XBild(x, y) {}

VCrypt::NBild::NBild() : VCrypt::XBild::XBild() {}

VCrypt::NBild::~NBild() {}

VCrypt::CBild::CBild(unsigned int x, unsigned int y) : VCrypt::XBild::XBild(x, y) {}

VCrypt::CBild::CBild() : VCrypt::XBild::XBild() {}

VCrypt::CBild::~CBild() {}

void VCrypt::XBild::importFile(std::string file) {
    std::ifstream isf{file};
    if (!isf) throw std::runtime_error("io error while reading: file not found.");
    // TODO: copy file to imageMx
//    for (int x = 0; x < )
    std::cout << "import successful" << std::endl;
}

void VCrypt::XBild::exportFile(std::string file) {
    std::ofstream osf{file};
    if (!osf) throw std::runtime_error("io error while writing: file not found.");
    //TODO: write image to file
    std::cout << "export successful" << std::endl;
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
    VCrypt::NBild imEncoded(10, 10);
    VCrypt::CBild imDecoded;

//    imEncoded.importFile("../../materials/beispielbild_1.txt");
    imEncoded.importFile("../materials/beispielbild_1.txt");
//    imEncoded.importFile("Milestones/Milestone1/materials/beispielbild_1.txt");

    std::cout << "hi" << std::endl;
}