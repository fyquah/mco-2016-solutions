#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

#define sz(x) (int)(x).size()

struct line {
    ll m, c;

    line () {}
    line (ll _m, ll _c) : m(_m), c(_c) {}

    ld x_intersect(line l) {
        return (ld) (l.c - c) / (ld) (m - l.m);
    }

    ld pass(ld x) {
        return m * x + c;
    }
};

bool cmp (line a, line b) {
    return (a.m == b.m ? a.c < b.c : a.m < b.m);
}

class ConvexHull {
private:
    deque<line> d;
    
    bool lower(line newLine) {
        if (sz(d) < 2) return false;
    
        line cmp = d[sz(d)-2];
        return cmp.x_intersect(newLine) <= cmp.x_intersect(d[sz(d)-1]);
    }
public:
    void push_line(line l) {
        while (lower(l)) d.pop_back();
        d.push_back(l);
    }
    int query(int N) {
        int bad = N - d.size();
        while (sz(d) > 1 && (d[0].pass(d[0].x_intersect(d[1])) <= (ld)0))
            d.pop_front(), bad++;
        for (int i = 1; i+1 < d.size(); i++)
            if ((ll)d[i].x_intersect(d[i-1]) == (ll)d[i].x_intersect(d[i+1]))
                bad++;
        return bad;
    }
};

int N;
vector<line> v;

int main() {

    scanf("%d",&N); v.assign(N,line());
    for (int i = 0, a, b; i < N; i++) {
        scanf("%d%d",&a,&b);

        v[i] = line(b, - a * b);
    }

    sort(v.begin(),v.end(),cmp);

    ConvexHull h;
    for (int i = 0; i < N; i++) {
        if (i+1 < N && v[i].m == v[i+1].m) continue;
        
        h.push_line(v[i]);
    }

    int ans = h.query(N);

    printf("%d\n", ans);

    return 0;
}