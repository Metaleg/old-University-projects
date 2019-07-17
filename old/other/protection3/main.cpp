#include <iostream>

#define SIZE 38
#define ASCII_S(a) ASCII->search(a)
#define LENGHT_BLOCK 2 // in bytes

char16_t ASCII_table_U1[] = u"АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩъЫЬЭЮЯабвгдежзийклмноп"; //128-175
char16_t ASCII_table_U2[] = u"рстуфхцчшщъыьэюяЁё"; //224-241
unsigned char ASCII_table_A1[][3] = {"А","Б","В","Г","Д","Е","Ж","З","И","Й","К","Л","М","Н","О","П","Р","С",
                                     "Т","У","Ф","Х","Ц","Ч","Ш","Щ","ъ","Ы","Ь","Э","Ю","Я","а","б","в","г",
                                     "д","е","ж","з","и","й","к","л","м","н","о","п"};
unsigned char ASCII_table_A2[][3] = {"р","с","т","у","ф","х","ц","ч","ш","щ","ъ","ы","ь","э","ю","я","Ё","ё"};
unsigned char ASCII_table_A3[][3] = {" ",",",".","\0","*"};

class ASCII {
public:
    unsigned char search(char16_t symbol);
    unsigned char *search(int number);
}*ASCII;

unsigned char ASCII::search(char16_t symbol){
    for(int i = 0; i < 48; ++i)
        if(symbol == ASCII_table_U1[i])
            return (unsigned char)(128 + i);
    for(int i = 0; i < 18; ++i)
        if(symbol == ASCII_table_U2[i])
            return (unsigned char)(224 + i);
    for(int i = 0; i < 256; ++i)
        if(symbol == (char16_t)i)
            return (unsigned char)i;
    return (unsigned char)0;
}

unsigned char *ASCII::search(int number){
    if((128 <= number) && (number <= 175))
        return ASCII_table_A1[number - 128];
    if((224 <= number) && (number <= 241))
        return ASCII_table_A2[number - 224];
    if(number == 32)
        return ASCII_table_A3[0];
    if(number == 44)
        return ASCII_table_A3[1];
    if(number == 46)
        return ASCII_table_A3[2];
    if(number == 0)
        return ASCII_table_A3[3];
    return ASCII_table_A3[4];
}
std::ostream &operator<<(std::ostream &out, const char16_t *__s){
    for(int i = 0; __s[i] != 0; ++i) {
        char16_t c = __s[i];
        int a = ASCII->search(c);
        out << ASCII->search(a);
    }
    return out;
}

std::ostream &operator<<(std::ostream &out, const char16_t &__s){
    int i = ASCII->search(__s);
    out << ASCII->search(i);
    return out;
}


class block{
public:
    unsigned char byte[LENGHT_BLOCK]{};
    bool bit[LENGHT_BLOCK * 8]{};
    block() = default;
    block(unsigned char byte1, unsigned char byte2){
        byte[0]=byte1;
        byte[1]=byte2;
        conformity_bit_byte();
    }
    void conformity_bit_byte(){
        for (int i = LENGHT_BLOCK; i > 0; --i)
            for (int j = 0; j < 8; ++j){
                bit[8 * i - j - 1] = (bool)((byte[i - 1] >> j)&1);
            }
    }

    unsigned char &operator[](const int &number){
        return this->byte[number];
    };
    block &operator=(const unsigned char *byte){
        this->byte[0] = *byte;
        this->byte[1] = *(byte+1);
        conformity_bit_byte();
        return *this;
    };
};
std::ostream &operator<<(std::ostream &out, const block &__bl){
    for (bool i : __bl.bit)
        out << (i?1:0);
    return out;
}

void print_str(block *str);
unsigned char mulmod(unsigned char a, char16_t b);


int main() {
    char16_t input[SIZE + 1] = u"Евклид был древнегреческим математиком";
    char16_t key[8] = u"Виталий";
    block str[SIZE];
    for (size_t i = 0; i < SIZE / 2; ++i) {
        block LR(ASCII_S(input[i * 2]), ASCII_S(input[i * 2 + 1]));
        str[i] = LR;
    }

    std::cout << "Source string:" << std::endl;
    print_str(str);

    //Encrypting
    for(int i = 0; i < SIZE/2; ++i) {
        block LR = str[i];
        for(int j = 0, k = 0; j < 16; ++j) {
            if (j == 7 || j == 14)
                k = 0;
            char16_t c = key[k];
            ++k;
            unsigned char fun = mulmod(LR[0], c);
            fun ^= LR[1];
            LR = block(fun,LR[0]);
            if (i == 0)
                std::cout << LR << std::endl;
        }
        str[i] = LR;
    }
    std::cout << std::endl;
    std::cout << "Encrypted string:" << std::endl;
    print_str(str);

    //Decrypting
    for(int i = 0; i < SIZE/2; ++i) {
        block LR = str[i];
        for(int j = 0, k = 1; j < 16; ++j) {
            if (j == 2 || j == 9)
                k = 6;
            char16_t c = key[k];
            --k;
            unsigned char fun;
            fun = mulmod(LR[1], c);
            fun ^= LR[0];
            LR = block(LR[1],fun);
            if (i == 0)
                std::cout << LR << std::endl;
        }
        str[i] = LR;
    }
    std::cout << std::endl;
    std::cout << "Decrypted string:" << std::endl;
    print_str(str);
    return 0;
}

void print_str(block *str){
    std::cout << "№L\t- L:  \t№R\t- R: \t(bit: |<-L-->||<--R->| )"<< std::endl;
    for (int i = 0; i < SIZE/2; ++i){
        std::cout << i*2 << "\t- " << (int)str[i][0] << " \t"
                  << i*2+1 << "\t- " << (int)str[i][1] << "\t(bit: "
                  << str[i] << " )"<< std::endl;
    }
    std::cout << std::endl;
}

unsigned char mulmod(unsigned char a, char16_t b) {
    unsigned char res = 0;
    int m = (2 ^ b) + 1;
    while (a != 0) {
        if (a & 1)
            res = static_cast<unsigned char>((res + b) % m);
        a >>= 1;
        b = static_cast<unsigned char>((b << 1) % m);
    }
    return res;
}