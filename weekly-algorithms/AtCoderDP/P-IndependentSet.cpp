#include <bits/stdc++.h>
using namespace std;

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
#define inf 1e16
#define F first
#define S second
#define bpc(x) __builtin_popcountll(x)
#define Cout cout << fixed << setprecision(12)
#define fast ios::sync_with_stdio(false); cin.tie(0);

const int mod = 1e9 + 7;
const double pi = acos(-1);

#define deb(...) logger(#__VA_ARGS__, __VA_ARGS__)
template<typename ...Args>
void logger(string vars, Args&&... values) {
    cout << "[";
    cout << vars << "] = [";
    string delim = "";
    (..., (cout << delim << values, delim = ", "));
    cout << "]\n";
}

void print(vi &a, int start = 0) {
    int n = a.size();
    for(int i = start; i < n; ++i) cerr << a[i] << ' ';
    cerr << "\n";
}

void print2D(vvi& a) {
    int n = a.size();
    for (int i = 0; i < n; ++i) print(a[i]);
}

int add(int a, int b) {
    a += b;
    if (a >= mod) {
        a -= mod;
    }
    return a;
}

int mult(int a, int b) {
    a %= mod;
    b %= mod;
    return (a * b) % mod;
}
void dfs(vector<vector<int> >& g, vector<vector<int> >& ways, int u, int par = -1) {
    ways[u][0] = ways[u][1] = 1;
    for (int child: g[u]) {
        if (child != par) {
            dfs(g, ways, child, u);
            ways[u][1] = mult(ways[u][1], add(ways[child][0], ways[child][1]));
            ways[u][0] = mult(ways[u][0], ways[child][1]);
        }
    }
}

int32_t main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    const int mxN = 1e5 + 10;
    int N;
    cin >> N;
    vector<vector<int> > g(mxN + 1);
    for (int i = 0; i + 1 < N; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    // defines number of ways we can color a given tree root at i, if we fill 0 -> black or 1-> white
    // such that no adjacent have black color 
    // Ans is simple for the leaf nodes
    
    vector<vector<int> > ways(mxN + 1, vector<int>(2, 0));
    vector<bool> vis(mxN + 1, false);
    dfs(g, ways, 0);
    int totalWays = 0;
    totalWays = add(ways[0][0], ways[0][1]);
    cout << totalWays << '\n';

    return 0;
}
