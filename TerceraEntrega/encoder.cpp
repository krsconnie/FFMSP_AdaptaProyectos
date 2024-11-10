#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>

using namespace std;

vector<double> encoder(const string& input){
    vector<double> encrypted;
    mt19937 generator(static_cast<unsigned>(time(nullptr))); // Random number generator with seed

    for (char ch : input){
        if(ch == 'A'){
            uniform_real_distribution<double> distA(0.0, 0.25);
            encrypted.push_back(distA(generator));

        }else if (ch == 'C'){
            uniform_real_distribution<double> distC(0.26, 0.50);
            encrypted.push_back(distC(generator));

        }else if (ch == 'T'){
            uniform_real_distribution<double> distT(0.51, 0.75);
            encrypted.push_back(distT(generator));

        }else if (ch == 'G'){
            uniform_real_distribution<double> distG(0.76, 1.0);
            encrypted.push_back(distG(generator));

        }else{
            cout <<"Carácter inválido.\n";
            return {};
        }
    }
    return encrypted;
}

string decoder(const vector<double>& encrypted) {
    string decrypted;

    for (double value : encrypted) {
        if (value >= 0.0 && value <= 0.25) {
            decrypted += 'A';
        } else if (value > 0.25 && value <= 0.50) {
            decrypted += 'C';
        } else if (value > 0.50 && value <= 0.75) {
            decrypted += 'T';
        } else if (value > 0.75 && value <= 1.0) {
            decrypted += 'G';
        } else {
            cout << "Valor inválido en la posición" << value <<".\n";
            return "";
        }
    }
    return decrypted;
}

/*
int main() {
    string input;
    cin >> input;

    vector<double> encoded = encoder(input);
    cout << "Encrypted values: ";
    for (double val : encoded) {
        cout << val << " ";
    }
    cout << endl;

    string decoded = decoder(encoded);
    cout << "Decrypted string: " << decoded << endl;

    return 0;
}
*/
