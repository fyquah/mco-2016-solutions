#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int R[1005][1005], C[1005][1005];

int main() {

    int N, M, Q;
    scanf("%d%d%d",&N,&M,&Q);
    for (int i = 0, op, x, y, z; i < Q; i++) {
        scanf("%d%d%d%d",&op,&x,&y,&z);

        if (op)
            C[y][x]++, C[z+1][x]--;
        else
            R[x][y]++, R[x][z+1]--;
    }

    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++)
            R[i][j] += R[i][j-1], C[j][i] += C[j-1][i];
    
    int max_num = 0, cnt = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (R[i][j] + C[i][j] == max_num)
                cnt++;
            else if (R[i][j] + C[i][j] > max_num)
                max_num = R[i][j] + C[i][j], cnt = 1;
        }
    }

    ll ans = 1LL * max_num * cnt;
    printf("%lld\n", ans);
}