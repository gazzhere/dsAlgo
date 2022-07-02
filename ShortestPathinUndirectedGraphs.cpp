#include <unordered_map>
#include <queue>
#include <list>
vector<int> shortestPath(vector<pair<int, int>> edges, int n, int m, int s, int t)
{

    unordered_map<int, list<int>> adj;
    for (int i = 0; i < edges.size(); i++)
    {
        int u = edges[i].first;
        int v = edges[i].second;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    unordered_map<int, bool> visited;
    unordered_map<int, int> parent;
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
    while (!q.empty())
    {
        int front = q.front();
        q.pop();
        for (auto neighbour : adj[front])
        {
            if (!visited[neighbour])
            {
                visited[neighbour] = true;
                parent[neighbour] = front;
                q.push(neighbour);
            }
        }
    }
    vector<int> ans;
    int currNode = t;
    ans.push_back(t);
    while (currNode != s)
    {
        currNode = parent[currNode];
        ans.push_back(currNode);
    }
    reverse(ans.begin(), ans.end());
    return ans;
}