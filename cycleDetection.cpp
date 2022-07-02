// using bfs traversal
#include <unordered_map>
#include <queue>
#include <list>
bool isCycBFS(int src, unordered_map<int, bool> &visited, unordered_map<int, list<int>> &adj)
{
    unordered_map<int, int> parent;
    parent[src] = -1;
    visited[src] = 1;
    queue<int> q;
    q.push(src);
    while (!q.empty())
    {
        int front = q.front();
        q.pop();
        for (auto neighbour : adj[front])
        {
            if (visited[neighbour] == true && neighbour != parent[front])
            {
                return true;
            }
            else if (!visited[neighbour])
            {
                q.push(neighbour);
                visited[neighbour] = 1;
                parent[neighbour] = front;
            }
        }
    }
    return false;
}
string cycleDetection(vector<vector<int>> &edges, int n, int m)
{
    //    CREATING ADJACENCY LIST
    unordered_map<int, list<int>> adj;
    for (int i = 0; i < m; i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    //     to handle disconnected conponent
    unordered_map<int, bool> visited;
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            bool ans = isCycBFS(i, visited, adj);
            if (ans == 1)
            {
                return "Yes";
            }
        }
    }
    return "No";
}
// using dfs
bool isCycleDFS(int node, int parent, unordered_map<int, bool> &visited, unordered_map<int, list<int>> &adj)
{
    visited[node] = true;
    for (auto neighbour : adj[node])
    {
        if (!visited[neighbour])
        {
            bool cycleDetected = isCycleDFS(neighbour, node, visited, adj);
            if (cycleDetected)
                return true;
        }
        else if (neighbour != parent)
        {
            return true;
        }
    }
    return false;
}
string cycleDetection(vector<vector<int>> &edges, int n, int m)
{
    //    CREATING ADJACENCY LIST
    unordered_map<int, list<int>> adj;
    for (int i = 0; i < m; i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    //     to handle disconnected conponent
    unordered_map<int, bool> visited;
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            bool ans = isCycleDFS(i, -1, visited, adj);
            if (ans == 1)
            {
                return "Yes";
            }
        }
    }
    return "No";
}

// cycle detection in directed grapgh
#include <unordered_map>
#include <list>
bool checkCycleDFS(int node, unordered_map<int, bool> &visited, unordered_map<int, bool> &dfsVisited, unordered_map<int, list<int>> adj)
{
    visited[node] = true;
    dfsVisited[node] = true;
    for (auto neighbour : adj[node])
    {
        if (!visited[neighbour])
        {
            bool cycleDetected = checkCycleDFS(neighbour, visited, dfsVisited, adj);
            if (cycleDetected)
                return true;
        }
        else if (dfsVisited[neighbour])
        {
            return true;
        }
    }
    dfsVisited[node] = false;
    return false;
}

int detectCycleInDirectedGraph(int n, vector<pair<int, int>> &edges)
{
    // create adj list
    unordered_map<int, list<int>> adj;
    for (int i = 0; i < edges.size(); i++)
    {
        int u = edges[i].first;
        int v = edges[i].second;
        adj[u].push_back(v);
    }
    // call dfs for all component
    unordered_map<int, bool> visited;
    unordered_map<int, bool> dfsVisited;
    for (int i = 1; i <= n; i++)
    {
        if (!visited[i])
        {
            bool cycleFound = checkCycleDFS(i, visited, dfsVisited, adj);
            if (cycleFound)
                return true;
        }
    }
    return false;
}
// cycle dtection in dAG
// using khans algo
#include <bits/stdc++.h>
int detectCycleInDirectedGraph(int n, vector<pair<int, int>> &edges)
{
    unordered_map<int, list<int>> adj;
    for (int i = 0; i < edges.size(); i++)
    {
        int u = edges[i].first - 1;
        int v = edges[i].second - 1;
        adj[u].push_back(v);
    }
    //    find all indegree
    vector<int> indegree(n);
    for (auto i : adj)
    {
        for (auto j : i.second)
        {
            indegree[j]++;
        }
    }
    //     0 indegree push
    queue<int> q;
    for (int i = 0; i < n; i++)
    {
        if (indegree[i] == 0)
        {
            q.push(i);
        }
    }
    //     do bfd
    int cnt = 0;
    while (!q.empty())
    {
        int front = q.front();
        q.pop();
        cnt++;
        for (auto neighbour : adj[front])
        {
            indegree[neighbour]--;
            if (indegree[neighbour] == 0)
                q.push(neighbour);
        }
    }
    if (cnt == n)
    {
        return false;
    }
    else
    {
        return true;
    }
}