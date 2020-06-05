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
    const int n;
    const int m;
    vector<Edge> Data;
    int Start;
    int End;
};

#define INF 1e+6

Input* Read(const char* filename);

int main()
{
    vector<int> d;
    Input* input = Read("input.txt");
    int a[];

    if (input == nullptr) {
        cout << "Input reading error" << endl;
        return -1;
    }

    for (int i = 0; i < input->Data.size(); ++i)
        d.push_back(INF);

    d[input->Start] = 0;

    // Algorithm
    for (int i = 0; i < input->n - 1; ++i) {
        for (int j = 0; j < input->m; ++j) {
            int u = input->Data[j].u;
            int v = input->Data[j].v;
            int w = input->Data[j].w;
            
            if (d[v] > d[u] + w)
                d[v] = d[u] + w;
        }
    }

    for (auto iter = d.begin(); iter < d.end(); ++iter) {
        cout << *iter << endl;
    }
    
    return 0;
}

Input* Read(const char* filename) {
    auto ifinput = ifstream(filename);
    auto input = string(istreambuf_iterator<char>(ifinput), istreambuf_iterator<char>());
    ifinput.close();

    int pos = input.find('\n');
    int n = stoi(input.substr(0, pos));
    if (n < 0) return nullptr;

    int m;
    vector<Edge> edges;
    
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

    auto result = new Input({ n, m });

    result->Start = start - 1;
    result->End = end - 1;

    return result;
}