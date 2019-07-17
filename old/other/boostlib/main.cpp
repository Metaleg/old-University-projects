//
// Created by metalleg on 28.04.18.
//
/*#include <iostream>
#include <cstring>
#include <type_traits>
template <typename T>
constexpr T quad(T arg){
    return arg * arg;
}

int main(){
    using male = int;
    using integral_c = std::integral_constant<int, 10>;

    integral_c k;
    std::cout << k << std::endl;


    constexpr male f = quad(5);
    constexpr float fu = quad(9.7F);
    std::cout << f << std::endl << fu;


    auto *p = const_cast<char *>("qweasdfgh");
    size_t s = strlen(p);
    std::cout << std::endl << s;

    auto z{1};
    std::cout << std::endl << z;
}
*/