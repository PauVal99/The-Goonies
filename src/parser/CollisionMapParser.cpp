
#include <iostream>
#include <string>
#include <fstream>
using namespace std;


bool inArray(int number, int array[30]){

    for(int i = 0; i < 30; i++){
        if(number == array[i])return true;
    }

    return false;
}


int main() {
    ofstream fout;
    fout.open("output_cm");
   

    int air[30] = {0,6,7,8,9,10,11,17,18,19,20,21,22,28,29,30,31,32,33, 57, 58, 59, 61};
    int number;

    int filas = 20;
    int columnas = 96;

    char output_map[filas][columnas];

    for (int i = 0; i < filas; i++) {

        for (int p = 0; p < columnas; p++) {

            cin >> number;
       
            if (inArray(number, air)) {
                output_map[i][p] = ' ';
            }
            else if(number == 40) {
                output_map[i][p] = '3';
            }
            else if(number == 14 || number == 25){
                output_map[i][p] = '2';
            }
            else output_map[i][p] = '1';
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

