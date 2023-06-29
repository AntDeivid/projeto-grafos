#include <iostream>
#include <fstream>
#include <vector>
#include <list>
using namespace std;

bool isBipartite(vector<list<int>> grafo, int start, vector<string>& colors) {
    list<int> fila;
    fila.push_back(start);
    colors[start] = "gray";

    while(!fila.empty()) {
        int u = fila.front();
        fila.pop_front();

        for(auto v : grafo[u]) {
            if(colors[v] == "white") {
                colors[v] = (colors[u] == "gray") ? "black" : "gray";
                fila.push_back(v);
            } else if(colors[v] == colors[u]) {
                return false;
            }
        }
    }
    return true;
}

bool Bipartite(vector<list<int>> grafo) {
    vector<string> colors;
    colors.resize(grafo.size(), "white");

    for(int i = 0; i < grafo.size(); i++) {
        if(colors[i] == "white") {
            if(!isBipartite(grafo, i, colors)) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    fstream file;
    file.open("NAO/snarks_28_vertices.txt");
    
    while (!file.eof()) {
        int n, m;
        file >> n >> m;

        vector<list<int>> grafo;
        grafo.resize(n);

        for(int i = 0; i < m; i++) {
            int u, v;
            file >> u >> v;
            grafo[u].push_back(v);
            grafo[v].push_back(u);
        }

        if(Bipartite(grafo)) {
            cout << "SIM" << endl;
        } else {
            cout << "NAO" << endl;
        }
    }

    file.close();
    return 0;
}