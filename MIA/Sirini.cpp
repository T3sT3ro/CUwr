//
// Created by Tooster on 2017-10-13.
//

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 100005;
const int P = 10000007;
int n;
vector<int> V;
int UF[P];
int _next[P];
int sets;

int _find(int a) {
    int parent = UF[a];
    while (parent != UF[parent]) {
        parent = UF[parent];
        UF[a] = parent;
    }
    return parent;
}

void _union(int a, int b) {
    a = _find(a);
    b = _find(b);
    if (a != b) UF[b] = a;
}

struct edge {
    int cost;
    int a, b;

    edge();

    edge(int cost, int a, int b) : cost(cost), a(a), b(b) {}

    bool operator<(const edge &rhs) const {
        return (cost < rhs.cost) ||
               (cost == rhs.cost && a < rhs.a) ||
               (cost == rhs.cost && a == rhs.a && b < rhs.b);
    }
};

void init() {
    for (int i = 0; i < P; ++i)
        UF[i] = i;

    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int a;
        scanf("%d", &a);
        V.push_back(a);
        _next[a] = a;
    }
    sort(V.begin(), V.end());
    V.resize(distance(V.begin(), unique(V.begin(), V.end())));
    sets = V.size();
    for (int i = V.back() - 1, _nextVar = V.back(); i > 0; --i) {
        if (_next[i] != 0) {
            _next[i] = _nextVar = i;
        } else {
            _next[i] = _nextVar;
        }
    }
}

int sirini_main() {
    init();

    vector <edge> links;
    for (int i = 0; i < V.size() - 1; ++i) {
        for (int p = V[i], k = 1; p * k <= V.back(); ++k) {

            if (k == 1)
                links.push_back(edge(_next[p * k + 1] - (p * k), p, _next[p * k + 1]));
            else
                links.push_back(edge(_next[p * k] - (p * k), p, _next[p * k]));
        }
    }

    sort(links.begin(), links.end());

    long long cost = 0;
    for (int k = 0; k < links.size() && sets > 1; ++k) {
        edge tmp = links[k];
        if (_find(tmp.a) != _find(tmp.b)) {
            _union(tmp.a, tmp.b);
            sets--;
            cost += tmp.cost;
        }
    }

    printf("%d", cost);
    return 0;
}