#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>

using namespace std;

struct Graph {
    int Count;
    vector<vector<int>>* Data;
    int Start;
    int End;
};

struct Edge {
    int u, v, w;
};

#define INF 1e+6

Graph* ReadInput(const char* filename);

int main()
{
    Graph* input = ReadInput("input.txt");
    vector<Edge> edges;
    vector<int> d;

    // Initialization
    for (int i = 0; i < input->Count; ++i) {
        d.push_back(INF);
    }

    d[input->Start] = 0;

    // Algorithm
    for (int i = 0; i < input->Count - 1; ++i) {
        for (int j = 0; j < edges.size(); ++j) {
            int u = edges[j].u;
            int v = edges[j].v;
            int w = edges[j].w;
            
            if (d[v] > d[u] + w)
                d[v] = d[u] + w;
        }
    }

    for (auto iter = d.begin(); iter < d.end(); ++iter) {
        cout << *iter << endl;
    }
    
    return 0;
}

Graph* ReadInput(const char* filename) {
    vector<vector<int>>* graph = new vector<vector<int>>();

    ifstream ifinput = ifstream(filename);

    char s[128];
    ifinput.getline(s, 128, '\n');
    
    int vertCount = atoi(s);

    for (int i = 0; i < vertCount; ++i) {
        graph->push_back(vector<int>());

        ifinput.getline(s, 128, '\n');
        
        char c[128];
        memset(c, 0, 128);
        char len = strlen(s);
        for (char j = 0; j < len; ++j) {
            if (s[j] == ' ') {
                graph->at(i).push_back(atoi(c));
                memset(c, 0, 128);
            }
            else {
                c[strlen(c)] = s[j];
            }
        }
    }

    ifinput.getline(s, 128, '\n');
    int start = atoi(s) - 1;

    ifinput.getline(s, 128, '\n');
    int end = atoi(s) - 1;

    ifinput.close();

    Graph* output = new Graph({vertCount, graph, start, end});
    return output;
}