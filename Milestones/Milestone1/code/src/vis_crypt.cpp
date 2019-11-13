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


XBild::XBild(bool isNBild) : imageMx{360, std::vector<bool>(360, false)}, xLen{360}, yLen{360}, isNBild(isNBild) {}

XBild::XBild(const XBild &xxBild) : imageMx{360, std::vector<bool>(360, false)}, xLen{360}, yLen{360},
                                    isNBild(isNBild) {}

XBild::XBild(const XBild &xxBild, bool isNBild) : imageMx{360, std::vector<bool>(360, false)}, xLen{360}, yLen{360},
                                                  isNBild(isNBild) {}

// create 2D Matrix with x rows filled with y columns each and all elements set to false
XBild::XBild(unsigned int x, unsigned int y, bool isNBild) : imageMx{x, std::vector<bool>(y, false)}, xLen{x}, yLen{y},
                                                             isNBild(isNBild) {
    // xLen = x; yLen = y;
    std::cout << "is N Bild: " << isNBild << std::endl;
}

XBild::~XBild() {}

NBild::NBild() : XBild::XBild(true) {}

NBild::NBild(const NBild &nnBild) : XBild::XBild(true) {}

// matrix construct to build x*y matrix for the image
NBild::NBild(unsigned int x, unsigned int y) : XBild::XBild(x, y, true) {
}

NBild::~NBild() {}

// A = true, B = false
// matrix construct to build x*y matrix for the image
CBild::CBild() : XBild::XBild(false) {}

// copy constructor (needed for returning a CBild object in randomImage)
CBild::CBild(const CBild &ccBild) : XBild::XBild(false) {}

CBild::CBild(unsigned int x, unsigned int y) : XBild::XBild(x, y, false) {}

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

unsigned XBild::get_y_size() const { return this->yLen; }

unsigned XBild::get_x_size() const { return this->xLen; }

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
                // std::cout << elem;
                elems.push_back(elem == '1' || elem == 'A');
            }
            // std::cout<< std::endl;
            elems.resize(elems.size());
            imageMx.push_back(elems);
        }
    }
    imageMx.resize(imageMx.size());

    std::cout << "imageMx.capacity():  " << imageMx.capacity() << std::endl;
    std::cout << "imageMx.size():  " << imageMx.size() << std::endl;
    std::cout << "imageMx[0].capacity():  " << imageMx[0].capacity() << std::endl;
    std::cout << "imageMx[0].size():  " << imageMx[0].size() << std::endl;

    for (int i = 1; i < imageMx.size(); i++) {
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
template<class N, class C>
void XBild::encode(N &im, C &k) {
    int imX, imY, kX, kY;
    imX = im.get_x_size();
    imY = im.get_y_size();
    kX = k.get_x_size();
    kY = k.get_y_size();
    CBild c(imX, imY);

    std::cout << imX << ' ' << kX << "  <<<< x      y >>>>  " << imY << ' ' << kY << std::endl;
    if (imX != kX || imY != kY)
        throw std::runtime_error("Dimensions error: The dimensions of the matrices to encode don't match.");

    for (int xx = 0; xx < imX; xx++) {
        for (int yy = 0; yy < imY; yy++) {
            imageMx[yy][xx] = im[yy][xx] == k[yy][xx] ? false : true;
        }
    }

    yLen = im.imageMx.size();
    xLen = im.imageMx[0].size();

    std::cout << "print encoded image:" << std::endl;
    // this->printImage();
}

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
    std::cout << "print decoded image:" << std::endl;
    this->printImage();
}

// task 2e
// merge two images
void merge();


//int _main(int argc, const char **argv) {
int main(int argc, const char **argv) {

    std::vector <std::string> options{"encode", "decode", "overlay"};

    // if (argc != 5 || options.end() != std::find(options.begin(), options.end(), argv[2])) {
    // std::cout << menu << std::endl;
    // exit(0);
    // }

    switch (argv[2][0]) {
        // case 'e': encodeCode(); break;
        // case 'd': decodeCode(); break;
        // case 'o': overlayCode(); break;
    }

    std::cout << "keyy1" << std::endl;
    CBild keyy1(10, 4); keyy1.randomImage(10,4); keyy1.printImage();
    std::cout << "keyy2" << std::endl;
    XBild keyy2(2, 6); keyy2.randomImage(2, 6); keyy2.printImage();

    NBild imDecoded; //(303, 89);
    imDecoded.importFile("../materials/beispielbild_1.txt");
    imDecoded.exportFile("../materials/beispielbild_1_OUT.txt");
    imDecoded.printImage();

    std::cout << "KEY KEY KEY KEY" << std::endl;
    std::cout << "KEY KEY KEY KEY" << std::endl;
    std::cout << "KEY KEY KEY KEY" << std::endl;
    // CBild key2(imDecoded.get_x_size(), imDecoded.get_y_size());
    // CBild key(imDecoded.get_x_size(), imDecoded.get_y_size());
    CBild key(imDecoded.get_y_size(), imDecoded.get_x_size());
    key.randomImage(imDecoded.get_x_size(), imDecoded.get_y_size());
    key.exportFile("../materials/beispielbild_1_OUT_key.txt");
    // key.printImage();

    std::cout << "ENCODE ENCODE ENCODE ENCODE" << std::endl;
    std::cout << "ENCODE ENCODE ENCODE ENCODE" << std::endl;
    std::cout << "ENCODE ENCODE ENCODE ENCODE" << std::endl;
    CBild imEncoded(imDecoded.get_x_size(), imDecoded.get_y_size());
    imEncoded.encode(imDecoded, key);
    imEncoded.exportFile("../materials/beispielbild_1_OUT_en.txt");
    // imEncoded.printImage();

    std::cout << "DECODE DECODE DECODE DECODE" << std::endl;
    std::cout << "DECODE DECODE DECODE DECODE" << std::endl;
    std::cout << "DECODE DECODE DECODE DECODE" << std::endl;

    CBild im2Encoded;
    CBild im2Key;
    NBild im2Decoded;

    im2Encoded.importFile("../materials/beispielbild_1_OUT.txt");
    std::cout << "____DECODE DECODE DECODE DECODE" << std::endl;
    im2Encoded.printImage();
    std::cout << "____DECODE DECODE DECODE DECODE" << std::endl;
    im2Key.importFile("../materials/beispielbild_1_OUT_key.txt");

    im2Decoded.decode(im2Encoded, im2Key);
    std::cout << "____DECODE DECODE DECODE DECODE" << std::endl;
    im2Decoded.exportFile("../materials/beispielbild_1_OUT_de.txt");

    std::cout << "\n\nEND" << std::endl;

    return 0;
}
