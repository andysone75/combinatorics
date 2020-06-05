#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

struct Edge {
    int u, v, w;
};

struct Input {
    int n;
    int m;
    vector<Edge> Data;
    int Start;
    int End;
};

#define INF 1e+6

Input* Read(const char* filename);

int main()
{
    vector<vector<int>> a, p;
    Input* input = Read("input.txt");

    if (input == nullptr) {
        system("pause");
        return -1;
    }

    for (int i = 0; i < input->n; ++i) {
        a.push_back(vector<int>());
        p.push_back(vector<int>());
        for (int j = 0; j < input->m; ++j) {
            a[i].push_back(INF);
            p[i].push_back(-1);
        }
    }

    a[input->Start][0] = 0;

    // Algorithm
    for (int i = 1; i < input->n; ++i) {
        for (int j = 0; j < input->m; ++j) {
            int u = input->Data[j].u;
            int v = input->Data[j].v;
            int w = input->Data[j].w;
            
            if (a[v][i] > a[u][i - 1] + w) {
                a[v][i] = a[u][i - 1] + w;
                p[v][i] = u;
            }
        }
    }

    // A matrix output
    /*for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < a[i].size(); ++j) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }*/

    int j;
    int min = INF;
    for (int i = 0; i < a[input->End].size(); ++i) {
        if (a[input->End][i] < min) {
            min = a[input->End][i];
            j = i;
        }
    }

    if (min == INF) {
        cout << "N" << endl;
        return 0;
    }

    vector<int> path;
    int i = input->End;
    while (j > 0) {
        path.push_back(i);
        i = p[i][j];
        --j;
    }
    path.push_back(input->Start);
    reverse(path.begin(), path.end());

    cout << "Y" << endl;
    for (int i = 0; i < path.size(); ++i) {
        cout << path[i] + 1 << " ";
    }
    cout << endl << min << endl;
    
    system("pause");
    return 0;
}

Input* Read(const char* filename) {
    auto ifinput = ifstream(filename);
    auto input = string(istreambuf_iterator<char>(ifinput), istreambuf_iterator<char>());
    ifinput.close();

    if (input.empty()) {
        cout << "File \"input.txt\" doesn't exist in this directory" << endl;
        return nullptr;
    }

    int pos = input.find('\n');
    int n = stoi(input.substr(0, pos));

    if (n < 0) {
        cout << "Invalid input" << endl;
        return nullptr;
    }

    auto result = new Input();
    result->n = n;
    int m;
    
    for (int v = 0; v < n; ++v) {
        ++pos;
        int temp = pos;
        pos = input.find('\n', pos);
        string line = input.substr(temp, pos-temp);

        size_t linePos = 0;
        while (linePos < line.size()) {
            size_t temp = linePos;
            linePos = line.find(' ', linePos);
            if (linePos == string::npos) break;
            int u = stoi(line.substr(temp, linePos - temp)) - 1;

            temp = ++linePos;
            linePos = line.find(' ', linePos);
            if (linePos == string::npos) break;
            int w = stoi(line.substr(temp, linePos - temp));

            ++linePos;

            result->Data.push_back(Edge({ u, v, w }));
            m = result->Data.size();
        }
    }

    int temp = ++pos;
    pos = input.find('\n', pos);
    int start = stoi(input.substr(temp, pos - temp));

    ++pos;
    int end = stoi(input.substr(pos));

    result->m = m;
    result->Start = start - 1;
    result->End = end - 1;

    return result;
}