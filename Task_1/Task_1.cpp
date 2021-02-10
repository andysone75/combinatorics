#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <string>
#include <cstdlib>

using namespace std;

vector<vector<int>*>* getAdjacencyList();
vector<int>* findCycle(vector<vector<int>*>*);
vector<int>* BFS(vector<vector<int>*>*, int, int);
vector<vector<int>*>* copy(vector<vector<int>*>*);
vector<int>* copy(vector<int>*);

int main()
{
    freopen("in.txt", "rt", stdin);
    freopen("out.txt", "wt", stdout);
    vector<vector<int>*>* adjacency_list = getAdjacencyList();
    vector<int>* cycle = findCycle(adjacency_list);

    cout << endl;
    if (cycle == nullptr)
        cout << 'A';
    else {
        sort(cycle->begin(), cycle->end());
        cout << 'N';
        for (vector<int>::const_iterator iter = cycle->begin(); iter < cycle->end(); iter++)
            cout << ' ' << (*iter)+1;
    }
    cout << "\n\n";

    //system("pause");
    return 0;
}

vector<int>* findCycle(vector<vector<int>*>* adjacency_list) {
    vector<vector<int>*>* adjlst_cpy = copy(adjacency_list);

    int i = -1;
    vector<int>* path;
    for (vector<vector<int>*>::iterator iter = adjlst_cpy->begin(); iter < adjlst_cpy->end(); ++iter) {
        ++i;
        for (vector<int>::iterator iter2 = (*iter)->begin(); iter2 < (*iter)->end(); ++iter2) {
            int dest = *iter2;
            *iter2 = -2;
            path = BFS(adjlst_cpy, i, dest);
            *iter2 = dest;
            if (path != nullptr) return path;
        }
    }

    return nullptr;
}

vector<int>* BFS(vector<vector<int>*>* graph, int source, int dest) {
    queue<int> q;
    q.push(source);
    vector<bool> used(graph->size());
    vector<int> d(graph->size()), p(graph->size());
    used[source] = true;
    p[source] = -1;
    int count = 0;
    while (!q.empty()) {
        count++;
        int v = q.front();
        q.pop();
        for (size_t i = 0; i < graph->at(v)->size(); ++i) {
            int to = graph->at(v)->at(i);
            if (to == -2) continue;
            if (!used[to]) {
                used[to] = true;
                q.push(to);
                d[to] = d[v] + 1;
                p[to] = v;
            }
        }
    }

    if (!used[dest])
        return nullptr;
    else {
        vector<int>* path = new vector<int>();
        for (int v = dest; v != -1; v = p[v])
            path->push_back(v);
        reverse(path->begin(), path->end());
        return path;
    }
}

vector<vector<int>*>* copy(vector<vector<int>*>* adjacency_list) {
    vector<vector<int>*>* adjlst_cpy = new vector<vector<int>*>();
    for (vector<vector<int>*>::const_iterator iter = adjacency_list->begin(); iter < adjacency_list->end(); iter++) {
        vector<int>* vec = new vector<int>();
        for (vector<int>::const_iterator iter2 = (*iter)->begin(); iter2 < (*iter)->end(); iter2++) {
            vec->push_back(*iter2);
        }
        adjlst_cpy->push_back(vec);
    }
    return adjlst_cpy;
}

vector<int>* copy(vector<int>* vec) {
    vector<int>* cpy = new vector<int>();
    for (vector<int>::const_iterator iter = vec->begin(); iter < vec->end(); iter++) {
        cpy->push_back(*iter);
    }
    return cpy;
}

vector<vector<int>*>* getAdjacencyList() {
    vector<vector<int>*>* adjacency_list = new vector<vector<int>*>();
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        vector<int>* adjacents = new vector<int>();

        istringstream f;
        string s;

        while (getline(cin, s)) {
            bool empty = s.empty();
            f = (istringstream)s;
            while (getline(f, s, ' ')) {
                int val = stoi(s) - 1;
                if (val != -1) adjacents->push_back(val);
            }
            if (!empty) break;
        }

        adjacency_list->push_back(adjacents);
    }
    return adjacency_list;
}