#include <iostream>
#include <cmath>

#define N 250 // Кол-во станций

typedef struct frame {
    int start_frame[8];		// НК
    int adr_send[8];		// АО
    int adr_reciv[8];		// АП
    int length[8];		// Длина данных
    int data[81];		// Данные
    int mod256;			// Проверка по mod 256
} frame;

frame station_receiver(frame reciv_frame);

int main() {
    frame send_frame;
    // Заполняем НК
    send_frame.start_frame[0] = 1;
    send_frame.start_frame[1] = 0;
    send_frame.start_frame[2] = 1;
    send_frame.start_frame[3] = 0;
    send_frame.start_frame[4] = 1;
    send_frame.start_frame[5] = 0;
    send_frame.start_frame[6] = 1;
    send_frame.start_frame[7] = 1;
    // Заполняем АО
    send_frame.adr_send[0] = 1;
    send_frame.adr_send[1] = 0;
    send_frame.adr_send[2] = 1;
    send_frame.adr_send[3] = 0;
    send_frame.adr_send[4] = 1;
    send_frame.adr_send[5] = 0;
    send_frame.adr_send[6] = 1;
    send_frame.adr_send[7] = 0;
    // Заполняем АП
    send_frame.adr_reciv[0] = 0;
    send_frame.adr_reciv[1] = 0;
    send_frame.adr_reciv[2] = 0;
    send_frame.adr_reciv[3] = 0;
    send_frame.adr_reciv[4] = 1;
    send_frame.adr_reciv[5] = 0;
    send_frame.adr_reciv[6] = 0;
    send_frame.adr_reciv[7] = 0;
    // Заполняем длину данных
    send_frame.length[0] = 0;
    send_frame.length[1] = 0;
    send_frame.length[2] = 0;
    send_frame.length[3] = 0;
    send_frame.length[4] = 0;
    send_frame.length[5] = 0;
    send_frame.length[6] = 0;
    send_frame.length[7] = 1;
    // Заполняем данные
    for (int & i : send_frame.data)
        i = 0;
    send_frame.data[0] = 1;
    send_frame.data[1] = 1;
    send_frame.data[2] = 1;
    send_frame.data[3] = 1;
    send_frame.data[4] = 0;
    send_frame.data[5] = 1;
    send_frame.data[6] = 1;
    send_frame.data[7] = 0;
    // Проверка данных mod 256
    int buf = 0;
    for (auto i = 0; i < 8; ++i)
        buf += send_frame.start_frame[i] * pow((float)2, 7 - i) + send_frame.adr_send[i] * pow((float)2, 7 - i) + send_frame.adr_reciv[i] * pow((float)2, 7 - i) + send_frame.length[i] * pow((float)2, 7 - i);
    send_frame.mod256 = 256 - (buf % 256);
    // Отправляем пакет
    station_receiver(send_frame);
    return 0;
}
frame station_receiver(frame reciv_frame) {
    int station_adress[8]; // Номер станции
    // Заполняем номер станции
    station_adress[0] = 0;
    station_adress[1] = 0;
    station_adress[2] = 0;
    station_adress[3] = 0;
    station_adress[4] = 1;
    station_adress[5] = 0;
    station_adress[6] = 0;
    station_adress[7] = 0;
    // Вывод номер станции
    std::cout << "Current station:\n";
    for (int i : station_adress)
        std::cout << i;
    //Вывод заголовка принятого кадра
    std::cout << "\n\n\nStart seq:";
    for (int i : reciv_frame.start_frame)
        std::cout << i;
    std::cout << "\nSource addr:\n";
    for (int i : reciv_frame.adr_send)
        std::cout << i;
    std::cout << "\nReceiver addr:\n";
    for (int i : reciv_frame.adr_reciv)
        std::cout << i;
    std::cout << "\nData length:\n";
    for (int i : reciv_frame.length)
        std::cout << i;
    std::cout << "\nMod 256: " << reciv_frame.mod256 << std::endl << std::endl;
    printf("%d\n\n", reciv_frame.mod256);
    //Проверяем mod 256
    int buf = 0;
    for (auto i = 0; i < 8; i++)
        buf += reciv_frame.start_frame[i] * pow((float)2, 7 - i) + reciv_frame.adr_send[i] * pow((float)2, 7 - i) + reciv_frame.adr_reciv[i] * pow((float)2, 7 - i) + reciv_frame.length[i] * pow((float)2, 7 - i);
    
    buf = (buf + reciv_frame.mod256) % 256;
    // Вывод проверки mod 256
    std::cout << "Mod 256 result on this station: " << buf << std::endl << std::endl;
    if (buf == 0) {
        // Проверка - наш ли кадр?
        auto counter = 0;
        for (auto i = 0; i < 8; ++i)
            if (reciv_frame.adr_reciv[i] == station_adress[i])
                counter++;
        if (counter==8)
            std::cout << "This is station is reciver";
        else
            std::cout << "This is tranzit station";
    }
    else
        std::cout << "frame drop";
    return reciv_frame;
}