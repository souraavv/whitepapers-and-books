You are given a tree consisting of n nodes.

The diameter of a tree is the maximum distance between two nodes. Your task is to determine the diameter of the tree.

Input

The first input line contains an integer n: the number of nodes. The nodes are numbered 1,2,.,n.

Then there are n-1 lines describing the edges. Each line contains two integers a and b: there is an edge between nodes a and b.

Output

Print one integer: the diameter of the tree.

Constraints
1髇�2�105
1骯,b髇
Example

Input:
5
1 2
1 3
3 4
3 5

Output:
3

Explanation: The diameter corresponds to the path 2


code:

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
#define out cout << fixed << setprecision(12)
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
int dp[N][2];
int diameter = 0;
 
void dfs(int u, int par) {
    dp[u][0] = 0; // if u is the end or start of diameter
    dp[u][1] = 0; // if u is a point in diameter ( any where )
    vi values;
    for(int v : g[u]) {
        if(v != par) {
            dfs(v, u);
            values.pb(dp[v][0]);
        }
    }
    sort(all(values));
    if(SZ(values)) {
        dp[u][0] = 1 + values.back(); 
    }
    if(SZ(values) >= 2) {
        dp[u][1] = 2 + values.back() + values[SZ(values) - 2];
    }
    diameter = max({diameter, dp[u][1], dp[u][0]});
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
    cout << diameter << '\n';
    return 0;
}

Link to this code: https://cses.fi/paste/cc520a9ab3e7abdec7a2a/