#include <iostream>
#include <iomanip>
#include <vector>
#include <map>


int main() {

    std::vector<int> vect (10, 5);
    for (auto iter : vect)
        std::cout << iter << std::endl;

    return 0;
}