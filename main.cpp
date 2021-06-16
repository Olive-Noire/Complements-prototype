#include <iostream>
#include <string>
#include <bitset>

template<typename Number, std::enable_if_t<std::is_arithmetic_v<Number>, bool> = true>
constexpr std::bitset<8*sizeof(Number)> CA1(Number x) noexcept {

    std::bitset<8*sizeof(Number)> bits(x);
    for (std::size_t i{0}; i < 8*sizeof(Number); i++) bits[i]=!bits[i]; // Inverse tout les bits
    return bits;

}

template<typename Number, std::enable_if_t<std::is_arithmetic_v<Number>, bool> = true>
constexpr std::bitset<8*sizeof(Number)> CA(Number x, std::size_t c) noexcept {

    return std::bitset<8*sizeof(Number)>(CA1(x).to_ullong()+(c-1)); // CAn(x) = CA1(x)+(n-1)

}

/*
template<typename Number, std::enable_if_t<std::is_arithmetic_v<Number>, bool> = true>
constexpr std::bitset<8*sizeof(Number)> SignedCA2(Number x) noexcept {

    if (x & 1 << sizeof(Number)-1) return CA(x & 0b01111111 >> 1, 2); else return CA(x & 0b01111111 >> 1, 2);

}
*/

// Juste pour le test x = CAn(CAn(x))
template<std::size_t Size, std::enable_if_t<Size >= 8*sizeof(unsigned long long), bool> = true>
constexpr bool operator==(unsigned long long n, const std::bitset<Size> &b) noexcept { return b.to_ullong() == n; }

int main() {

    // Tests unitaires
    std::cout << CA1<unsigned char>(0b0010) << ' ' << CA<unsigned char>(0b0010, 2) << ' ' << /*std::bitset<32>(SignedCA2(2)) <<*/
    std::boolalpha << bool(1ULL == CA(CA(1ULL, 1/*n*/).to_ullong(), 1/*n*/)) << std::endl; // Vérifie l'expression : x = CAn(CAn(x))

    std::cin.get();

    return 0;

}
