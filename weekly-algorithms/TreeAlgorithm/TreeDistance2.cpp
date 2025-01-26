You are given a tree consisting of n nodes.

Your task is to determine for each node the sum of the distances from the node to all other nodes.

Input

The first input line contains an integer n: the number of nodes. The nodes are numbered 1,2,…,n.

Then there are n−1 lines describing the edges. Each line contains two integers a and b: there is an edge between nodes a and b.

Output

Print n integers: for each node 1,2,…,n, the sum of the distances.

Constraints
1≤n≤2⋅105
1≤a,b≤n
Example

Input:
5
1 2
1 3
3 4
3 5

Output:
6 9 5 8 8

Link to this code: https://cses.fi/paste/628b72b1775a873fc8834/
#include <bits/stdc++.h>
using namespace std;
 
#define hey(x) cerr << #x << " : " << x << "\n";
#define int long long int
#define ll long long
#define vi vector<int>
#define vvi vector<vector<int> >
#define vpi vector<pair<int, int> >
#define vvpi vector<vector<pair<int, int> > >
#define all(v) (v).begin(), (v).end()   
#define rall(v) (v).rbegin(), (v).rend()
#define pii pair<int, int>
#define pb push_back
#define SZ(x) (int)(x).size()
#define inf 1e12
#define F first
#define S second
#define PI 3.1415926535897932384626
#define fill(v, val) memset((v), val, sizeof(v))
#define fast ios::sync_with_stdio(false); cin.tie(0);
#define hey2(x, y) cerr << #x << " : " << x << "," << #y << " : " << y << '\n';
 
const int N = 1e6 + 10;
const int mod = 1e9 + 7;
const double pi = acos(-1);
 
void print(vi &a) {
    for(int i : a) cerr << i << ' ';
    cerr << "\n";
}
 
vvi g;
int in[N], out[N];
int cnt[N];
int Count = 0;
 
void dfs(int u, int par) {
    Count++;
    in[u] = 0;
    cnt[u] = 1;
    for(int v: g[u]) {
        if(v != par) {
            dfs(v, u);
            cnt[u] += cnt[v];
            in[u] += in[v] + cnt[v];
        }
    }  
}
 
void dfs2(int u, int par) {
    if(par) {
        // sibling effect :
        int Newin = in[par] - (in[u] + cnt[u]);
        out[u] = Newin + (cnt[par] - cnt[u]);
        // parent effect :
        if(out[par])
            out[u] += out[par] + (Count - cnt[par]);
    }
    for(int v : g[u]) {
        if(v != par) {
            dfs2(v, u);
        }
    }
}
 
 
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    g = vvi(n + 1);
    for(int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].pb(v), g[v].pb(u);
    }
    dfs(1, 0);
    dfs2(1, 0);
    for(int i = 1; i <= n; ++i) {
        cout << in[i] + out[i] << ' ';
    }
    cout << '\n';
}
