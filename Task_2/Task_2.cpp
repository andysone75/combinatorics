#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cstdlib>

using namespace std;

void input(int[]);
int getCharacterNumber(char);
void print(int[2], int[2]);
vector<vector<int>*>* adjacencyList(int[2]);
bool DFS(vector<vector<int>*>*, int, int, stack<int>*, bool[64]);
void toChessNotation(int, int[2]);

int main()
{
    int knight[2], pawn[2];
    input(knight);
    input(pawn);

    knight[0]--;
    knight[1]--;

    pawn[0]--;
    pawn[1]--;

    int deadzones[2] = { -1, -1 };
    if (pawn[1] - 1 > 0) {
        if (pawn[0] - 1 > 0)
            deadzones[0] = (pawn[1] - 1) * 8 + pawn[0] - 1;
        if (pawn[0] + 1 < 8)
            deadzones[1] = (pawn[1] - 1) * 8 + pawn[0] + 1;
    }

    vector<vector<int>*>* adjlst = adjacencyList(deadzones);

    stack<int>* path = new stack<int>();
    bool used[64] = { false };
    DFS(adjlst, knight[1] * 8 + knight[0], pawn[1] * 8 + pawn[0], path, used);
    vector<int> _path;
    while (path->size() > 0) {
        _path.push_back(path->top());
        path->pop();
    }
    reverse(_path.begin(), _path.end());
    char chars[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    for (vector<int>::const_iterator iter = _path.begin(); iter != _path.end(); ++iter) {
        int value[2];
        toChessNotation(*iter, value);
        cout << chars[value[0]] << value[1] + 1 << ' ';
    }
    cout << endl;

    system("pause");
}

void toChessNotation(int index, int value[2]) {
    value[0] = index % 8;
    value[1] = index / 8;
}

bool DFS(vector<vector<int>*>* g, int v, int dest, stack<int>* path, bool used[64]) {
    used[v] = true;
    path->push(v);
    if (v == dest) return true;
    for (vector<int>::const_iterator iter = g->at(v)->begin(); iter != g->at(v)->end(); ++iter) {
        if (!used[*iter]) {
            if (DFS(g, *iter, dest, path, used)) return true;
        }
    }
    path->pop();
    return false;
}

vector<vector<int>*>* adjacencyList(int deadzones[2]) {
    vector<vector<int>*>* adjlst = new vector<vector<int>*>();

    for (int i = 0; i < 64; ++i) {
        if (i == deadzones[0] || i == deadzones[1]) {
            vector<int>* moves = new vector<int>();
            adjlst->push_back(moves);
            continue;
        }

        vector<int>* moves = new vector<int>();

        int x = i % 8;
        int y = i / 8;

        if (y + 2 < 8) {
            if (x + 1 < 8) {
                int value = (y + 2) * 8 + (x + 1);
                if (!(value == deadzones[0] || value == deadzones[1]))
                    moves->push_back(value);
            }
            if (x - 1 >= 0) {
                int value = (y + 2) * 8 + (x - 1);
                if (!(value == deadzones[0] || value == deadzones[1]))
                    moves->push_back(value);
            }
        }

        if (x - 2 >= 0) {
            if (y + 1 < 8) {
                int value = (y + 1) * 8 + (x - 2);
                if (!(value == deadzones[0] || value == deadzones[1]))
                    moves->push_back(value);
            }
            if (y - 1 >= 0) {
                int value = (y - 1) * 8 + (x - 2);
                if (!(value == deadzones[0] || value == deadzones[1]))
                    moves->push_back(value);
            }
        }

        if (y - 2 >= 0) { 
            if (x - 1 >= 0) {
                int value = (y - 2) * 8 + (x - 1);
                if (!(value == deadzones[0] || value == deadzones[1]))
                    moves->push_back(value);
            }
            if (x + 1 < 8) {
                int value = (y - 2) * 8 + (x + 1);
                if (!(value == deadzones[0] || value == deadzones[1]))
                    moves->push_back(value);
            }
        }

        if (x + 2 < 8) {
            if (y - 1 >= 0) {
                int value = (y - 1) * 8 + (x + 2);
                if (!(value == deadzones[0] || value == deadzones[1]))
                    moves->push_back(value);
            }
            if (y + 1 < 8) {
                int value = (y + 1) * 8 + (x + 2);
                if (!(value == deadzones[0] || value == deadzones[1]))
                    moves->push_back(value);
            }
        }

        adjlst->push_back(moves);
    }

    return adjlst;
}

void print(int knight[2], int pawn[2]) {
    cout << endl;
    for (int y = 8; y >= 1; --y) {
        for (int x = 1; x <= 8; ++x) {
            if (x == knight[0] && y == knight[1])
                cout << ' ' << 'K' << ' ';
            else if (x == pawn[0] && y == pawn[1])
                cout << ' ' << 'P' << ' ';
            else
                cout << "   ";

            if (x != 8) cout << '|';
        }
        if (y != 1)
            cout << "\n-------------------------------" << endl;
        else cout << endl;
    }
}

void input(int arr[]) {
    string str = "";

    bool condition = true;
    while(condition) {
        condition = false;
        cin >> str;
        if (str.length() != 2) {
            cout << "! - Invalid input length" << endl;
            condition = true;
        } else if (getCharacterNumber(str[0]) == -1 || getCharacterNumber(str[1]) != -1) {
            cout << "! - Invalid input format" << endl;
            condition = true;
        } else if (str[1] - '0' > 8) {
            cout << "! - Input range: 1..8" << endl;
            condition = true;
        }
    }

    arr[0] = getCharacterNumber(str[0]);
    arr[1] = str[1] - '0';
}

int getCharacterNumber(char ch) {
    switch (ch)
    {
        case 'a': return 1;
        case 'b': return 2;
        case 'c': return 3;
        case 'd': return 4;
        case 'e': return 5;
        case 'f': return 6;
        case 'g': return 7;
        case 'h': return 8;
        default: return -1;
    }
}