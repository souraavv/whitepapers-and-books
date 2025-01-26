You are given a tree consisting of n nodes.

Your task is to determine for each node the maximum distance to another node.

Input

The first input line contains an integer n: the number of nodes. The nodes are numbered 1,2,.,n.

Then there are n-1 lines describing the edges. Each line contains two integers a and b: there is an edge between nodes a and b.

Output

Print n integers: for each node 1,2,.,n, the maximum distance to another node.

Constraints
1ónó2ú105
1óa,bón
Example

Input:
5
1 2
1 3
3 4
3 5

Output:
2 3 2 3 3

Code : :
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
 
void dfs(int u, int par) {
    in[u] = 0;
    for(int v: g[u]) {
        if(v != par) {
            dfs(v, u);
            in[u] = max(1 + in[v], in[u]);
        }
    }   
}
 
void dfs2(int u, int par) {
    int mx1 = -1, mx2 = -1;
    for(int v : g[u]) {
        if(v != par) {
            if(in[v] >= mx1) {
                mx2 = mx1;
                mx1 = in[v];
            }
            else if(in[v] > mx2) {
                mx2 = in[v];
            }
        }
    }   
    for(int v : g[u]) {
        if(v != par) {
            int use = mx1;
            if(in[v] == use) {
                use = mx2;
            }
            out[v] = max(2 + use, 1 + out[u]);
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
        cout << max(in[i], out[i]) << ' ';
    }
    cout << '\n';
}

Link to this code: https://cses.fi/paste/644e047b2e6816e3c87ea/
