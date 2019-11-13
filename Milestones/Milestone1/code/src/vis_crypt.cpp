//
// Created by Hendrik
//

#include "../include/vis_crypt.h"
#include <algorithm>

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


//constructor
XBild::XBild(bool isNBild) : imageMx{360, std::vector<bool>(360, false)}, xLen{360}, yLen{360}, isNBild(isNBild) {}

XBild::XBild(const XBild &xxBild) : imageMx{360, std::vector<bool>(360, false)}, xLen{360}, yLen{360},
                                    isNBild(isNBild) {}

XBild::XBild(const XBild &xxBild, bool isNBild) : imageMx{360, std::vector<bool>(360, false)}, xLen{360}, yLen{360},
                                                  isNBild(isNBild) {}

// create 2D Matrix with x rows filled with y columns each and all elements set to false
XBild::XBild(unsigned int x, unsigned int y, bool isNBild) : imageMx{x, std::vector<bool>(y, false)}, xLen{x}, yLen{y},
                                                             isNBild(isNBild) {
    // xLen = x; yLen = y;
}

// destructor
XBild::~XBild() {}

// constructor
NBild::NBild() : XBild::XBild(true) {}

NBild::NBild(const NBild &nnBild) : XBild::XBild(true) {}

// matrix construct to build x*y matrix for the image
NBild::NBild(unsigned int x, unsigned int y) : XBild::XBild(x, y, true) {
}

//  destructor
NBild::~NBild() {}

// constructor
CBild::CBild() : XBild::XBild(false) {}

// copy constructor (needed for returning a CBild object in randomImage)
CBild::CBild(const CBild &ccBild) : XBild::XBild(false) {}

CBild::CBild(unsigned int x, unsigned int y) : XBild::XBild(x, y, false) {}

// destructor
CBild::~CBild() {}

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

// getter for dimension of matrix
unsigned XBild::get_y_size() const { return this->yLen; }

unsigned XBild::get_x_size() const { return this->xLen; }

// print function used for development
void XBild::printImage() {
    for (int row = 0; row < yLen; row++) {
        for (int col = 0; col < xLen; col++) {
            std::cout << this->imageMx[row][col];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// import a file from a file given as parameter
// https://codereview.stackexchange.com/questions/206852/template-matrix-class-second-version
void XBild::importFile(std::string file) {
    std::ifstream isf(file);
    if (!isf.is_open()) throw std::runtime_error("io error while reading: file not found.");

    char elem;
    std::string line;
    std::vector<bool> elems;

    // for (auto &line: imageMx) {
    //     // for (auto const &elem: line) {
    //         line.clear();
    //     // }
    // }
    imageMx.clear();
    // elems.resize(500);
    // imageMx.resize(500);

    // split file by delimitors '\n' and ' '
    // https://stackoverflow.com/questions/37957080/can-i-use-2-or-more-delimiters-in-c-function-getline
    while (std::getline(isf, line, '\n')) {
        std::stringstream lines(line);
        while (std::getline(lines, line, ' ')) {
            elems.clear();
            std::stringstream lineStream(line);
            while (lineStream >> elem) {
                elems.push_back(elem == '1' || elem == 'A');
            }
            elems.resize(elems.size());
            imageMx.push_back(elems);
        }
    }
    imageMx.resize(imageMx.size());

    for (int i = 1; i < imageMx.size(); i++) {
        if (imageMx[0].size() != imageMx[i].size())
            throw std::runtime_error("error: image is broken.");
    }
    // set the dimensions from the imported file
    yLen = imageMx.size(); // elemsLines.size();
    xLen = imageMx[0].size(); // elemsLines[0].size();

    isf.close();

    std::cout << "import successful" << std::endl;
}

// export an image to a textfile
void XBild::exportFile(std::string file) {
    std::ofstream osf{file};
    if (!osf) throw std::runtime_error("io error while writing: file not found.");
    // https://stackoverflow.com/questions/409348/iteration-over-stdvector-unsigned-vs-signed-index-variable/409396#409396
    // for (auto const &line: imageMx) {
    //     for (auto const &elem: line) {
    //         // osf << (isNBild ? elem : (elem == 1 ? 'A' : 'B'));
    //         if (isNBild) {
    //             osf << elem;
    //         } else {
    //             osf << (elem == 1 ? 'A' : 'B');
    //         }
    //     }
    //     osf << std::endl;
    // }
    for (int row = 0; row < yLen; row++) {
        for (int col = 0; col < xLen; col++) {
            if (isNBild) {
                osf << imageMx[row][col];
            } else {
                osf << (imageMx[row][col] == 1 ? 'A' : 'B');
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

// create a random pixels picture used as a key for encryption (the dimensions have to be provided as arguments)
// https://de.wikibooks.org/wiki/C%2B%2B-Programmierung/_Im_Zusammenhang_mit_Klassen/_Statische_Methoden
// https://www.tutorialspoint.com/cplusplus/cpp_static_members.htm
void XBild::randomImage(const unsigned int x, const unsigned int y) {
    srand(time(NULL));

    int randPixel;
    std::vector<bool> elems;

    imageMx.clear();


    for (int yy = 0; yy < y; yy++) {
        elems.clear();
        for (int xx = 0; xx < x; xx++) {
            randPixel = rand() % 2;
            elems.push_back(randPixel > 0);
            // imageMx[yy][xx] = randPixel > 0; // ? true : false;
        }
        elems.resize(elems.size());
        imageMx.push_back(elems);
    }
    imageMx.resize(imageMx.size());

    yLen = imageMx.size(); // y;
    xLen = imageMx[0].size(); // x;
}

// task 2d
// create two methods for encryption and decryption
// https://www.internalpointers.com/post/move-smart-pointers-and-out-functions-modern-c
// https://www.geeksforgeeks.org/auto_ptr-unique_ptr-shared_ptr-weak_ptr-2/
// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rr-sharedptrparam
// https://stackoverflow.com/questions/3350385/how-to-return-an-object-in-c/3350439#3350439
// https://stackoverflow.com/questions/8293426/error-invalid-initialization-of-non-const-reference-of-type-int-from-an-rval

// encode an image with a given key
template<class N, class C>
void XBild::encode(N &im, C &k) {
    int imX, imY, kX, kY;
    imX = im.get_x_size();
    imY = im.get_y_size();
    kX = k.get_x_size();
    kY = k.get_y_size();
    CBild c(imX, imY);

    if (imX != kX || imY != kY)
        throw std::runtime_error("Dimensions error: The dimensions of the matrices to encode don't match.");

    for (int xx = 0; xx < imX; xx++) {
        for (int yy = 0; yy < imY; yy++) {
            imageMx[yy][xx] = im[yy][xx] == k[yy][xx] ? false : true;
        }
    }

    yLen = im.imageMx.size();
    xLen = im.imageMx[0].size();

    // std::cout << "print encoded image:" << std::endl;
//     this->printImage();
}

template void XBild::encode<NBild, CBild>(NBild &, CBild &);

// decode an image using the encryption key
template<class C>
void XBild::decode(C &im, C &k) {
    int imX, imY, kX, kY;
    imX = im.get_x_size();
    imY = im.get_y_size();
    kX = k.get_x_size();
    kY = k.get_y_size();
    NBild d(imX, imY);

    if (imX != kX || imY != kY)
        throw std::runtime_error("Dimensions error: The dimensions of the matrices to decode don't match.");

    for (int yy = 0; yy < imY; yy++) {
        for (int xx = 0; xx < imX; xx++) {
            imageMx[yy][xx] = im[yy][xx] == k[yy][xx] ? false : true;
            // imageMx[xx][yy] = im[yy][xx] == k[yy][xx] ? false : true;
            // imageMx[yy][xx] = im[xx][yy] == k[xx][yy] ? false : true;
            // imageMx[xx][yy] = im[xx][yy] == k[xx][yy] ? false : true;
        }
    }
    yLen = im.imageMx.size();
    xLen = im.imageMx[0].size();
    // std::cout << "print decoded image:" << std::endl;
    // this->printImage();
}

template void XBild::decode<CBild>(CBild &, CBild &);

// task 2e
// merge two images
// ===> we can use the encode functionality to achieve that (see overlayCode())

// task 2g
// console ui methods
// g++ src/vis_crypt.cpp include/vis_crypt.h && ./a.out encode ../materials/2f_approval.txt ../materials/_ENCODED.txt ../materials/2f_bugaspicture.txt
void encodeCode(const char *source, const char *result, const char *key) {
    NBild imDecoded;
    imDecoded.importFile(source);

    CBild imKey(imDecoded.get_y_size(), imDecoded.get_x_size());
    imKey.importFile(key);
    // imKey.randomImage(imDecoded.get_x_size(), imDecoded.get_y_size());

    CBild imEncoded(imDecoded.get_x_size(), imDecoded.get_y_size());
    imEncoded.encode(imDecoded, imKey);
    imEncoded.exportFile(result);
}

// g++ src/vis_crypt.cpp include/vis_crypt.h && ./a.out decode ../materials/_ENCODED.txt ../materials/2f_bugaspicture.txt ../materials/_DECODED.txt
void decodeCode(const char *im, const char *k, const char *res) {
    CBild imEncoded;
    CBild imKey;
    NBild imDecoded;

    imEncoded.importFile(im);
    imKey.importFile(k);

    imDecoded.decode(imEncoded, imKey);
    imDecoded.exportFile(res);
}

// g++ src/vis_crypt.cpp include/vis_crypt.h && ./a.out overlay ../materials/2f_bugaspicture.txt ../materials/2f_approval.txt ../materials/_MERGE.txt
void overlayCode(const char *im, const char *k, const char *res) {
    NBild imDecoded;
    imDecoded.importFile(im);

    CBild imKey(imDecoded.get_y_size(), imDecoded.get_x_size());
    imKey.importFile(k);
    // imKey.randomImage(imDecoded.get_x_size(), imDecoded.get_y_size());

    CBild imEncoded(imDecoded.get_x_size(), imDecoded.get_y_size());
    imEncoded.encode(imDecoded, imKey);
    imEncoded.exportFile(res);
}


#ifndef VISCRYPT_NOMAIN

int main(int argc, const char **argv) {

    // console UI
    std::vector <std::string> options{"encode", "decode", "overlay"};

    if (argc != 5 || options.end() != std::find(options.begin(), options.end(), argv[2])) {
        std::cout << menu << std::endl;
        exit(0);
    }

    switch (argv[1][0]) {

        case 'e':
            encodeCode(argv[2], argv[3], argv[4]);
            break;
        case 'd':
            decodeCode(argv[2], argv[3], argv[4]);
            break;
        case 'o':
            overlayCode(argv[2], argv[3], argv[4]);
            break;
    }

    // some examples for the code above
    if (false) {
        std::cout << "keyy1" << std::endl;
        CBild keyy1(10, 4);
        keyy1.randomImage(10, 4);
        keyy1.printImage();
        std::cout << "keyy2" << std::endl;
        XBild keyy2(2, 6);
        keyy2.randomImage(2, 6);
        keyy2.printImage();

        NBild imDecoded; //(303, 89);
        imDecoded.importFile("../materials/2f_approval.txt");
        // imDecoded.importFile("../materials/beispielbild_1.txt");
        imDecoded.exportFile("../materials/2f_approval_OUT.txt");
        imDecoded.printImage();
        // imDecoded2.printImage();

        std::cout << "KEY KEY KEY KEY" << std::endl;
        std::cout << "KEY KEY KEY KEY" << std::endl;
        std::cout << "KEY KEY KEY KEY" << std::endl;
        // CBild key2(imDecoded.get_x_size(), imDecoded.get_y_size());
        // CBild key(imDecoded.get_x_size(), imDecoded.get_y_size());
        CBild key(imDecoded.get_y_size(), imDecoded.get_x_size());
        key.randomImage(imDecoded.get_x_size(), imDecoded.get_y_size());
        key.exportFile("../materials/2f_approval_OUT_key.txt");
        // key.printImage();
        CBild key2;
        key2.importFile("../materials/2f_bugaspicture.txt");

        std::cout << "ENCODE ENCODE ENCODE ENCODE" << std::endl;
        std::cout << "ENCODE ENCODE ENCODE ENCODE" << std::endl;
        std::cout << "ENCODE ENCODE ENCODE ENCODE" << std::endl;
        CBild imEncoded(imDecoded.get_x_size(), imDecoded.get_y_size());
        CBild imEncoded2(imDecoded.get_x_size(), imDecoded.get_y_size());
        imEncoded.encode(imDecoded, key);
        imEncoded.exportFile("../materials/2f_approval_OUT_en.txt");
        imEncoded.printImage();
        imEncoded2.encode(imDecoded, key2);
        imEncoded2.exportFile("../materials/2f_bugaspicture_OUT_en.txt");
        imEncoded2.printImage();

        std::cout << "DECODE DECODE DECODE DECODE" << std::endl;
        std::cout << "DECODE DECODE DECODE DECODE" << std::endl;
        std::cout << "DECODE DECODE DECODE DECODE" << std::endl;

        CBild im2Encoded;
        CBild im2Encoded2;
        CBild im2Key;
        CBild im2Key2;
        NBild im2Decoded;
        NBild im2Decoded2;
        im2Encoded.importFile("../materials/2f_approval_OUT_en.txt");
        im2Encoded2.importFile("../materials/2f_bugaspicture_OUT_en.txt");
        im2Key.importFile("../materials/2f_approval_OUT_key.txt");
        im2Key.importFile("../materials/2f_bugaspicture.txt");
        im2Decoded.decode(im2Encoded, im2Key);
        im2Decoded2.decode(im2Encoded2, im2Key2);
        im2Decoded.exportFile("../materials/2f_approval_OUT_de.txt");

        std::cout << "\n\nEND" << std::endl;
    }

    return 0;
}

#endif
