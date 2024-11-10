#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <functional>
#include <fstream>
#include <sstream>

using namespace std;

vector<vector<double>> encoder(const string& filename){
    vector<vector<double>> encryptedGenomes;
    ifstream infile(filename);

    if(!infile){
        cout << "Archivo invalido." << endl;
        return encryptedGenomes;
    }

    mt19937 rndm(static_cast<unsigned>(time(nullptr)));
    string line;
    while(getline(infile, line)){
        vector<double> encryptedGenome;
        for(char ch : line){
            if(ch == 'A'){
                uniform_real_distribution<double> rangeA(0.0, 0.25);
                encryptedGenome.push_back(rangeA(rndm));

            }else if (ch == 'C'){
                uniform_real_distribution<double> rangeC(0.26, 0.50);
                encryptedGenome.push_back(rangeC(rndm));

            }else if(ch == 'T'){
                uniform_real_distribution<double> rangeT(0.51, 0.75);
                encryptedGenome.push_back(rangeT(rndm));

            }else if (ch == 'G'){
                uniform_real_distribution<double> rangeG(0.76, 1.0);
                encryptedGenome.push_back(rangeG(rndm));

            }else{
                cout <<"Carácter inválido.\n";
                encryptedGenome.clear();
                break;
            }
        }
        if(!encryptedGenome.empty()){
            encryptedGenomes.push_back(encryptedGenome);
        }
    }
    return encryptedGenomes;
}

vector<string> decoder(vector<vector<double>>& encryptedGenomes) {
    vector<string> decryptedGenomes;

    for(auto& encryptedGenome : encryptedGenomes){
        string decrypted;
        
        for(double value : encryptedGenome){
            if(value >= 0.0 && value <= 0.25){
                decrypted += 'A';
            }else if(value > 0.25 && value <= 0.50){
                decrypted += 'C';
            }else if(value > 0.50 && value <= 0.75){
                decrypted += 'T';
            }else if(value > 0.75 && value <= 1.0){
                decrypted += 'G';
            }else{
                cout << "Valor inválido." << endl;
                decrypted.clear();
                break;
            }
        }
        if(!decrypted.empty()){ 
            decryptedGenomes.push_back(decrypted);
        }
    }
    return decryptedGenomes;
}


vector<vector<double>> populate(){
    vector<vector<double>> population;
    //Not sure yet how to manipulate the genome text files here yet. How do we classify each genome as elite or not-elite? Should I encode the file first? If so, create a new file and encode it in there.
    //WIP
    return population;
}


double solutionScore(vector<double> genome){
    double score = 0.0;
    for(double gene : genome){
        score += gene;
    }
    return score;
}

vector<double> evaluateScores(vector<vector<double>>& population){
    vector<double> scores;
    for(const auto& it : population){
        scores.push_back(solutionScore(it));
    }
    return scores;
}

vector<vector<double>> eliteSelection(vector<vector<double>> population, vector<double> scores, int population_size, int elite_proportion){
    int count = static_cast<int>(population_size * elite_proportion);
    vector<pair<double, vector<double>>> scorePairs;

    for(int i=0; i<population_size; ++i){
        scorePairs.emplace_back(scores[i], population[i]);
    }
    sort(scorePairs.begin(), scorePairs.end(), greater<>());
    
    vector<vector<double>> elite;
    for(int i=0; i<count; ++i){
        elite.push_back(scorePairs[i].second);
    }
    return elite;
}

vector<double> crossover(vector<double>& elite, vector<double>& nonElite, int genome_size, double bias, mt19937& rndm){
    vector<double> child(genome_size);
    uniform_real_distribution<double> selectionDist(0.0, 1.0);

    for(int i=0; i<genome_size; ++i){
        if(selectionDist(rndm) < bias){
            child[i] = elite[i];
        }else{
            child[i] = nonElite[i];
        }
    }
    return child;
}

void mutateGenome(vector<double> genome, double mutation_rate, mt19937& rndm){
    uniform_real_distribution<double> mutationRange(0.0, 1.0);
    uniform_real_distribution<double> valueRange(0.0, 1.0);

    for(double& gene : genome){
        if(mutationRange(rndm)< mutation_rate){
            gene = valueRange(rndm);
        }
    }    
}

vector<vector<double>> rePopulate(vector<vector<double>>& elite, vector<vector<double>>& population, int population_size, int genome_size, double bias, double mutation_rate){
    vector<vector<double>> newPopulation;
    mt19937 rndm(static_cast<unsigned>(time(nullptr)));

    for(auto& it : elite){
        newPopulation.push_back(it);
    }

    uniform_int_distribution<int> eliteRange(0, elite.size()-1);
    uniform_int_distribution<int> nonEliteRange(elite.size(), population_size-1);

    while(newPopulation.size()<population_size){
        auto& parentElite = elite[eliteRange(rndm)];
        auto& parentNonElite = population[nonEliteRange(rndm)];

        auto child = crossover(parentElite, parentNonElite, genome_size, bias, rndm);
        mutateGenome(child, mutation_rate, rndm);
        newPopulation.push_back(child);
    }
    return newPopulation;
}

vector<string> BRKGA(int population_size, int genome_size, double elite_proportion, double mutation_rate, double bias, int number_of_generations, const string& filename){
    vector<vector<double>> encrypted_genomes = encoder(filename);
    
    auto population = populate(); //Population receives encrypted_genomes as parameter.

    for(int generation=0; generation < number_of_generations; ++generation){
        auto scores = evaluateScores(population);
        auto elite = eliteSelection(population, scores, population_size, elite_proportion);
        population = rePopulate(elite, population, population_size, genome_size, bias, mutation_rate);

        double bestScore = *max_element(scores.begin(), scores.end());
        cout << "Generación " << generation << " || Mejor puntuación: " << bestScore << endl;
    }
    
    vector<string> decryptedPopulation = decoder(population);
    return decryptedPopulation;
}