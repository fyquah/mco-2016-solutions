#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
#define ll long long
using namespace std;
const int MX = 100010;
int N, K;
vector<vector<int> > adj(MX);
ll d[MX], D[MX], s[MX], sz = 0;;
bool vis[MX];

void fill_size(int u, int p) {
	s[u] = 0;
	sz++;
	for (int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i];
		if (v != p && !vis[v]) {
			fill_size(v, u);
			s[u] += 1+s[v];
		}
	}
}

int centroid(int u, int p) {
	for (int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i];
		if (s[v] >= sz/2 && v != p && !vis[v]) {
			return centroid(v, u);
		}
	}
	return u;
}

map<ll, ll> A;
vector<ll> B;
ll ans = 0;

void fill_a(int u, int p) {
	B.push_back(D[u]);
	for (int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i];
		if (v != p && !vis[v]) {
			D[v] = D[u]+d[v];
			fill_a(v, u);
		}
	}
}

void solve(int u) {
	vis[u] = 1;
	D[u] = d[u]; 
	A.clear();
	A[D[u]]++;
	if (d[u]+2 == K) ans++;
	for (int i = 0; i < adj[u].size(); i++) {
		B.clear();
		int v = adj[u][i];
		if (!vis[v]) {
			D[v] = D[u]+d[v];
			fill_a(v, u);
			for (int j = 0; j < B.size(); j++) {
				ll search = K-2+d[u]-B[j];
				ans += A[search];
			}
			for (int j = 0; j < B.size(); j++) A[B[j]]++;
		}
	}
	for (int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i];
		if (!vis[v]) {
			sz = 0;
			fill_size(v, u);
			int C = centroid(v, u);
			solve(C);
		}
	}
}

int main() {
	scanf("%d%d", &N, &K);
	for (int i = 0; i < N-1; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	for (int i = 1; i <= N; i++) d[i] = adj[i].size()-2;
	sz = 0;
	fill_size(1, 1);
	int c = centroid(1, 1);
	solve(c);
	printf("%lld\n", ans);
	return 0;
}