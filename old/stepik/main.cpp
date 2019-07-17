#include <iostream>

void string_rand(char *string, unsigned& size){
    srand((unsigned int)time(nullptr));
    for (auto i = 0; i < size; ++i)
        string[i] = static_cast<char>(53 + rand() % 37);
}

void print_string(const char *string){
    for (; *string; ++string)
        std::cout << *string;
    std::cout << std::endl;
}

char *resize(const char *str, unsigned size, unsigned new_size) {
    char *res = new char[new_size];
    for (auto i = 0; i < ((size > new_size) ? new_size : size); ++i)
        res[i] = str[i];
    delete[] str;
    return res;
}

char *getline() {
    char *string;
    
}





int main() {
    unsigned size = 10;
    char *string = new char[size];
    string_rand(string, size);
    print_string(string);
    unsigned new_size = 10;
    string = resize(string, size, new_size);
    print_string(string);
    
    delete[] string;
    return 0;
}