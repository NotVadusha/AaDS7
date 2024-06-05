#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <limits>

using namespace std;

vector<vector<int>> convertToAdjacencyList(const vector<vector<int>>& adjacencyMatrix) {
    int n = adjacencyMatrix.size();
    vector<vector<int>> adjacencyList(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (adjacencyMatrix[i][j] != 0) {
                adjacencyList[i].push_back(j);
            }
        }
    }

    return adjacencyList;
}

void printAdjacencyList(const vector<vector<int>>& adjacencyList) {
    for (int i = 0; i < adjacencyList.size(); ++i) {
        cout << i << ": ";
        for (int j : adjacencyList[i]) {
            cout << j << " ";
        }
        cout << endl;
    }
}

void BFS(const vector<vector<int>>& adjacencyList, int start) {
    vector<bool> visited(adjacencyList.size(), false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        cout << v << " ";

        for (int u : adjacencyList[v]) {
            if (!visited[u]) {
                visited[u] = true;
                q.push(u);
            }
        }
    }
    cout << endl;
}


void DFS(const vector<vector<int>>& adjacencyList, int start) {
    vector<bool> visited(adjacencyList.size(), false);
    stack<int> s;

    s.push(start);

    while (!s.empty()) {
        int v = s.top();
        s.pop();

        if (!visited[v]) {
            visited[v] = true;
            cout << v << " ";

            for (int u : adjacencyList[v]) {
                if (!visited[u]) {
                    s.push(u);
                }
            }
        }
    }
    cout << endl;
}


void Dijkstra(const vector<vector<int>>& adjacencyMatrix, int start) {
    int n = adjacencyMatrix.size();
    vector<int> dist(n, numeric_limits<int>::max());
    vector<bool> visited(n, false);
    dist[start] = 0;

    for (int i = 0; i < n - 1; ++i) {
        int minDistance = numeric_limits<int>::max();
        int minIndex = -1;

        for (int j = 0; j < n; ++j) {
            if (!visited[j] && dist[j] < minDistance) {
                minDistance = dist[j];
                minIndex = j;
            }
        }

        if (minIndex == -1) break;

        visited[minIndex] = true;

        for (int j = 0; j < n; ++j) {
            if (adjacencyMatrix[minIndex][j] && !visited[j] && dist[minIndex] != numeric_limits<int>::max() &&
                dist[minIndex] + adjacencyMatrix[minIndex][j] < dist[j]) {
                dist[j] = dist[minIndex] + adjacencyMatrix[minIndex][j];
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (dist[i] == numeric_limits<int>::max()) {
            cout << "INF ";
        }
        else {
            cout << dist[i] << " ";
        }
    }
    cout << endl;
}


int main() {
    // Приклад матриці суміжності
    vector<vector<int>> adjacencyMatrix = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 1, 0},
        {0, 1, 0, 1, 0},
        {0, 1, 1, 0, 1},
        {1, 0, 0, 1, 0}
    };

    vector<vector<int>> adjacencyList = convertToAdjacencyList(adjacencyMatrix);
    printAdjacencyList(adjacencyList);

    cout << "BFS starting from vertex 0: ";
    BFS(adjacencyList, 0);

    cout << "DFS starting from vertex 0: ";
    DFS(adjacencyList, 0);

    cout << "Dijkstra's shortest path starting from vertex 0: ";
    Dijkstra(adjacencyMatrix, 0);

    return 0;
}
