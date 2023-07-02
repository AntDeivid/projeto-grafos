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
    string name;
    string movie;
    int baconNumber;
};

void findBaconNumber(const unordered_map<string, list<pair<string, string>>>& graph) {
    queue<Actor> queue;
    unordered_map<string, bool> visited;
    unordered_map<string, int> baconNumbers;

    for (const auto& entry : graph) {
        visited[entry.first] = false;
        baconNumbers[entry.first] = -1;
    }

    vector<Actor> actors;

    queue.push({ "Kevin Bacon", "", 0 });
    visited["Kevin Bacon"] = true;
    baconNumbers["Kevin Bacon"] = 0;

    while (!queue.empty()) {
        Actor current = queue.front();
        queue.pop();

        /*if (current.name != "Kevin Bacon") {
            actors.push_back(current);
        }*/
        
        actors.push_back(current);

        for (const auto& coactor : graph.at(current.name)) {
            string nextActor = coactor.first;
            string movie = coactor.second;

            if (!visited[nextActor]) {
                queue.push({ nextActor, movie, current.baconNumber + 1 });
                visited[nextActor] = true;
                baconNumbers[nextActor] = current.baconNumber + 1;
            }
        }
    }

    sort(actors.begin(), actors.end(), [](const Actor& a, const Actor& b) {
        return a.name < b.name;
    });

    for (const auto& actor : actors) {
        cout << "O numero de Bacon de " << actor.name << " e " << actor.baconNumber << " pelo filme " << actor.movie << endl;
    }
}

int main() {
    ifstream file("input.txt");
    if (!file.is_open()) {
        cout << "Erro ao abrir o arquivo" << endl;
        return 0;
    }

    unordered_map<string, list<pair<string, string>>> graph;

    string line;
    while (getline(file, line)) {
        string actor, movie, coactor;

        size_t firstDelimiter = line.find(';');
        size_t secondDelimiter = line.find(';', firstDelimiter + 1);

        actor = line.substr(0, firstDelimiter);
        movie = line.substr(firstDelimiter + 1, secondDelimiter - firstDelimiter - 1);
        coactor = line.substr(secondDelimiter + 1);

        graph[actor].push_back({ coactor, movie });
        graph[coactor].push_back({ actor, movie });
    }

    file.close();

    findBaconNumber(graph);

    return 0;
}
