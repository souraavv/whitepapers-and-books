
#include <bits/stdc++.h>
using namespace std;

#define hey(x) cerr << "[" #x << " : " << x << "]\n";
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
#define bpc(x) __builtin_popcountll(x)
#define Cout cout << fixed << setprecision(12)
#define fill(v, val) memset((v), val, sizeof(v))
#define fast ios::sync_with_stdio(false); cin.tie(0);
#define hey2(x, y) cerr << "[" << #x << " : " << x << "], [" << #y << " : " << y << "]\n";

const int N = 1e6 + 10;
const int mod = 1e9 + 7;
const double pi = acos(-1);

void print(vi &a, int start = 0) {
    cerr << "Print\n[";
    for(int i = start; i < SZ(a); ++i) {
        cerr << a[i] << " ]"[i == SZ(a) - 1];
    }
    cerr << "\n";
}

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vvi g(n + 1);
    vi deg(n + 1, 0);
    for(int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].pb(v);
        deg[v]++;
    }

    vector<int> dp(n + 1, 0);
    vector<int> vis(n + 1, 0);
    queue<int> q;
    for(int i = 1; i <= n; ++i) {
        if(deg[i] == 0) {
            q.push(i);
        }
    }
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for(int v: g[u]) {
            deg[v]--;
            dp[v] = max(dp[v], 1 + dp[u]);
            if(deg[v] == 0) {
                q.push(v);
            }
        }
    }
    cout << *max_element(all(dp)) << '\n';
    return 0;
}

