You are given a tree consisting of n nodes.

Your task is to process q queries of the form: what is the distance between nodes a and b?

Input

The first input line contains two integers n and q: the number of nodes and queries. The nodes are numbered 1,2,…,n.

Then there are n−1 lines describing the edges. Each line contains two integers a and b: there is an edge between nodes a and b.

Finally, there are q lines describing the queries. Each line contains two integer a and b: what is the distance between nodes a and b?

Output

Print q integers: the answer to each query.

Constraints
1≤n,q≤2⋅105
1≤a,b≤n
Example

Input:
5 3
1 2
1 3
3 4
3 5
1 3
2 5
1 4

Output:
1
3
2

Solution:

#include <bits/stdc++.h>
using namespace std;
 
#define print(x) cerr << #x << " is " << x << endl;
#define int long long int
#define ll long long
#define vi vector<int>
#define vvi vector<vector<int>>
#define vpi vector<pair<int, int>>
#define all(v) (v).begin(), (v).end()
#define pii pair<int, int>
#define pb push_back
 
const int N = 5e5 + 10;
const int mod = 1e9 + 7;
 
vi g[N];
int u, v;
 
int dp[N][31];
int lvl[N];
 
void dfs(int u, int par){
    dp[u][0] = par;
    lvl[u] = lvl[par] + 1;
    
    for(int i = 1; i <= 30; ++i)
        if(dp[u][i-1] != -1)
            dp[u][i] = dp[dp[u][i-1]][i-1];
    
    for(int v: g[u]){
        if(v != par){
            dfs(v, u);
        }
    }
}
 
int lca(int u, int v){
    
    if(lvl[u] < lvl[v])
        swap(u, v);
    
    for(int i = 30; ~i; --i)
        if(lvl[u] - (1 << i) >= lvl[v])
            u = dp[u][i];
    
    if(u == v)
        return u;
    
    for(int i = 30; ~i; --i)
        if(dp[u][i] ^ dp[v][i])
            u = dp[u][i],v = dp[v][i];
        
    return dp[u][0];
}
 
int Parent(int u, int k) {
    k = lvl[u] - k;
    for(int i = 30; ~i; --i) {
        if(lvl[u] - (1 << i) >= k) {
            u = dp[u][i];
        }
    }
    return u == 0 ? -1 : u;
}
 
int distance(int u, int v) {
    return lvl[u] + lvl[v] - 2 * lvl[lca(u, v)];    
}
int32_t main()
{    
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    for(int i = 2; i <= n; ++i){
        int u, v;
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    memset(dp, -1, sizeof(dp));
    lvl[0] = -1;
    dfs(1, 0);
    
    /* ---------------write code below---------------------------- */
    while(q--) {
        int u, v;
        cin >> u >> v;
        cout << distance(u, v) << "\n";
    }   
    return 0;
}
