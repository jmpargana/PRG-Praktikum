//
// Created by Hendrik
//

#ifndef PRG_PR_VIS_CRYPT_H
#define PRG_PR_VIS_CRYPT_H

//#include "matrix.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <sstream>
#include <algorithm>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <memory>

//using namespace std;

//namespace VCrypt {

// template <typename T>
class XBild {
public:
    // constructor
    XBild(bool);

    XBild(const XBild& xxBild);

    XBild(const XBild& xxBild, bool);

    XBild(unsigned int, unsigned int, bool);

    // assignment operator
    XBild &operator=(const XBild &);

    // move constructor and move operator
    XBild &operator=(XBild &&) noexcept;

    // read & write
    std::vector<bool> &operator[](unsigned);

    // read only
    const std::vector<bool> &operator[](unsigned) const;

    // destructor
    ~XBild();

    void printImage();

    unsigned get_x_size() const;

    unsigned get_y_size() const;

    // methods
    void importFile(std::string);

    void exportFile(std::string);

    void randomImage3(const unsigned int x, const unsigned int y);
    // XBild randomImage(unsigned, unsigned);
    // CBild randomImage(unsigned, unsigned);

//    void encode(NBild&, CBild&);
    template <class N, class C> void encode(N&, C&);
//    void decode(CBild);
    // void encode(NBild &im, CBild &k) {};


private:
    // image in matrix representation
    std::vector<std::vector<bool>> imageMx;
    unsigned xLen, yLen;
    bool isNBild;
};

class NBild : public XBild {
public:
    NBild();
    NBild(const NBild& nnBild);

    NBild(unsigned int x, unsigned int y);

    // void decode(CBild &im, CBild &k) {};

    ~NBild();

private:
};

class CBild : public XBild {
public:
    CBild();

    CBild(const CBild& ccBild); // copy constructor

    CBild(unsigned int x, unsigned int y);

    // void encode(NBild &im, CBild &k) {};
    // void encode(NBild &im, CBild &k) {};

    ~CBild();

private:
};

//} // namespace VCrypt

#endif //PRG_PR_VIS_CRYPT_H
