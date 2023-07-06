#include <iostream>
#include <fstream>
#include <vector>
#include <list>
using namespace std;

bool isValidGraphColor(vector<list<int>> grafo, int start, vector<string>& colors) {
    // Estruturas auxiliares
    list<int> fila;
    fila.push_back(start);
    colors[start] = "gray";

    while(!fila.empty()) {
        int u = fila.front();
        fila.pop_front();

        // Percorre os vértices adjacentes
        for(auto v : grafo[u]) {
            // Se o vértice não foi visitado, colore e adiciona na fila
            if(colors[v] == "white") {
                // Se o vértice atual for cinza, o próximo será preto, e vice-versa
                colors[v] = (colors[u] == "gray") ? "black" : "gray";
                fila.push_back(v); // Adiciona na fila
            }
            // Se o vértice adjacente já foi visitado e possui a mesma cor do vértice atual, a coloração é inválida
            else if(colors[v] == colors[u]) { return false; }
        }
    }
    // Se não houver conflitos, a coloração é válida
    return true;
}

bool validGraphColor(vector<list<int>> grafo) {
    // Estruturas auxiliares
    vector<string> colors;
    colors.resize(grafo.size(), "white");

    // Percorre todos os vértices do grafo
    for(int i = 0; i < grafo.size(); i++) {
        // Se o vértice não foi visitado, verifica se a coloração é válida
        if(colors[i] == "white") {
            if(!isValidGraphColor(grafo, i, colors)) {
                return false; // Se não for, retorna falso
            }
        }
    }
    return true;
}

int main() {
    fstream file;
    file.open("SIM/cubic_bipartite_26_vertices.txt"); // Abrir arquivo
    
    while (!file.eof()) { 
        int n, m;
        file >> n >> m;

        vector<list<int>> grafo;
        grafo.resize(n);

        for(int i = 0; i < m; i++) {
            int u, v;
            file >> u >> v;
            // Criação do grafo/lista de adjacência
            grafo[u].push_back(v);
            grafo[v].push_back(u);
        }

        if(validGraphColor(grafo)) { // Chamada da função
            cout << "SIM" << endl;
        } else {
            cout << "NAO" << endl;
        }
    }

    file.close();
    return 0;
}