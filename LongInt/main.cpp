#include <iostream>
#include "LongInt.h"
#include <chrono>
#include <locale>

int main() {

    setlocale(LC_CTYPE, "ukr");


    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    //LongInt a = LongInt::GenerateRandomLongInt(10);
    //LongInt b = LongInt::GenerateRandomLongInt(5);


    LongInt a("658ec5e5d8f126d692936c196bc1be68fdbc7483d7f1035c8e636c36ed5d4d0f0f69a0fa8158f4d0967e3ebd23aa4081f14540fb4f4724140e38ab2a40d33e807028b2f40b1e5362c392348d7cd81dde9ec6a79e1f4abb8b706ea0d63d30f0663a2ca1ff673d8889bc315853fca663a2c05f46c87657f0fea4ec2aafe8bbf3ac");
    LongInt b("f5aa1bd307eedf96db133a218aa605a0edb6de4fa9d43d100cd75990b3c9b72347ff83796c2f886b4a58f312b8bdbdbcaf500790eee9add7165837032d2bd268e9a73cb50dca7a065abb515a18f8783c9f1bdaa5400a2b2f06cc42a2b38f41599d5bab219aaff407f6c283d479de944f8d039233709e21e30aa380b98026ac33");
    LongInt n("7");

    std::cout << "A = " << LongInt::convert_NumberToHexString(a.getNumber()) << std::endl;
    std::cout << "B = " << LongInt::convert_NumberToHexString(b.getNumber()) << std::endl;
    std::cout << "n = " << LongInt::convert_NumberToHexString(n.getNumber()) << std::endl;


    // Виконання арифметичних операцій
    LongInt q = a + b;
    LongInt w = a - b;
    LongInt e = a * 0x10;
    LongInt r = a * b;
    LongInt t = a.square();
    LongInt y = a / b;
    LongInt u = a % b;
    LongInt i = a.pow(n);



    //Вивід результатів
    std::cout << "A + B = " << LongInt::convert_NumberToHexString(q.getNumber()) << std::endl;
    std::cout << "A - B = " << LongInt::convert_NumberToHexString(w.getNumber()) << std::endl;
    std::cout << "A * 0x10 = " << LongInt::convert_NumberToHexString(e.getNumber()) << std::endl;
    std::cout << "A * B = " << LongInt::convert_NumberToHexString(r.getNumber()) << std::endl;
    std::cout << "A ^ 2 = " << LongInt::convert_NumberToHexString(t.getNumber()) << std::endl;
    std::cout << "A / B = " << LongInt::convert_NumberToHexString(y.getNumber()) << std::endl;
    std::cout << "A % B = " << LongInt::convert_NumberToHexString(u.getNumber()) << std::endl;
    std::cout << "A ^ n = " << LongInt::convert_NumberToHexString(i.getNumber()) << std::endl;
    std::cout << std::endl;


    std::cout << "Обрахування середнього часу виконання для операцій:" << std::endl;

    const int iter = 100;

    // Середній час додавання
    long long totalAddTime = 0;
    for (int i = 0; i < iter; ++i) {
        auto startTime = std::chrono::high_resolution_clock::now();
        LongInt c = a + b;
        auto endTime = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
        totalAddTime += duration.count();
    }
    double averageAddTime = static_cast<double>(totalAddTime) / iter;
    std::cout << "Серед. час для додавання: " << averageAddTime << " nanoseconds\n";

    // Середній час віднімання
    long long totalSubTime = 0;
    for (int i = 0; i < iter; ++i) {
        auto startTime = std::chrono::high_resolution_clock::now();
        LongInt d = a - b;
        auto endTime = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
        totalSubTime += duration.count();
    }
    double averageSubTime = static_cast<double>(totalSubTime) / iter;
    std::cout << "Серед. час для віднімання: " << averageSubTime << " nanoseconds\n";

    // Середній час множення (на цифру)
    long long totalMultTime = 0;
    for (int i = 0; i < iter; ++i) {
        auto startTime = std::chrono::high_resolution_clock::now();
        LongInt e = a * 0x10;
        auto endTime = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
        totalMultTime += duration.count();
    }
    double averageMultTime = static_cast<double>(totalMultTime) / iter;
    std::cout << "Серед. час мнодення(на цифру): " << averageMultTime << " nanoseconds\n";

    // Середній час для множення LongInt
    long long totalLongMultTime = 0;
    for (int i = 0; i < iter; ++i) {
        auto startTime = std::chrono::high_resolution_clock::now();
        LongInt f = a * b;
        auto endTime = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
        totalLongMultTime += duration.count();
    }
    double averageLongMultTime = static_cast<double>(totalLongMultTime) / iter;
    std::cout << "Серед. час для множення LongInt: " << averageLongMultTime << " nanoseconds\n";

    // Середній час для квадрата 
    long long totalSquareTime = 0;
    for (int i = 0; i < iter; ++i) {
        auto startTime = std::chrono::high_resolution_clock::now();
        LongInt g = a.square();
        auto endTime = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
        totalSquareTime += duration.count();
    }
    double averageSquareTime = static_cast<double>(totalSquareTime) / iter;
    std::cout << "Серед. час для квадрату: " << averageSquareTime << " nanoseconds\n";

    // Середній час ділення
    long long totalDivTime = 0;
    for (int i = 0; i < iter; ++i) {
        auto startTime = std::chrono::high_resolution_clock::now();
        LongInt h = a / b;
        auto endTime = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
        totalDivTime += duration.count();
    }
    double averageDivTime = static_cast<double>(totalDivTime) / iter;
    std::cout << "Серед. час для ділення: " << averageDivTime << " nanoseconds\n";

    // Середній час для mod
    long long totalModTime = 0;
    for (int i = 0; i < iter; ++i) {
        auto startTime = std::chrono::high_resolution_clock::now();
        LongInt j = a % b;
        auto endTime = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
        totalModTime += duration.count();
    }
    double averageModTime = static_cast<double>(totalModTime) / iter;
    std::cout << "Серед. час для mod: " << averageModTime << " nanoseconds\n";

    // Середній час виконання pow
    long long totalPowTime = 0;
    for (int i = 0; i < iter; ++i) {
        auto startTime = std::chrono::high_resolution_clock::now();
        LongInt k = a.pow(n);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
        totalPowTime += duration.count();
    }
    double averagePowTime = static_cast<double>(totalPowTime) / iter;
    std::cout << "Серед. час для pow: " << averagePowTime << " nanoseconds\n";



    // Проведення тестів

    LongInt hexLongInt("FFFFFF");
    assert(LongInt::convert_NumberToHexString(hexLongInt.getNumber()) == "FFFFFF");

    LongInt A("DA107D303F078BC54C6ADBB8EC0BE59F65D709F76281CA5DADDD1C4C64A15AAF867556E7C0A34415");
    LongInt B("9AC19414A633B2ABD6646EB0BC09C32C02DB7452");
    LongInt C("14CDEAC83901D4C92B6E720D27D7EE96C83A233C3E7CAB76D63677C2F578618596D6DECE8D5DA710");

    LongInt addResult = A + B;
    assert(LongInt::convert_NumberToHexString(addResult.getNumber()) == "DA107D303F078BC54C6ADBB8EC0BE59F65D709F7FD435E725410CEF83B05C960427F1A13C37EB867");

    LongInt subResult = A - B;
    assert(LongInt::convert_NumberToHexString(subResult.getNumber()) == "DA107D303F078BC54C6ADBB8EC0BE59F65D709F6C7C0364907A969A08E3CEBFECA6B93BBBDC7CFC3");

    LongInt multResult = A * B;
    assert(LongInt::convert_NumberToHexString(multResult.getNumber()) == "83D2CFE0868675A26945D3E5A1B4668154F972A1B2BF2866B50771A1FBD8557D02CFD93E3E5C6228AC9C1734E4A95929C6AA7DF3AE629E55171C52BA");

    LongInt divResult = A / B;
    assert(LongInt::convert_NumberToHexString(divResult.getNumber()) == "168B9B7B7514F319DF4E7F288D79F793DB4FF1CEC");

    LongInt modResult = A % B;
    assert(LongInt::convert_NumberToHexString(modResult.getNumber()) == "6611C23F7E8877568CD51CD83C0FFA1897ED107D");


    LongInt res1 = (A + B) * C;
    LongInt res2 = C * (A + B);
    LongInt res3 = A * C + B * C;
    assert(res1 == res2 && res2 == res3);


    int m = 105;

    LongInt res4 = A * m;
    LongInt res5("0");
    for (int i = 0; i < m; i++) {
        res5 = res5 + A;
    }
    assert(res4 == res5);


    std::cout << std::endl;
    std::cout << "Тести успiшно завершенi" << std::endl;

    return 0;
}


