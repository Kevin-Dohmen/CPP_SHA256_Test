#ifndef BASE64_H
#define BASE64_H

#include <cstddef> // for size_t
// #include <iostream>

class Base64 {
private:
    static char ByteToChar(unsigned char b);
    static unsigned char CharToByte(char c);
public:
    static char* Encode(const unsigned char* data, size_t input_length, size_t* output_length);
    static unsigned char* Decode(const char* data, size_t input_length, size_t* output_length);
};

#endif