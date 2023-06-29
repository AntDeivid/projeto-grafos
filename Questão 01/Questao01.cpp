#include <iostream>
#include <fstream>
#include <vector>
#include <list>
using namespace std;

bool isBipartite(vector<list<int>> grafo, int start, vector<int>& colors) {
    list<int> queue;
    queue.push_back(start);
    colors[start] = 0;

    while(!queue.empty()) {
        int current = queue.front();
        queue.pop_front();

        for(auto vizinho : grafo[current]) {
            if(colors[vizinho] == -1) {
                colors[vizinho] = 1 - colors[current];
                queue.push_back(vizinho);
            }
            else if(colors[vizinho] == colors[current]) { return false; }
        }
    }
    return true;
}

int main() {
    fstream file;
    file.open("SIM/cubic_bipartite_26_vertices.txt");
    int n, m;
    file >> n >> m;

    vector<list<int>> grafo;
    grafo.resize(n);

    int count {m};
    while(count > 0) {
        int u, v;
        file >> u >> v;
        grafo[u].push_back(v);
        grafo[v].push_back(u);
        count--;
    }
    file.close();

    
}