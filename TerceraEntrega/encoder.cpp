#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <random>
#include <ctime>

using namespace std;

vector<double> encoder(const string& input){
    vector<double> encrypted;
    mt19937 generator(static_cast<unsigned>(time(nullptr))); // Random number generator with seed

    for(char ch : input){
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

string decoder(const vector<double>& encrypted){
    string decrypted;

    for(double value : encrypted){
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

vector<double> BRKGA(vector<double> parentA, vector<double> parentB){
    vector<double> child;
    mt19937 generator(static_cast<unsigned>(time(nullptr)));
    uniform_int_distribution<int> distribution(0, 1);

    int minlen = min(parentA.size(), parentB.size());
    for(int i=0; i<minlen; i++){
        if(distribution(generator) == 0){
            child.push_back(parentA[i]);
        }else{
            child.push_back(parentB[i]);
        }
    }
    return child;
}

int main() {
    string parentA, parentB, child;
    cin >> parentA;
    cin >> parentB;

    vector<double> encoded1 = encoder(parentA);
    vector<double> encoded2 = encoder(parentB);
    cout << "Valores encriptados: " << endl;
    for(int i=0; i<parentA.size(); i++){
        cout << i << " => " << "Padre A: " << encoded1[i] << " || Padre B: " << encoded2[i] << endl;
    }
    cout << endl;

    vector<double> encoded_child = BRKGA(encoded1, encoded2);

    string decoded = decoder(encoded_child);
    cout << "Padre A: " << parentA << endl;
    cout << "Padre B: " << parentB << endl;
    cout << "Hijo desencriptado: " << decoded << endl;

    return 0;
}

