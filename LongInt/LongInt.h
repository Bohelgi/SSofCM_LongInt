#pragma once

#ifndef LongInt_H 
#define LongInt_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <random>
#include <bitset>
#include <cassert>

class LongInt {
private:
    static const int S = 256;
    uint32_t number[S];
public:

    uint32_t* getNumber() {
        return number;
    }

    LongInt();

    LongInt(const std::string& hexValue);

    static LongInt GenerateRandomLongInt(int size);

    static uint32_t convert_HexToDigit(char c);
    static char convert_DigitToHex(uint32_t i, bool isSmall = false);
    static uint32_t* convert_HexStringToNumber(const std::string& str);
    static std::string convert_NumberToHexString(uint32_t* array, bool isSmall = false);
    std::string convert_IntoBinary(const LongInt& other) const;

    LongInt operator+(const LongInt& other) const;
    LongInt operator-(const LongInt& other) const;
    LongInt operator*(const uint32_t other) const;
    LongInt operator*(const LongInt& other) const;
    LongInt operator/(const LongInt& other) const;
    LongInt operator%(const LongInt& other) const;

    LongInt operator >> (int b) const;
    LongInt operator << (int b) const;

    bool operator==(const LongInt& other) const;
    bool operator!=(const LongInt& other) const;
    bool operator<(const LongInt& other) const;
    bool operator>(const LongInt& other) const;
    bool operator<=(const LongInt& other) const;
    bool operator>=(const LongInt& other) const;

    LongInt square() const;
    int Bit_Length() const;
    LongInt LongShiftBits_ToHigh(int bits) const;
    LongInt pow(const LongInt& exponent) const;
};
#endif