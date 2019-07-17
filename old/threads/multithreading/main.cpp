#include <dirent.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <thread>
#include <ctime>
#include <unistd.h>

void read(std::string &filename, std::string &buf);
void purge(std::string &filename);
void emplace_to(std::string &filename, std::string &buf);
void luchok();
void ukropchik();
void ololo();

int main() {

    std::thread fucking_thread1(luchok);
    std::thread fucking_thread2(ukropchik);
    std::thread fucking_thread3(ololo);


    if(fucking_thread1.joinable())
        fucking_thread1.join();
    if(fucking_thread2.joinable())
        fucking_thread2.join();
    if(fucking_thread3.joinable())
        fucking_thread3.join();

    return 0;
}

void read(std::string &filename, std::string &buf){
    std::fstream file;
    file.open(filename, std::ios::in);
    getline(file, buf);
    file.close();
}

void purge(std::string &filename){
    //remove(filename.c_str());
}

void emplace_to(std::string &filename, std::string &buf){
    std::fstream file;
    file.open(filename, std::ios::out);
    file << buf;
    file.close();
}


void luchok(){
    DIR *dir;
    struct dirent *ent;
    std::string buf;
    std::string filename;

    if ((dir = opendir("/home/metalleg/CLionProjects/multithreading/list")) != nullptr) {
        while ((ent = readdir(dir)) != nullptr){
            if (strcmp(ent->d_name, ".") && strcmp(ent->d_name, "..")){
                if (strlen(ent->d_name) < 10){
                    filename =  std::string("/home/metalleg/CLionProjects/multithreading/list/") + ent->d_name;
                    read(filename, buf);
                    purge(filename);
                    filename = std::string("/home/metalleg/CLionProjects/multithreading/a_catalog/") + ent->d_name;
                    std::cout << "move " << ent->d_name << " to /home/metalleg/CLionProjects/multithreading/a_catalog/\n";
                    emplace_to(filename, buf);
                    sleep(1);
                }
            }
        }
        closedir(dir);
    }
    else {
        std::cerr << "Error! Directory not found!\n";
        exit(0);
    }
}


void ukropchik(){
    DIR *dir;
    struct dirent *ent;
    std::string buf;
    std::string filename;

    if ((dir = opendir("/home/metalleg/CLionProjects/multithreading/list")) != nullptr) {
        while ((ent = readdir(dir)) != nullptr){
            if (strcmp(ent->d_name, ".") && strcmp(ent->d_name, "..")){
                if (strlen(ent->d_name) >= 10){
                    filename =  std::string("/home/metalleg/CLionProjects/multithreading/list/") + ent->d_name;
                    read(filename, buf);
                    purge(filename);
                    filename = std::string("/home/metalleg/CLionProjects/multithreading/b_catalog/") + ent->d_name;
                    std::cout << "move " << ent->d_name << " to /home/metalleg/CLionProjects/multithreading/b_catalog/\n";
                    emplace_to(filename, buf);
                    sleep(1);
                }
            }
        }
        closedir(dir);
    }
    else {
        std::cerr << "Error! Directory not found!\n";
        exit(0);
    }
}

void ololo(){
   DIR *dir;
   struct dirent *ent;
   std::string buf;
   std::string filename;

    if ((dir = opendir("/home/metalleg/CLionProjects/multithreading/list")) != nullptr) {
        while ((ent = readdir(dir)) != nullptr){
           if (strcmp(ent->d_name, ".") && strcmp(ent->d_name, "..")){
               printf("ololo\n");
               sleep(1);
            }
        }
        closedir(dir);
    }
    else {
        std::cerr << "Error! Directory not found!\n";
        exit(0);
    }
}