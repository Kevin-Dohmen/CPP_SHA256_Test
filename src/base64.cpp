#include "base64.h"

static const char b2c_lt[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ" // 0-25
    "abcdefghijklmnopqrstuvwxyz" // 26-51
    "0123456789+/"; // 52-63

static const unsigned char c2b_lt[256] = {
//  -0    -1    -2    -3    -4    -5    -6    -7    -8    -9    -A    -B    -C    -D    -E    -F
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 0- |   0 -  15
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 1- |  16 -  31
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3E, 0xFF, 0xFF, 0xFF, 0x3F, // 2- |  32 -  47 | 43 = '+' = 62 = 0x3E | 47 = '/' = 63 = 0x3F
    0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 3- |  48 -  63 | 48 = '0' = 52 = 0x34 | 57 = '9' = 61 = 0x3D
    0xFF, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, // 4- |  64 -  79 | 65 = 'A' = 0 = 0x00
    0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 5- |  80 -  95 | 90 = 'Z' = 25 = 0x19
    0xFF, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, // 6- |  96 - 111 | 97 = 'a' = 26 = 0x1A
    0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 7- | 112 - 127 | 122 = 'z' = 51 = 0x33
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 8- | 128 - 143
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 9- | 144 - 159
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // A- | 160 - 175
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // B- | 176 - 191
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // C- | 192 - 207
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // D- | 208 - 223
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // E- | 224 - 239
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF  // F- | 240 - 255
};

char Base64::ByteToChar(unsigned char b){
    return b < 64 ? b2c_lt[b] : '=';
}

unsigned char Base64::CharToByte(char c) {
    return c2b_lt[static_cast<unsigned char>(c)];
}

char* Base64::Encode(const unsigned char* data, size_t input_length, size_t* output_length){
    size_t encodedLen = 4 * ((input_length + 2) / 3);
    char* encoded = new char[encodedLen + 1];

    size_t dataIndex = 0;
    size_t encodedIndex = 0;

    unsigned int buffer = 0;
    int bitsInBuffer = 0;

    while (dataIndex < input_length){
        buffer = (buffer << 8) | data[dataIndex++];
        bitsInBuffer += 8;

        while (bitsInBuffer >= 6){
            encoded[encodedIndex++] = ByteToChar((buffer >> (bitsInBuffer - 6)) & 0x3F);
            bitsInBuffer -= 6;
        }
    }

    if (bitsInBuffer > 0) {
        buffer <<= (6 - bitsInBuffer);
        encoded[encodedIndex++] = ByteToChar(buffer & 0x3F);
    }

    while (encodedIndex < encodedLen) {
        encoded[encodedIndex++] = '=';
    }

    encoded[encodedIndex] = '\0';

    *output_length = encodedLen;
    return encoded;
}

unsigned char* Base64::Decode(const char* data, size_t input_length, size_t* output_length){
    size_t padding = 0;
    if (input_length >= 2) {
        if (data[input_length - 1] == '=') padding++;
        if (data[input_length - 2] == '=') padding++;
    }
    size_t decodedLen = (input_length / 4) * 3 - padding;
    unsigned char* decoded = new unsigned char[decodedLen];

    size_t dataIndex = 0;
    size_t decodedIndex = 0;
    
    unsigned int buffer = 0;
    int bitsInBuffer = 0;

    while (dataIndex < input_length){
        buffer = (buffer << 6) | (CharToByte(data[dataIndex++]) & 0x3F);
        bitsInBuffer += 6;

        if (bitsInBuffer >= 8){
            decoded[decodedIndex++] = (buffer >> (bitsInBuffer - 8)) & 0xFF;
            bitsInBuffer -= 8;
        }
    }

    *output_length = decodedLen;
    return decoded;
}
