#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<vector<int>*>* listsOfPrev = new vector<vector<int>*>();
    for (int i = 0; i < n; ++i) {
        istringstream f;
        string s;
        vector<int>* list = new vector<int>();
        
        while (getline(cin, s)) {
            f = (istringstream)s;
            while (getline(f, s, ' ')) {
                int val = stoi(s);
                list->push_back(val);
            }
;        }

        listsOfPrev->push_back(list);
    }

    system("pause");
}