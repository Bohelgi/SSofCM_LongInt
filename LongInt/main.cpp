#include <iostream>
#include "LongInt.h"
#include <chrono>
#include <locale>

int main() {

    setlocale(LC_CTYPE, "ukr");


    std::srand(static_cast<unsigned int>(std::time(nullptr)));


    LongInt a("658ec5e5d8f126d692936c196bc1be68fdbc7483d7f1035c8e636c36ed5d4d0f0f69a0fa8158f4d0967e3ebd23aa4081f14540fb4f4724140e38ab2a40d33e807028b2f40b1e5362c392348d7cd81dde9ec6a79e1f4abb8b706ea0d63d30f0663a2ca1ff673d8889bc315853fca663a2c05f46c87657f0fea4ec2aafe8bbf3ac");
    LongInt b("f5aa1bd307eedf96db133a218aa605a0edb6de4fa9d43d100cd75990b3c9b72347ff83796c2f886b4a58f312b8bdbdbcaf500790eee9add7165837032d2bd268e9a73cb50dca7a065abb515a18f8783c9f1bdaa5400a2b2f06cc42a2b38f41599d5bab219aaff407f6c283d479de944f8d039233709e21e30aa380b98026ac33");
    LongInt m("5bffd2ad88c901a224caba35ba09c26ae6be9c06dae976a0fc91b7e6f5076559813cb94d2b33e86c9bf1afabc4598e769fd3e7c27bc45bbeab5e78ce48fabe89ef514ff65c64da6e6858a91600de5b4091b219b88ff502fd166ea1ef805e37bc0695d17348823898c0a7bfe217d7980ca93b724b2aecec6c4f0165e9b30002e2");

    std::cout << "A = " << LongInt::convert_NumberToHexString(a.getNumber()) << std::endl;
    std::cout << "B = " << LongInt::convert_NumberToHexString(b.getNumber()) << std::endl;
    std::cout << "m = " << LongInt::convert_NumberToHexString(m.getNumber()) << std::endl;


    LongInt result_gcd_bin = LongInt::gcd_bin(a, b);
    LongInt result_gcd_euclidian = a.LongInt::gcd_euclidian(b);
    LongInt result_lcm = LongInt::lcm(a, b);
    LongInt Add_Mod = LongInt::Add_Mod(a, b, m);
    LongInt Sub_Mod = LongInt::Sub_Mod(a, b, m);
    LongInt Mult_Mod = LongInt::Mult_Mod(a, b, m);
    LongInt Square_Mod = LongInt::Square_Mod(a, m);
    LongInt ModPower_Barrett = LongInt::ModPower_Barrett(a, b, m);



    std::cout << "gcd_bin(a, b) = " << LongInt::convert_NumberToHexString(result_gcd_bin.getNumber()) << std::endl;
    std::cout << "gcd_euclidian(a, b) = " << LongInt::convert_NumberToHexString(result_gcd_euclidian.getNumber()) << std::endl;
    std::cout << "lcm(a, b) = " << LongInt::convert_NumberToHexString(result_lcm.getNumber()) << std::endl;
    std::cout << "a + b (mod m) = " << LongInt::convert_NumberToHexString(Add_Mod.getNumber()) << std::endl;
    std::cout << "a - b (mod m) = " << LongInt::convert_NumberToHexString(Sub_Mod.getNumber()) << std::endl;
    std::cout << "a * b (mod m) = " << LongInt::convert_NumberToHexString(Mult_Mod.getNumber()) << std::endl;
    std::cout << "a ^ 2 (mod m) = " << LongInt::convert_NumberToHexString(Square_Mod.getNumber()) << std::endl;
    std::cout << "a ^ b (mod m) = " << LongInt::convert_NumberToHexString(ModPower_Barrett.getNumber()) << std::endl;


    std::cout << "Обрахування середнього часу виконання для операцiй:" << std::endl;

    const int iter = 100;


    long long totalgcd_bintime = 0;
    for (int i = 0; i < iter; ++i) {
        auto startTime = std::chrono::high_resolution_clock::now();
        LongInt result_gcd_bin = LongInt::gcd_bin(a, b);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
        totalgcd_bintime += duration.count();
    }
    double averagegcdtime = static_cast<double>(totalgcd_bintime) / iter;
    std::cout << "Серед. час для НСД_bin: " << averagegcdtime << " nanoseconds\n";



    long long totalgcd_euclidiantime = 0;
    for (int i = 0; i < iter; ++i) {
        auto startTime = std::chrono::high_resolution_clock::now();
        LongInt result_gcd_euclidian = a.LongInt::gcd_euclidian(b);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
        totalgcd_euclidiantime += duration.count();
    }
    double averagegcd_euclidiantime = static_cast<double>(totalgcd_euclidiantime) / iter;
    std::cout << "Серед. час для НСД_euclidian: " << averagegcdtime << " nanoseconds\n";



    long long totallcmtime = 0;
    for (int i = 0; i < iter; ++i) {
        auto startTime = std::chrono::high_resolution_clock::now();
        LongInt result_lcm = LongInt::lcm(a, b);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
        totallcmtime += duration.count();
    }
    double averagelcmtime = static_cast<double>(totallcmtime) / iter;
    std::cout << "Серед. час для НСК: " << averagelcmtime << " nanoseconds\n";



    long long totaladdmodtime = 0;
    for (int i = 0; i < iter; ++i) {
        auto startTime = std::chrono::high_resolution_clock::now();
        LongInt Add_Mod = LongInt::Add_Mod(a, b, m);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
        totaladdmodtime += duration.count();
    }
    double averageaddmodtime = static_cast<double>(totaladdmodtime) / iter;
    std::cout << "Серед. час для a + b (mod m): " << averageaddmodtime << " nanoseconds\n";



    long long totalsubmodtime = 0;
    for (int i = 0; i < iter; ++i) {
        auto startTime = std::chrono::high_resolution_clock::now();
        LongInt Sub_Mod = LongInt::Sub_Mod(a, b, m);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
        totalsubmodtime += duration.count();
    }
    double averagesubmodtime = static_cast<double>(totalsubmodtime) / iter;
    std::cout << "Серед. час для a - b (mod m): " << averagesubmodtime << " nanoseconds\n";



    long long totalmultmodtime = 0;
    for (int i = 0; i < iter; ++i) {
        auto startTime = std::chrono::high_resolution_clock::now();
        LongInt Mult_Mod = LongInt::Mult_Mod(a, b, m);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
        totalmultmodtime += duration.count();
    }
    double averagemultmodtime = static_cast<double>(totalmultmodtime) / iter;
    std::cout << "Серед. час для a * b (mod m): " << averagemultmodtime << " nanoseconds\n";



    long long totalsquaremodtime = 0;
    for (int i = 0; i < iter; ++i) {
        auto startTime = std::chrono::high_resolution_clock::now();
        LongInt Square_Mod = LongInt::Square_Mod(a, m);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
        totalsquaremodtime += duration.count();
    }
    double averagesquaremodtime = static_cast<double>(totalsquaremodtime) / iter;
    std::cout << "Серед. час для a ^ 2 (mod m): " << averagesquaremodtime << " nanoseconds\n";



    long long totalpowmodtime = 0;
    for (int i = 0; i < iter; ++i) {
        auto startTime = std::chrono::high_resolution_clock::now();
        LongInt ModPower_Barrett = LongInt::ModPower_Barrett(a, b, m);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
        totalpowmodtime += duration.count();
    }
    double averagepowmodtime = static_cast<double>(totalpowmodtime) / 10;
    std::cout << "Серед. час для a ^ b (mod m): " << averagepowmodtime << " microseconds\n";



    //Тестування

    LongInt A("6745A11ED5C715477C4AA37A865D25E494295C4AA5453581A1A3B2D0BDEBED8910746C403A2A624E");
    LongInt B("715D237C256351605D77ED70736FC7A6ED4DE2D5");
    LongInt C("B897ED959502EF58818C869EA3923C2810AEE22492BA1DC935085DBBE9667F8C036DEEC0CD800C69");
    LongInt M("F8F6E9F15BE202327967EC80D54C2D207C582D6055639B7B1F89DC126E6A1D91FED1D500D2E1BC76");

    /*LongInt result_gcd_bin = LongInt::gcd_bin(A, B);;
    assert(LongInt::convert_NumberToHexString(result_gcd_bin.getNumber()) == "3");

    LongInt result_lcm = LongInt::lcm(A, B);
    assert(LongInt::convert_NumberToHexString(result_lcm.getNumber()) == "F3E6F9394CCF9A3E8437DF2D72B793B2B525698840369143CDF2AC44114F76AF9ED8B48CAADE7DF053C14F26ECF22DE1AF652C69B1B4B0A87D637A2");

    LongInt Add_Mod = LongInt::Add_Mod(A, B, M);
    assert(LongInt::convert_NumberToHexString(Add_Mod.getNumber()) == "6745A11ED5C715477C4AA37A865D25E494295C4B16A258FDC70704311B63DAF983E433E727784523");

    LongInt Sub_Mod = LongInt::Sub_Mod(A, B, M);
    assert(LongInt::convert_NumberToHexString(Sub_Mod.getNumber()) == "6745A11ED5C715477C4AA37A865D25E494295C4A33E812057C406170607400189D04A4994CDC7F79");

    LongInt Mult_Mod = LongInt::Mult_Mod(A, B, M);
    assert(LongInt::convert_NumberToHexString(Mult_Mod.getNumber()) == "943DA66CF631772B28B347EBA82A867965304352F82580121015CD21F647EC8E44BAF61309364966");

    LongInt Square_Mod = LongInt::Square_Mod(A, M);
    assert(LongInt::convert_NumberToHexString(Square_Mod.getNumber()) == "8707C2B27B2E55F061158C5437B7A74135D0039F9EDDB435B875D363B061EA030369D309A5F47E0");

    LongInt ModPower_Barrett = LongInt::ModPower_Barrett(A, B, M);
    assert(LongInt::convert_NumberToHexString(ModPower_Barrett.getNumber()) == "BFE618791866A0EC1ECCB89FD2F15518118DCE3DA3D5A83BDDB61C3CC5ED26CE348E3D79A11F5CEA");*/



    //#1

    //(a + b) * c
    LongInt res1 = LongInt::BarrettReduction((A + B) * C, M, LongInt::funcMu(M));

    ////a * c + b * c 
    LongInt res2 = LongInt::BarrettReduction(A * C + B * C, M, LongInt::funcMu(M));

    ////c * (a + b) 
    LongInt res3 = LongInt::BarrettReduction(C * (A + B), M, LongInt::funcMu(M));

    assert(res1 == res2 && res2 == res3);


    //#2
    /*int t = 100;
    LongInt j = a * t;

    LongInt res5 = LongInt::BarrettReduction(j, M, LongInt::funcMu(M));

    LongInt k;
    for (int i = 0; i < t; ++i) {
        k = k + a;
    }
    LongInt res6 = LongInt::BarrettReduction(k, M, LongInt::funcMu(M));
    assert(res5 == res6 );*/

    std::cout << std::endl;
    std::cout << "Тести успiшно завершенi" << std::endl;

    return 0;
}