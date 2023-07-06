#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Estrutura auxiliar para armazenar os dados de um ator
struct Actor {
    string name;
    string movie;
    int baconNumber;
};

// Função para encontrar o número de Bacon para cada ator no grafo
void findBaconNumber(const unordered_map<string, list<pair<string, string>>>& graph) {
    // Estruturas auxiliares
    queue<Actor> queue;
    unordered_map<string, bool> visited;
    unordered_map<string, int> baconNumbers;

    // Inicializa as estruturas auxiliares
    for (const auto& entry : graph) {
        visited[entry.first] = false; // Marca todos os atores como não visitados
        baconNumbers[entry.first] = -1; // Inicializa o número de Bacon de todos os atores como -1 (não calculado)
    }

    vector<Actor> actors; // Vetor para armazenar os atores

    queue.push({ "Kevin Bacon", "", 0 });
    baconNumbers["Kevin Bacon"] = 0;

    while (!queue.empty()) {
        Actor current = queue.front();
        queue.pop();
        
        actors.push_back(current);
        // Percorre os atores adjacentes
        for (const auto& coactor : graph.at(current.name)) {
            string nextActor = coactor.first; // Próximo ator = ator adjacente
            string movie = coactor.second;

            // Se o ator não foi visitado, adiciona na fila e marca como visitado
            if (!visited[nextActor]) {
                queue.push({ nextActor, movie, current.baconNumber + 1 }); // Adiciona na fila, incrementando o número de Bacon
                visited[nextActor] = true;
                baconNumbers[nextActor] = current.baconNumber + 1; // Atualiza o número de Bacon
            }
        }
    }

    // Ordena os atores por ordem alfabética
    sort(actors.begin(), actors.end(), [](const Actor& a, const Actor& b) {
        return a.name < b.name;
    });

    // Imprime os atores, seus números de Bacon e por qual filme eles se conectam
    for (const auto& actor : actors) {
        cout << "O numero de Bacon de " << actor.name << " e " << actor.baconNumber << " pelo filme " << actor.movie << endl;
    }
}

int main() {
    ifstream file("input.txt");
    if (!file.is_open()) { // Verifica se o arquivo foi aberto corretamente
        cout << "Erro ao abrir o arquivo" << endl;
        return 0;
    }

    unordered_map<string, list<pair<string, string>>> graph; // Cria a estrutura de dados para armazenar o grafo

    string line;
    while (getline(file, line)) {
        string actor, movie, coactor;

        // Encotra os delimitadores
        size_t firstDelimiter = line.find(';');
        size_t secondDelimiter = line.find(';', firstDelimiter + 1);

        // Extrai os dados da linha, separando-os pelos delimitadores
        actor = line.substr(0, firstDelimiter);
        movie = line.substr(firstDelimiter + 1, secondDelimiter - firstDelimiter - 1);
        coactor = line.substr(secondDelimiter + 1);

        // Adiciona os atores e o filme no grafo, fazendo o grafo ser não-direcionado
        graph[actor].push_back({ coactor, movie });
        graph[coactor].push_back({ actor, movie });
    }

    file.close();

    findBaconNumber(graph);

    return 0;
}
