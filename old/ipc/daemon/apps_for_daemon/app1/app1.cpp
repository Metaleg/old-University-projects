#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    std::ofstream fout;
    fout.open("app1.txt", std::ios_base::out | std::ios_base::app);
    fout << argv[1] << std::endl;
    return 0;
}