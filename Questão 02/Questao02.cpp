#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Actor {
    string ator;
    string filme;
    int numeroBacon;
};

void encontrarGrauBacon(const unordered_map<string, list<string>>& grafo) {
    queue<Actor> fila;
    unordered_map<string, int> grauBacon;
    unordered_map<string, bool> visitado;

    for (const auto& entry : grafo) {
        grauBacon[entry.first] = -1;
        visitado[entry.first] = false;
    }

    vector<Actor> atoresResultantes;

    for (const auto& entry : grafo) {
        string ator = entry.first;

        fila.push({ator, "", 0});
        visitado[ator] = true;
        grauBacon[ator] = 0;

        while (!fila.empty()) {
            Actor atorAtual = fila.front();
            fila.pop();

            string atorAtualNome = atorAtual.ator;
            int grauAtual = atorAtual.numeroBacon;

            for (const auto& filme : grafo.at(atorAtualNome)) {
                string atorVizinho = filme;
                if (!visitado[atorVizinho]) {
                    visitado[atorVizinho] = true;
                    grauBacon[atorVizinho] = grauAtual + 1;
                    fila.push({atorVizinho, filme, grauAtual + 1});
                }
            }
        }

        for (const auto& entry : grauBacon) {
            atoresResultantes.push_back({entry.first, "", entry.second});
        }

        grauBacon.clear();
        for (const auto& entry : grafo) {
            grauBacon[entry.first] = -1;
            visitado[entry.first] = false;
        }

        sort(atoresResultantes.begin(), atoresResultantes.end(), [](const Actor& a, const Actor& b) {
            return a.ator < b.ator;
        });

    }

    for (const auto& ator : atoresResultantes) {
        cout << "O numero de Bacon de " << ator.ator << " e " << ator.numeroBacon << " pelo filme " << ator.filme << endl;
    }
}

int main() {
    ifstream arquivo("input.txt");
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo" << endl;
        return 0;
    }

    unordered_map<string, list<string>> grafo;

    string linha;

    while (getline(arquivo, linha)) {
        string ator, filme, coautor;

        int pos = linha.find(";");
        int pos2 = linha.rfind(";");

        ator = linha.substr(0, pos);
        filme = linha.substr(pos + 1, pos2 - pos - 1);
        coautor = linha.substr(pos2 + 1);

        if (grafo.find(ator) == grafo.end()) {
            grafo[ator] = list<string>();
        }
        grafo[ator].push_back(coautor);

        if (grafo.find(coautor) == grafo.end()) {
            grafo[coautor] = list<string>();
        }
        grafo[coautor].push_back(ator);
    }

    arquivo.close();

    encontrarGrauBacon(grafo);

    return 0;
    
}