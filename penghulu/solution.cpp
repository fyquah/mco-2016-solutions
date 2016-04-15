#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

vector<vector<int> > graph;
vector<int> weight, depth;
vector<long long> subtree_weight;
vector<vector<int> > parent_list;

// O(log n)
int k_th_parent(int node, int k){
    if(k == 0) return node;

    int lsb = k & -k, i;
    for(i = 0; !(1<<i & lsb); i++);

    return k_th_parent(parent_list[node][i], k & ~lsb);
}

// find p in the subtree of q rooted at 0
int find_subtree(int p, int q){
    int diff = depth[p] - depth[q];
    if(diff <= 0){
        return -1;
    }

    int parent_p = k_th_parent(p, diff-1);
    if(parent_list[parent_p][0] == q){
        return parent_p;
    }
    else{
        return -1;
    }

}

// O(n log n)
long long fill_weight_depth_parent(int root, int parent, int d){
    depth[root] = d;

    // this O(log n)
    if(parent != -1){
        parent_list[root].push_back(parent);
        int i = 0;
        int two_power_i_parent = parent;
        // 2^(i+1) parent = 2^i parent + 2^i parent
        while(parent_list[two_power_i_parent].size() >= parent_list[root].size()){
            two_power_i_parent = parent_list[two_power_i_parent][i];
            parent_list[root].push_back(two_power_i_parent);
            i++;
        }
    }

    subtree_weight[root] = weight[root];
    //cout << root << ' ' << weight[root] << endl;
    for(int i = 0; i < graph[root].size(); i++){
        if(graph[root][i] != parent){
            subtree_weight[root] += fill_weight_depth_parent(graph[root][i], root, d+1);
        }
    }
    return subtree_weight[root];
}



int main(){
    int n, query;
    cin >> n >> query;

    depth.resize(n);
    parent_list.assign(n, vector<int> ());
    graph.assign(n, vector<int> ());
    weight.resize(n);
    subtree_weight.assign(n, -1);

    for(int i = 0; i < n; i++){
        cin >> weight[i];
    }

    for(int i = 0; i < n-1; i++){
        int a, b;
        cin >> a >> b;
        graph[a-1].push_back(b-1);
        graph[b-1].push_back(a-1);
    }
    fill_weight_depth_parent(0, -1, 0);

    while(query--){
        int p, q;
        cin >> p >> q;
        p--; q--;

        if(p == q){
            cout << subtree_weight[0] << endl;
            continue;
        }

        // find p in the subtree of q rooted at 0
        int subtree = find_subtree(p, q);

        if(subtree == -1){
            cout << subtree_weight[q] << endl;
        }
        else{
            cout << subtree_weight[0] - subtree_weight[subtree] << endl;
        }

    }

    return 0;
}