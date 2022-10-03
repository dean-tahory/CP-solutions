// Link to problem - https://codeforces.com/contest/1714/problem/G
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
class Graph
{
    int n; // number of vertices
    vector<tuple<int, ll, ll>> *Adj;
    bool *visited;
    void DFS_visit(int s);

public:
    Graph(int n);
    void addEdge(int u, int v, ll red, ll blue);
    ll *red_sums;
    int *r;
    vector<ll> blue_sums;
    void DFS();
    void printGraph();
    void printR();
};

Graph::Graph(int n)
{
    this->n = n;
    this->Adj = new vector<tuple<int, ll, ll>>[n];
    this->visited = new bool[n];

    this->red_sums = new ll[n];
    this->r = new int[n];
}

void Graph::addEdge(int u, int v, ll red, ll blue)
{
    this->Adj[u].push_back(tuple<int, int, int>(v, red, blue));
    this->Adj[v].push_back(tuple<int, int, int>(u, red, blue));
}

void Graph::DFS()
{
    for (int i = 0; i < n; i++)
    {
        visited[i] = false;
        red_sums[i] = 0;
        r[i] = 0;
    }
    DFS_visit(0);
}

void Graph::DFS_visit(int s)
{
    if (visited[s])
        return;
    visited[s] = true;
    for (auto u_tuple : Adj[s])
    {
        int u = get<0>(u_tuple);
        if (!visited[u])
        {
            red_sums[u] = get<1>(u_tuple) + red_sums[s];
            ll last_blue_sum = blue_sums.empty() ? 0 : blue_sums.back();
            blue_sums.push_back(get<2>(u_tuple) + last_blue_sum);
            r[u] = upper_bound(blue_sums.begin(), blue_sums.end(), red_sums[u]) - blue_sums.begin();

            DFS_visit(u);
            blue_sums.pop_back();
        }
    }
}

int main()
{
    string line;
    while (getline(cin, line))
    {
        istringstream iss(line);
        int t, n;
        iss >> t;
        for (int j = 0; j < t; j++)
        {
            getline(cin, line);
            iss = istringstream(line);
            iss >> n;
            Graph g(n);
            for (int i = 1; i < n; i++)
            {
                int u;
                ll red, blue;
                getline(cin, line);
                iss = istringstream(line);
                iss >> u >> red >> blue;
                u--;
                g.addEdge(i, u, red, blue);
            }
            g.DFS();
            for (int i = 1; i < n; i++)
            {
                cout << g.r[i] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}