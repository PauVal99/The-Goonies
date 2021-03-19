
#include <iostream>
#include <string>
#include<fstream>
using namespace std;

int main()
{
   

    ofstream fout;
    fout.open("output.txt");
    char output_map[20][32];

    int number;
    
    for (int i = 0; i < 20; i++) {

        for (int p = 0; p < 32; p++) {

            cin >> number;
       
            if (number == 0) {
                output_map[i][p] = ' ';
            }
            else {
                char ascii = number + 96;
                output_map[i][p] = ascii;
            }
        }
    }

    

    for (int i = 0; i < 20; i++) {
        for (int p = 0; p < 32; p++) {
            fout << output_map[i][p];
        }
        fout << endl;
    }

    fout.close();

    system("pause");
}

