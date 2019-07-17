#include <iostream>
#include <iomanip>

#define I 18
#define N (5 + I % 3)
#define J (I % 7)
#define Y ((I + 1) % N)

char distance[3][7][95] =
        {{
                 "AB=30; BD=40+; AC=50+; CD=10; EA=35; ED=25+; BC=20; CE=40+",
                 "AC=20; AD=30+; BE=10+; BD=25; CB=85; CD=15+",
                 "AB=30+; BD=20; AC=5; CB=15; CD=20+; EA=25; CE=15; DE=40+",
                 "AB=20+; BD=30+; CA=40; CB=10+; CD=15+; AE=35; EC=15; ED=40",
                 "AE=5+; AD=60; BE=80; CB=10; DE=50+; EC=35",
                 "AB=30; BD=30+; CA=60; CD=15+; CB=10+; AE=30+; CE=25+; DE=40+",
                 "AE=60+; BC=10+; CA=25; CD=15; CE=30+; DE=20+; EB=90"
         },{
                 "AB=30; BC=15+; AD=20+; DC=20+; BD=15+; DF=25+; CE=25+; ED=10; EF=40+; DF=25+; FA=15",
                 "AF=25+; AB=10; BC=30+; CF=75+; DE=50+; EB=40; FE=15",
                 "AB=20; BC=30; AD=20+; DC=20+; CE=10+; DE=35; DF=10; EF=40+; FA=15",
                 "BA=40; BC=10+; AD=30+; DB=35+; DC=5+; DE=20+; EС=65+; AF=25; FE=20",
                 "AF=25; BA=35; BE=70+; BD=10; BC=45+; CE=20+; DE=90+; EF=5+",
                 "AB=40+; AD=35; BC=10+; CD=35+; DE=35+; EB=10; EF=15; FA=5",
                 "BA=35; BC=10+; AD=40; DB=10; CD=25+; AF=60; DF=10+; CE=70+; DE=15; EF=30+"
         },{
                 "AB=20+; BC=30; AD=30; BD=20+; DC=15; CE=35; DE=20+; DF=10+; FE=15; FG=15+; DG=15+; GA=35",
                 "AE=10+; BC=20+; BD=20+; CD=60+; CF=70+; DG=15+; DE=40+; FG=5+; GA=25",
                 "AB=30; BC=40+; DA=35; DB=10+; DC=85; CE=35; ED=20; EF=5+; FD=15+; GF=30; GD=30+; AG=45+",
                 "AG=50+; AE=15; AC=15+; BC=10; CF=15; DB=10; DA=40; DE=20+; EF=35+; FG=60+",
                 "AD=60+; BA=10; BF=65+; BC=20+; CG=5+; CE=70+; DC=15; ED=20; EF=35; FG=25",
                 "AB=15+; BC=30+; BD=20; AD=15+; DC=20+; CE=35+; DE=40+; DF=10; FE=20+; GF=10+; GD=50+; AG=35+",
                 "BA=20; BC=15; BD=25+; DC=30+; DA=25+; CE=35+; ED=40; FE=30+; DF=15; FG=5+; GD=15+; GA=25"
         }};
#define NA ((unsigned int) (0 - (unsigned int)1))

unsigned int min(unsigned int a, unsigned int b){
    return (a<b)?a:b;
}

unsigned int pos(const unsigned int mas[N]){
    unsigned int value = mas[0];
    unsigned int number = 0;
    for(unsigned int i = 1; i < N; ++i)
        if(mas[i] < value){
            value = mas[i];
            number = i;
        }
    if(value == NA)
        return NA;
    return number;
}

void print_mas(const unsigned int my_mas[N][N]){
    char symbol[7][2]= {"A", "B", "C", "D", "E", "F", "G"};
    std::cout << "    ";
    for (int i = 0; i < N; ++i)
        std::cout << std::setw(4) << symbol[i];
    std::cout << std::endl;
    for (int i = 0; i < N; ++i) {
        std::cout << std::setw(4) << symbol[i];
        for (int j = 0; j < N; ++j)
            if(my_mas[i][j] != NA)
                std::cout << std::setw(4) << my_mas[i][j];
            else
                std::cout << std::setw(4) << "--";
        std::cout << std::endl;
    }
}

void print_pos_mas(unsigned int my_mas[N][N]){
    char sumbol[7][2]= {"A", "B", "C", "D", "E", "F", "G"};
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            if(my_mas[i][j] != NA)
                std::cout << std::setw(4) << sumbol[my_mas[i][j]];
            else
                std::cout << std::setw(4) << "-";
        std::cout << std::endl;
    }
}

int main() {
    std::cout << "i = " << I << std::endl;  // i = 18
    std::cout << "N = " << N << std::endl;  // N = 5
    std::cout << "j = " << J << std::endl;  // j = 4
    std::cout << "I = " << Y << " (E)" << std::endl;  // I = 4(E)
    std::cout << "distance = \n" << distance[N - 5][J] << std::endl;
    unsigned int my_mas[N][N] = {
            /*     0A	1B	2C	3D	4E */
            /*A */{0,	NA,	NA,	60,	5},
            /*B */{NA,	0,	NA,	NA,	80},
            /*C */{NA,  10,	0,	NA,	NA},
            /*D */{NA,  NA,	NA,	0,	50},
            /*E */{5,	NA, 35, 50, 0}
    };
    unsigned int L[N][N][N],/* № преобразования, i, j*/ D[N][N], G[N][N],
            del[N][N];
    std::cout << std::endl;
    std::cout << "Graph =" << std::endl;
    print_mas(my_mas);

    std::cout << std::endl << "-------------" << std::endl;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            L[0][i][j] = my_mas[i][j];
    int n;
    for (n = 1; n < N-1; ++n) {
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j) {
                unsigned int sum;
                if (L[n - 1][i][0] == NA || L[0][0][j] == NA)
                    sum = NA;
                else
                    sum = L[n - 1][i][0] + L[0][0][j];
                L[n][i][j] = sum;
                for (int k = 1; k < N; ++k) {
                    if (L[n - 1][i][k] == NA || L[0][k][j] == NA)
                        sum = NA;
                    else
                        sum = L[n - 1][i][k] + L[0][k][j];
                    L[n][i][j] = min(L[n][i][j], sum);
                }
            }
        int clone = 1;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                if (L[n][i][j] != L[n - 1][i][j])
                    clone = 0;
        std::cout << std::endl;
        std::cout << "L" << n+1 << " =" << std::endl;
        print_mas(L[n]);
        if (clone == 1)
            break;
    }




    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            D[i][j] = L[n-1][i][j];
    std::cout << std::endl << "-------------" << std::endl;
    std::cout << std::endl;
    std::cout << "D = L" << n << " =" << std::endl;
    print_mas(D);




    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (i != j)
                G[i][j] = my_mas[i][j];
            else
                G[i][j] = NA;
    std::cout << std::endl;
    std::cout << "Г =" << std::endl;
    print_mas(G);

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            unsigned int mas[N];
            for (int k = 0; k < N; ++k) {
                if (i != j) {
                    if (G[i][k] == NA || D[k][j] == NA)
                        mas[k] = NA;
                    else
                        mas[k] = G[i][k] + D[k][j];
                } else
                    mas[k] = NA;
            }
            del[i][j] = pos(mas);
        }

    std::cout << std::endl;
    std::cout << "del =" << std::endl;
    print_pos_mas(del);
    return 0;
}
