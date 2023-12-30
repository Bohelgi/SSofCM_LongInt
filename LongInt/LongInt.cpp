#include "LongInt.h"

// ����������� �� ������������� ��� ����������� LongInt �����
LongInt::LongInt() {
    for (int i = 0; i < S; i++) {
        number[i] = 0;
    }
}

// ����������� ��� ����������� ���� LongInt � ���������������� �����
LongInt::LongInt(const std::string& hexValue) {

    uint32_t* hexArray = convert_HexStringToNumber(hexValue);
    for (int i = 0; i < S; i++) {
        number[i] = hexArray[i];
    }
}

// ��������� ����� ��������� ����������� ���� LongInt �������� ������
LongInt LongInt::GenerateRandomLongInt(int size) {
    if (size == 0) size = S;

    LongInt randLongInt;
    std::random_device    rd;
    std::mt19937      generator(rd());
    std::uniform_int_distribution<uint32_t>  distr(0, UINT_MAX);

    for (int i = 0; i < size; ++i) {
        uint32_t randomValue = static_cast<uint32_t>(distr(generator));

        randLongInt.number[i] = randomValue;
    }

    return randLongInt;
}

// �������� ��������� ��� LongInt
LongInt LongInt::operator + (const LongInt& other) const {
    uint32_t carry = 0;
    LongInt result;
    for (int i = 0; i < S; i++) {

        uint64_t temp = static_cast<uint64_t>(number[i]) + static_cast<uint64_t>(other.number[i]) + carry;

        result.number[i] = static_cast<uint32_t>(temp & 0xFFFFFFFF);

        carry = static_cast<uint32_t>(temp >> 32);
    }
    return result;
}

// �������� �������� ��� LongInt
LongInt LongInt::operator - (const LongInt& other) const {
    if (*this < other)
    {
        return LongInt();
    }

    uint32_t borrow = 0;
    LongInt result;
    for (int i = 0; i < S; i++) {
        int64_t temp = static_cast<int64_t>(number[i]) - static_cast<int64_t>(other.number[i]) - borrow;
        if (temp >= 0) {
            result.number[i] = static_cast<uint32_t>(temp);
            borrow = 0;
        }
        else {
            result.number[i] = static_cast<uint32_t>(0xFFFFFFFF + temp + 1);
            borrow = 1;
        }
    }
    for (int i = 0; i < S; i++)
    {
        if (result.number[i] < 0) {
            result.number[i] = 0;
        }
    }

    return result;
}

// �������� �������� ��� LongInt �� 32-������� ������ ��� �����
LongInt LongInt::operator * (const uint32_t b) const {
    uint32_t carry = 0;
    LongInt result;
    for (int i = 0; i < S; i++) {

        uint64_t temp = static_cast<uint64_t>(number[i]) * static_cast<uint64_t>(b) + static_cast<uint64_t>(carry);

        result.number[i] = static_cast<uint32_t>(temp & 0xFFFFFFFF);

        carry = static_cast<uint32_t>(temp >> 32);
    }

    result.number[S - 1] = carry;
    return result;
}

// �������� �������� ��� ���� LongInt
LongInt LongInt::operator * (const LongInt& other) const {
    LongInt result;
    for (int i = 0; i < S; i++) {

        LongInt temp = *this * other.number[i];

        temp = temp << i;

        result = result + temp;
    }
    return result;
}

// �������� ������ ��� LongInt
LongInt LongInt::operator/(const LongInt& other) const {
    if (other == LongInt("0")) {
        throw std::invalid_argument("Division by zero is not allowed.");
    }
    if (*this < other) {
        return LongInt("0");
    }

    LongInt divided = *this;
    LongInt divisor = other;
    LongInt quotient;
    LongInt remainder;
    int k = divisor.Bit_Length();
    remainder = divided;
    quotient = LongInt("0");

    while (remainder >= divisor) {
        int t = remainder.Bit_Length();
        LongInt C = divisor.LongShiftBits_ToHigh(t - k);

        if (remainder < C) {
            t = t - 1;
            C = divisor.LongShiftBits_ToHigh(t - k);
        }

        remainder = remainder - C;
        quotient = quotient + LongInt("1").LongShiftBits_ToHigh(t - k);
    }

    return quotient;
}

// �������� �� ������� ��� LongInt
LongInt LongInt::operator%(const LongInt& other) const {

    if (other == LongInt("0")) {
        throw std::invalid_argument("Division by zero is not allowed.");
    }

    LongInt A = *this;
    LongInt B = other;
    LongInt R;
    int k = B.Bit_Length();
    R = A;

    while (R >= B) {
        int t = R.Bit_Length();
        LongInt C = B.LongShiftBits_ToHigh(t - k);

        if (R < C) {
            t = t - 1;
            C = B.LongShiftBits_ToHigh(t - k);
        }

        R = R - C;
    }

    return R;
}


// ����� ��������� �� �������� LongInt
LongInt LongInt::square() const {
    return *this * *this;
}

// ����� ��������� LongInt �� ������� ������ LongInt
LongInt LongInt::pow(const LongInt& other) const {
    LongInt base = *this;
    std::string exponent = convert_IntoBinary(other);
    LongInt result("1");

    for (int i = exponent.size() - 1; i >= 0; i--) {
        if (exponent[i] == '1')
            result = result * base;

        if (i > 0)
            base = base.square();
    }
    return result;
}


// �������� ��������� �� ������ ��� LongInt
bool LongInt::operator == (const LongInt& other) const {
    for (int i = S - 1; i >= 0; i--) {
        if (number[i] != other.number[i]) {
            return false;
        }
    }
    return true;
}

// �������� ��������� ���������� ��� LongInt
bool LongInt::operator != (const LongInt& other) const {
    for (int i = S - 1; i >= 0; i--) {
        if (number[i] != other.number[i]) {
            return true;
        }
    }
    return false;
}

// �������� ��������� ����� �� ��� LongInt
bool LongInt::operator < (const LongInt& other) const {
    for (int i = S - 1; i >= 0; i--) {
        if (number[i] != other.number[i]) {
            return number[i] < other.number[i];
        }
    }
    return false;
}

// �������� ��������� ����� �� ��� LongInts
bool LongInt::operator > (const LongInt& other) const {
    return other < *this;
}

// �������� ��������� ����� ��� ������� ��� LongInts
bool LongInt::operator <= (const LongInt& other) const {
    for (int i = S - 1; i >= 0; i--) {
        if (number[i] != other.number[i]) {
            return number[i] < other.number[i];
        }
    }
    return true;
}

// �������� ��������� ����� ��� ������� ��� LongInts
bool LongInt::operator >= (const LongInt& other) const {
    return other <= *this;
}


// �������� ����� ���� ��� LongInts
LongInt LongInt::operator << (int b) const {
    LongInt result(*this);

    for (int i = S - 1; i >= 0; i--) {
        if (i - b >= 0) {

            result.number[i] = result.number[i - b];
        }
        else {
            result.number[i] = 0;
        }
    }
    return result;
}

// �������� ����� ������ ��� LongInts
LongInt LongInt::operator >> (int b) const {
    LongInt result(*this);

    for (int i = 0; i < S; i++) {
        if (i + b < S) {

            result.number[i] = result.number[i + b];
        }
        else {
            result.number[i] = 0;
        }
    }
    return result;
}



// ����� ���������� ����� ������� ���� LongInt
int LongInt::Bit_Length() const {
    int length = S * 32;
    for (int i = S - 1; i >= 0; i--) {
        if (number[i] != 0) {
            int bitPos = 31;
            while (bitPos >= 0 && (number[i] & (1u << bitPos)) == 0) {
                bitPos--;
            }
            length = i * 32 + bitPos + 1;
            break;
        }
    }
    return length;
}

// ����� ��� ��������� ������� ����� ��� � ������ �������
LongInt LongInt::LongShiftBits_ToHigh(int bits) const {
    LongInt result("0");

    if (bits <= 0) {
        return *this;
    }
    if (bits >= S * 32) {
        return result;
    }

    int numBlocks = bits / 32;
    int remainingBits = bits % 32;

    uint32_t carry = 0;

    if (remainingBits != 0) {

        for (int i = 0; i < S; i++) {
            result.number[i] = (this->number[i] << remainingBits) + carry;
            carry = (this->number[i] >> (32 - remainingBits));
        }


        for (int i = S - 1; i >= numBlocks; i--) {
            result.number[i] = result.number[i - numBlocks];
        }


        for (int i = 0; i < numBlocks; i++) {
            result.number[i] = 0;
        }
    }
    else {

        for (int i = S - 1; i >= numBlocks; i--) {
            result.number[i] = this->number[i - numBlocks];
        }


        for (int i = 0; i < numBlocks; i++) {
            result.number[i] = 0;
        }
    }

    return result;
}

//LAB2_tasks!!!!!!!!!!

LongInt LongInt::shiftRight() const {
    int carry = 0;
    LongInt result("0");

    for (int i = S - 1; i >= 0; --i) {
        result.number[i] = (this->number[i] >> 1) + (carry << 31);
        carry = this->number[i] & 1;
    }

    return result;
}

bool LongInt::isEven() const {
    return (number[0] % 2 == 0);
}

//�������� ����� ��� ���
LongInt LongInt::gcd_bin(const LongInt& a, const LongInt& b) {
    if (b == LongInt("0")) {
        return a;
    }

    LongInt tA = a;
    LongInt tB = b;
    LongInt d("1");

    while (tA.isEven()) {
        if (tB.isEven()) {
            tA = tA.shiftRight();
            tB = tB.shiftRight();
            d = d * LongInt("2");
        }
        else {
            break;
        }
    }

    while (tA.isEven()) {
        tA = tA.shiftRight();
    }


    while (tB != LongInt("0")) {
        while (tB.isEven()) {
            tB = tB.shiftRight();
        }

        LongInt temp;
        if (tA < tB) {
            temp = tA;
        }
        else {
            temp = tB;
        }

        if (tA < tB) {
            tB = tB - tA;
        }
        else {
            tB = tA - tB;
        }
        tA = temp;
    }

    d = d * tA;
    return d;
}


LongInt LongInt::gcd_euclidian(const LongInt& other) const {
    LongInt a = *this;
    LongInt b = other;

    while (b != LongInt("0")) {
        LongInt t = b;
        b = a % b;
        a = t;
    }

    return a;
}

//����� ��� ���
LongInt LongInt::lcm(const LongInt& a, const LongInt& b) {
    LongInt absProduct = a * b;
    if (absProduct < LongInt("0")) {
        absProduct = absProduct;
    }

    LongInt gcdResult = gcd_bin(a, b);
    LongInt lcmResult = absProduct / gcdResult;

    return lcmResult;
}


LongInt LongInt::funcMu(const LongInt& n) {
    int l = n.Digit_Length();
    LongInt B = LongInt("1") << (2 * l);
    return B / n;
}

int LongInt::Digit_Length() const {
    for (int l = S; l > 0; --l) {
        if (number[l - 1] != 0) {
            return l;
        }
    }
    return 0;
}

LongInt LongInt::BarrettReduction(const LongInt& x, const LongInt& n, const LongInt& modulus) {
    int k = n.Digit_Length();
    LongInt tX = x;
    LongInt tN = n;
    LongInt tM = modulus;

    if (tX < tN) {
        return tX;
    }

    LongInt Q = tX >> (k - 1);
    Q = Q * tM;
    Q = Q >> (k + 1);

    LongInt R = tX - (Q * tN);
    while (R >= tN) {
        R = R - tN;
    }
    return R;
}


LongInt LongInt::Add_Mod(const LongInt& a, const LongInt& b, const LongInt& modulus) {

    LongInt result("0");
    result = a + b;

    if (result >= modulus) {
        result = BarrettReduction(result, modulus, funcMu(modulus));
    }

    return result;
}

LongInt LongInt::Sub_Mod(const LongInt& a, const LongInt& b, const LongInt& modulus) {
    LongInt result("0");

    if (a >= b) {
        result = BarrettReduction(a - b, modulus, funcMu(modulus));
    }
    else {
        result = BarrettReduction(b - a, modulus, funcMu(modulus));
        result = modulus - result;
    }


    return result;
}

LongInt LongInt::Mult_Mod(const LongInt& a, const LongInt& b, const LongInt& modulus) {
    LongInt result("0");

    result = a * b;

    if (result >= modulus) {
        result = BarrettReduction(result, modulus, funcMu(modulus));
    }

    return result;
}

LongInt LongInt::Square_Mod(const LongInt& a, const LongInt& modulus) {
    return LongInt::Mult_Mod(a, a, modulus);
}

LongInt LongInt::ModPower_Barrett(const LongInt& a, const LongInt& b, const LongInt& modulus) {
    LongInt result("1");
    LongInt base = a % modulus;
    LongInt Mu = funcMu(modulus);

    std::string binaryExp = b.convert_IntoBinary(b);

    for (int i = binaryExp.length() - 1; i >= 0; --i) {
        if (binaryExp[i] == '1') {
            result = BarrettReduction(result * base, modulus, Mu);
        }
        base = BarrettReduction(base.square(), modulus, Mu);
    }
    return result;
}