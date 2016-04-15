#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;

int N, a[MAXN];

int main() {

    scanf("%d",&N);
    for (int i = 1; i <= N; i++)
        scanf("%d",&a[i]);

    int l, r, ans = 0;

    // left to right
    for (l = 1, r = 2; r <= N; r++)
        if (a[r] >= a[l])
            ans = max(ans,r-l), l = r;

    // right to left
    for (r = N, l = N-1; l > 0; l--)
        if (a[l] >= a[r]) 
            ans = max(ans,r-l), r = l;

    printf("%d\n", ans);

    return 0;
}