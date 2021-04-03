
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main() {
    ofstream fout;
    fout.open("output");
    char output_map[20][96];

    int number;
    for (int i = 0; i < 20; i++) {

        for (int p = 0; p < 96; p++) {

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

    for (int i = 0; i < 20; i++) {
        for (int p = 0; p < 96; p++) {
            cout << output_map[i][p];
            fout << output_map[i][p];
        }
        fout << endl;
        cout << endl;
    }

    fout.close();
}

