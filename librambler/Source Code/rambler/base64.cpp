/**********************************************************************************************************************
 * @file    base64.cpp
 * @date    2014-07-05
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#include "base64.hpp"
#include <iostream>

namespace rambler { namespace base64 {

    char encodeDigit(UInt8 uint6) {
        char encodedDigit;
        switch (uint6) {
            case  0: case  1: case  2: case  3: case  4: case  5: case  6: case  7: case  8: case  9:
            case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 19:
            case 20: case 21: case 22: case 23: case 24: case 25:
                encodedDigit = 'A' + uint6;
                break;
            case 26: case 27: case 28: case 29: case 30: case 31: case 32: case 33: case 34: case 35:
            case 36: case 37: case 38: case 39: case 40: case 41: case 42: case 43: case 44: case 45:
            case 46: case 47: case 48: case 49: case 50: case 51:
                encodedDigit = 'a' + uint6 - 26;
                break;
            case 52: case 53: case 54: case 55: case 56: case 57: case 58: case 59: case 60: case 61:
                encodedDigit = '0' + uint6 - 52;
                break;
            case 62:
                encodedDigit = '+';
                break;
            case 63:
                encodedDigit = '/';
                break;
            case 64:
                encodedDigit = '=';
                break;
            default:
                encodedDigit = '\0';
                break;
        }

        return encodedDigit;
    }

    UInt8 decodeDigit(char digit) {
        switch (digit) {
            case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G': case 'H': case 'I': case 'J':
            case 'K': case 'L': case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T':
            case 'U': case 'V': case 'W': case 'X': case 'Y': case 'Z':
                return digit - 'A' + 0;
            case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': case 'h': case 'i': case 'j':
            case 'k': case 'l': case 'm': case 'n': case 'o': case 'p': case 'q': case 'r': case 's': case 't':
            case 'u': case 'v': case 'w': case 'x': case 'y': case 'z':
                return digit - 'a' + 26;
            case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
                return digit - '0' + 52;
            case '+':
                return 62;
            case '/':
                return 63;
            case '=':
                return 64;
            default:
                return 65;
        }
    }

    String encodeBytes(UInt8 first, UInt8 second, UInt8 third) {
        UInt32 packed = 0 | (first << 16) | (second << 8) | (third);

        UInt8 uint6[4];
        uint6[0] = (packed & 0x00FC0000) >> 18;
        uint6[1] = (packed & 0x0003F000) >> 12;
        uint6[2] = (packed & 0x00000FC0) >>  6;
        uint6[3] = (packed & 0x0000003F);

        String encodedString;
        encodedString.reserve(4);

        encodedString += encodeDigit(uint6[0]);
        encodedString += encodeDigit(uint6[1]);
        encodedString += encodeDigit(uint6[2]);
        encodedString += encodeDigit(uint6[3]);

        return encodedString;
    }

    String encodeBytes(UInt8 first, UInt8 second) {
        UInt32 packed = 0 | (first << 16) | (second << 8);

        UInt8 uint6[3];
        uint6[0] = (packed & 0x00FC0000) >> 18;
        uint6[1] = (packed & 0x0003F000) >> 12;
        uint6[2] = (packed & 0x00000FC0) >>  6;

        String encodedString;
        encodedString.reserve(4);

        encodedString += encodeDigit(uint6[0]);
        encodedString += encodeDigit(uint6[1]);
        encodedString += encodeDigit(uint6[2]);
        encodedString += '=';

        return encodedString;
    }

    String encodeByte(UInt8 first) {
        UInt32 packed = 0 | (first << 16);

        UInt8 uint6[2];
        uint6[0] = (packed & 0x00FC0000) >> 18;
        uint6[1] = (packed & 0x0003F000) >> 12;

        String encodedString;
        encodedString.reserve(4);

        encodedString += encodeDigit(uint6[0]);
        encodedString += encodeDigit(uint6[1]);
        encodedString += '=';
        encodedString += '=';

        return encodedString;
    }

    String encode(String string)
    {
        std::vector<UInt8> data(string.begin(), string.end());
        return encode(data);
    }

    String encode(std::vector<UInt8> bytes)
    {
        String encodedString;
        size_t numberOfBytes = bytes.size();

        encodedString.reserve(numberOfBytes * 4 / 3 + 1);

        for (size_t i = 3; i < numberOfBytes; i += 3) {
            encodedString += encodeBytes(bytes[i - 3], bytes[i - 2], bytes[i - 1]);
        }

        switch (numberOfBytes % 3) {
            case 2:
                encodedString += encodeBytes(bytes[numberOfBytes - 2], bytes[numberOfBytes - 1]);
                break;
            case 1:
                encodedString += encodeByte(bytes[numberOfBytes - 1]);
                break;
            case 0:
                encodedString += encodeBytes(bytes[numberOfBytes - 3], bytes[numberOfBytes - 2], bytes[numberOfBytes - 1]);
        }

        return encodedString;
    }

    std::vector<UInt8> decode(String encodedString) {
        UInt numberOfDigits = encodedString.length();

        if (numberOfDigits % 4 != 0) {
            return {};
        }

        std::vector<UInt8> bytes;
        for (UInt i = 0; i < numberOfDigits; i += 4) {
            UInt8 uint6[4];
            uint6[0] = decodeDigit(encodedString[i + 0]);
            uint6[1] = decodeDigit(encodedString[i + 1]);
            uint6[2] = decodeDigit(encodedString[i + 2]);
            uint6[3] = decodeDigit(encodedString[i + 3]);

            UInt numberOfBytes;
            UInt32 packed = 0;

            if (uint6[2] == 64) {
                numberOfBytes = 1;
                packed = uint6[0] << 18 | uint6[1] << 12;
            } else if (uint6[3] == 64) {
                numberOfBytes = 2;
                packed = uint6[0] << 18 | uint6[1] << 12 | uint6[2] << 6;
            } else {
                numberOfBytes = 3;
                packed = uint6[0] << 18 | uint6[1] << 12 | uint6[2] << 6 | uint6[3];
            }

            for (UInt i = 0; i < numberOfBytes; ++i) {
                UInt8 byte = (0xFF << (16 - i * 8) & packed) >> (16 - i * 8);
                bytes.push_back(byte);
            }

        }

        return bytes;
    }

    String decodeAsString(String encodedString) {
        auto vector = decode(encodedString);

        return String(vector.begin(), vector.end());
    }

}}