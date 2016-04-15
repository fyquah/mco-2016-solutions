#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second

typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;
typedef priority_queue< ii,vector<ii>,greater<ii> > pqii;

const int MAXN = 500005;

ll N, M, A, B;
vii adjList[MAXN];

ll dist[2][MAXN]; pqii pq;

void dijkstra(int start, int mode) {
    dist[mode][start] = 0;
    pq = pqii(); pq.push(ii(0,start));
    while (!pq.empty()) {
        ii front = pq.top(); pq.pop();

        ll d = front.fi;
        ll u = front.se;

        if (d > dist[mode][u]) continue;

        for (ll i = 0; i < adjList[u].size(); i++) {
            ii next = adjList[u][i];
            ll vv = next.se;
            ll vd = next.fi;

            if (dist[mode][vv] == -1 || dist[mode][vv] > dist[mode][u] + vd) {
                dist[mode][vv] = dist[mode][u] + vd;
                pq.push(ii(dist[mode][vv],vv));
            }
        }
    }
}

int main() {

    scanf("%lld%lld%lld%lld",&N,&M,&A,&B);
    for (int i = 0; i < M; i++) {
        ll u, v, w;
        scanf("%lld%lld%lld",&u,&v,&w);

        adjList[u].push_back(ii(w,v));
        adjList[v].push_back(ii(w,u));
    }

    dijkstra(A,0);
    dijkstra(B,1);

    ll D = -1;
    for (int i = 1; i <= N; i++)
        if (dist[0][i] != -1 && dist[1][i] != -1)
            if (D == -1 || D > max(dist[0][i],dist[1][i]))
                D = max(dist[0][i],dist[1][i]);
        
    printf("%lld\n", D);

    return 0;
}