#include <bits/stdc++.h>
using namespace std;
class graph
{
public:
    unordered_map<int, list<pair<int, int>>> adj;
    void addEdge(int u, int v, int w)
    {
        adj[u].push_back(make_pair(v, w));
    }
    void printList()
    {
        for (auto i : adj)
        {
            cout << i.first << " ->";
            for (auto j : i.second)
            {
                cout << j.first << "," << j.second << ",";
            }
            cout << endl;
        }
    }
    void dfs(int node, unordered_map<int, bool> &vis, stack<int> &topo)
    {
        vis[node] = true;
        for (auto neighbour : adj[node])
        {
            if (!vis[neighbour.first])
            {
                dfs(neighbour.first, vis, topo);
            }
        }
        topo.push(node);
    }
    void getShortestPath(int src, vector<int> &dist, stack<int> &s)
    {

        dist[src] = 0;
        while (!s.empty())
        {
            int top = s.top();
            s.pop();
            if (dist[top] != INT_MAX)
            {
                for (auto i : adj[top])
                {
                    if (dist[top] + i.second < dist[i.first])
                    {
                        dist[i.first] = dist[top] + i.second;
                    }
                }
            }
        }
    }
};
int main()
{
    graph g;
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 3, 6);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 4, 4);
    g.addEdge(2, 5, 2);
    g.addEdge(3, 4, -1);
    g.addEdge(4, 5, -2);
    g.printList();
    int n = 6;
    unordered_map<int, bool> vis;

    stack<int> s;
    for (int i = 0; i < n; i++)
    {
        if (!vis[i])
        {
            g.dfs(i, vis, s);
        }
    }

    vector<int> dist(n);
    for (int i = 0; i < n; i++)
    {
        dist[i] = INT_MAX;
    }
    int src = 1;
    g.getShortestPath(src, dist, s);
    cout << "answer" << endl;

    for (int i = 0; i < dist.size(); i++)
    {
        cout << dist[i] << ", ";
    }
    cout << endl;
    return 0;
}