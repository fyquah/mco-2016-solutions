#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500000;

int N, M, A, B;
vector<int> adjList[MAXN];

int dist[MAXN];

int main() {

    scanf("%d%d%d%d",&N,&M,&A,&B);

    for (int i = 0, u, v, w; i < M; i++) {
        scanf("%d%d%d",&u,&v,&w);

        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    memset(dist,-1,sizeof(dist)); dist[A] = 0;
    queue<int> q; q.push(A);
    while (!q.empty()) {
        int u = q.front(); q.pop();

        for (int i = 0; i < adjList[u].size(); i++) {
            int v = adjList[u][i];

            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    int ans = (dist[B] + 1) / 2;
    printf("%d\n", ans);

    return 0;
}