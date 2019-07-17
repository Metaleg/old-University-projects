#include "pcxlib.cpp"
#include <iostream>
#include <cmath>

int main (){
    setlocale(LC_ALL, "rus");
    int count_images = 0;
    std::cout << "Введите количество обрабатываемых изображений:" << std::endl;
    std::cin >> count_images;
    while(count_images > 0){
        char *name = new char, *rez_name = new char;
        unsigned char *Im, *ImChar;
        double  *ImDbl, *ImTrf, xc, yc, summ1 = 0, summ2 = 0, summ3=0, mu=0, B=0, C=0, D=0, teta=0, xpls=0, ypls=0,
                M = 0, x = 0, y = 0;
        int XSize, YSize, result, xi = 0, yi = 0, K = 10;

        std::cout << "Введите имя файла (исходный): ";
        std::cin >> name;
        std::cout << "Введите имя файла (конечный): ";
        std::cin >> rez_name;

        if ((Im = ReadPCX(name, &XSize, &YSize)) == nullptr){
            std::cerr << "Ошибка открытия файла (исходный || конечный)" << std::endl;
            return -1;
        }

        ImDbl = new double[XSize * YSize];
        ImTrf = new double[XSize * YSize];
        ImChar=(unsigned char *)malloc(sizeof(double)*(XSize)*(YSize));

        for (size_t i = 0; i < YSize; ++i){
            for (size_t j = 0; j < XSize; ++j){
                ImDbl[i * XSize + j] = Im[i * XSize + j];
                ImTrf[i * XSize + j] = 0;
            }
        }
        //Вычисление абсциссы и ординаты центра тяжести изображения:
        for (size_t i = 0; i < XSize; ++i)
            for (size_t j = 0; j < YSize; ++j){
                summ1 += j * ImDbl[i * XSize + j];
                summ2 += ImDbl[i * XSize + j];
                summ3 += i * ImDbl[i * XSize + j];
            }

        xc = summ1 / summ2;
        yc = summ3 / summ2;
        std::cout << "Вычисление центра тяжести изображения:" << std::endl;
        std::cout << "Абцисса: " << ceil(xc) << ' ' << "Ордината: " << ceil(yc) << std::endl;

        // вычисление направления и величины сжатия изображения
        // цетрированного согласно пункту 1.6
        std::cout << "Вычисление направление и величины сжатия изображения:" << std::endl;
        for (size_t i = 0; i < XSize; ++i)
            for (size_t j = 0; j < YSize; ++j){
                B += ImDbl[i * XSize + j] * (((j - xc) * (j - xc)) - ((i - yc) * (i - yc)));
                C += ImDbl[i * XSize + j] * 2 * (j - xc) * (i - yc);
                D += ImDbl[i * XSize + j] * (((j - xc) * (j - xc)) + ((i - yc) * (i - yc)));
            }

        mu = sqrt((D + sqrt((C * C) + (B * B))) / (D - sqrt((C * C) + (B * B))));
        teta = (0.5 * atan2(C, B));
        std::cout << "Величина сжатия изображения: " << mu << std::endl;
        std::cout << "Направление сжатия изображения: " << teta << std::endl;

        std::cout << "Расчёт абциссы и ординаты пикселов центрированного\nизображения после компенсации его масштабирования" << std::endl;
        summ1 = 0;
        summ2 = 0;
        for (size_t i = 0; i < YSize; ++i){
            for (size_t j = 0; j < XSize; ++j){
                xpls=(1/mu)*((j-xc)*cos(-teta)-(i-yc)*sin(-teta))*cos(teta)-((j-xc)*sin(-teta)+(i-yc)*cos(-teta))*sin(teta);
                ypls=(1/mu)*((j-xc)*cos(-teta)-(i-yc)*sin(-teta))*sin(teta)+((j-xc)*sin(-teta)+(i-yc)*cos(-teta))*cos(teta);
                summ1+=ImDbl[i*XSize+j]*sqrt((xpls*xpls)+(ypls*ypls));
                summ2+=ImDbl[i*XSize+j];
            }
        }

        M = summ1 / (K * summ2);

        for (size_t i = 0; i < YSize; ++i){
            for (size_t j = 0; j < XSize; ++j){
                xpls=(1/mu)*((j-xc)*cos(-teta)-(i-yc)*sin(-teta))*cos(teta)-((j-xc)*sin(-teta)+(i-yc)*cos(-teta))*sin(teta);
                ypls=(1/mu)*((j-xc)*cos(-teta)-(i-yc)*sin(-teta))*sin(teta)+((j-xc)*sin(-teta)+(i-yc)*cos(-teta))*cos(teta);
                x = (1 / M) * xpls;
                y = (1 / M) * ypls;
                xi = x + xc;
                yi = y + yc;

                //Центрируем в обратную сторону, чтобы изображ было в центре
                if ((xi > 0) && (yi > 0) && (xi <= XSize) && (yi <= YSize))
                    ImTrf[yi * XSize + xi] = ImDbl[i * XSize + j];
            }
        }

        for (size_t i = 0; i < YSize; ++i)
            for (size_t j = 0; j < XSize; ++j)
                ImChar[i * XSize + j] = ImTrf[i * XSize + j];

        if ((result = WritePCX(ImChar, XSize, YSize, rez_name)) == 1){
            std::cout << "Ошибка запеиси изображения в файл" << std::endl;
            delete(ImTrf);
            free(ImChar);
            delete(ImDbl);
            return -1;
        }
        delete(ImTrf);
        free(ImChar);
        delete(ImDbl);

        count_images--;
    }
    return 0;
}