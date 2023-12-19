#include "LongInt.h"

// Конвектор шістнадцяткового символу у його десяткову цифру 
uint32_t LongInt::convert_HexToDigit(char c) {
    if (c >= '0' && c <= '9') {
        return static_cast<uint32_t>(c - '0');
    }
    else if (c >= 'a' && c <= 'f') {
        return static_cast<uint32_t>(c - 'a' + 10);
    }
    else if (c >= 'A' && c <= 'F') {
        return static_cast<uint32_t>(c - 'A' + 10);
    }
    return 0;
}


// Конвектор десяткової цифри в її шістнадцятковий символ
char LongInt::convert_DigitToHex(uint32_t i, bool isSmall) {
    if (i >= 0 && i < 10) {
        return static_cast<char>('0' + i);
    }
    else if (i >= 10 && i < 16) {
        if (isSmall) {
            return static_cast<char>('a' + i - 10);
        }
        else {
            return static_cast<char>('A' + i - 10);
        }
    }
    throw std::invalid_argument("Incorrect number");
}


// Конвектор шістнадцяткового рядка у масив типу uint32_t
uint32_t* LongInt::convert_HexStringToNumber(const std::string& str) {
    uint32_t* array = new uint32_t[S]();

    std::string strReverse(str.rbegin(), str.rend());

    int cell = -1;

    for (size_t i = 0; i < strReverse.length(); i++) {
        uint32_t j = static_cast<uint32_t>(i) % 8;

        if (j == 0) {
            cell++;
        }

        uint32_t powerOfTwo = static_cast<uint32_t>(1 << (4 * j));
        uint32_t hexSymbol = convert_HexToDigit(strReverse[i]);
        array[cell] += hexSymbol * powerOfTwo;
    }

    return array;
}

// Конвектор масиву типу uint32_t у шістнадцятковий рядок
std::string LongInt::convert_NumberToHexString(uint32_t* array, bool isSmall) {
    std::string output;
    uint32_t* reverseArray = new uint32_t[S];

    for (int i = S - 1; i >= 0; i--) {
        reverseArray[i] = array[S - 1 - i];
    }

    for (int i = 0; i < S; i++) {
        std::string str;

        for (int j = 0; j < 8; j++) {
            uint32_t powerOfTwo = static_cast<uint32_t>(1 << (4 * j));

            uint32_t temp = reverseArray[i] / powerOfTwo;
            temp = temp % 16;

            str += convert_DigitToHex(temp, isSmall);
        }

        std::reverse(str.begin(), str.end());

        output += str;
    }

    size_t firstNonZero = output.find_first_not_of('0');

    if (firstNonZero != std::string::npos) {
        output = output.substr(firstNonZero);
    }
    else {
        output = "0";
    }

    delete[] reverseArray;

    return output;
}

// Конвектор BigInteger у двійковий рядок
std::string LongInt::convert_IntoBinary(const LongInt& other) const {
    std::string binString;

    for (int i = S - 1; i >= 0; i--) {
        uint32_t currentNum = other.number[i];

        for (int j = 31; j >= 0; j--) {
            uint32_t bit = (currentNum >> j) & 1;

            binString += std::to_string(bit);
        }
    }

    binString.erase(0, binString.find_first_not_of('0'));

    if (binString.empty()) {
        return "0";
    }

    return binString;
}
