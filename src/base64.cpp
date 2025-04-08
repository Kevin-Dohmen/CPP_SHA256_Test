#include "base64.h"

char Base64::ByteToChar(unsigned char b){
    const char b64Chars[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ" // 0-25
        "abcdefghijklmnopqrstuvwxyz" // 26-51
        "0123456789+/"; // 52-63

    if (b < 64){
        return b64Chars[b];
    }
    return '=';
}

unsigned char Base64::CharToByte(char c) { // make lookup table?
    if (c >= 'A' && c <= 'Z') {
        return (unsigned char)(c - 'A');
    } else if (c >= 'a' && c <= 'z') {
        return (unsigned char)(c - 'a' + 26);
    } else if (c >= '0' && c <= '9') {
        return (unsigned char)(c - '0' + 52);
    } else if (c == '+') {
        return 62u;
    } else if (c == '/') {
        return 63u;
    }
    return 0xFFu;
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
