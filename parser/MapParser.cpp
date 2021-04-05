
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main() {
    ofstream fout;
    fout.open("output");
    int filas = 20;
    int columnas = 96;
    char output_map[filas][columnas];

    int number;
    for (int i = 0; i < filas; i++) {

        for (int p = 0; p < columnas; p++) {

            cin >> number;
       
            if (number == 0) {
                output_map[i][p] = ' ';
            }
            else {
                int sum = number + 32;
                char ascii = char(sum);
                output_map[i][p] = ascii;
            }
        }
    }

    for (int i = 0; i < filas; i++) {
        for (int p = 0; p < columnas; p++) {
            cout << output_map[i][p];
            fout << output_map[i][p];
        }
        fout << endl;
        cout << endl;
    }

    fout.close();
}

