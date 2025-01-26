A company has n employees, who form a tree hierarchy where each employee has a boss, except for the general director.

Your task is to process q queries of the form: who is employee x's boss k levels higher up in the hierarchy?

Input

The first input line has two integers n and q: the number of employees and queries. The employees are numbered 1,2,…,n, and employee 1 is the general director.

The next line has n−1 integers e2,e3,…,en: for each employee 2,3,…,n their boss.

Finally, there are q lines describing the queries. Each line has two integers x and k: who is employee x's boss k levels higher up?

Output

Print the answer for each query. If such a boss does not exist, print −1.

Constraints
1≤n,q≤2⋅105
1≤ei≤i−1
1≤x≤n
1≤k≤n
Example

Input:
5 3
1 1 3 3
4 1
4 2
4 3

Output:
3
1
-1

Solution : 

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
 
int32_t main()
{    
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    for(int i = 2; i <= n; ++i){
        int val; cin >> val;
        g[i].pb(val);
        g[val].pb(i);
    }
    memset(dp, -1, sizeof(dp));
    lvl[0] = -1;
    dfs(1, 0);
    
    /* ---------------write code below---------------------------- */
    
    while(q--) {
        int x, k;
        cin >> x >> k;
        cout << Parent(x, k) << '\n';
    }
 
   
   
    return 0;
}
