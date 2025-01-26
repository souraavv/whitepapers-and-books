You are given a rooted tree consisting of n nodes. The nodes are numbered 1,2,…,n, and node 1 is the root. Each node has a value.

Your task is to process following types of queries:
change the value of node s to x
calculate the sum of values on the path from the root to node s
Input

The first input line contains two integers n and q: the number of nodes and queries. The nodes are numbered 1,2,…,n.

The next line has n integers v1,v2,…,vn: the value of each node.

Then there are n−1 lines describing the edges. Each line contains two integers a and b: there is an edge between nodes a and b.

Finally, there are q lines describing the queries. Each query is either of the form "1 s x" or "2 s".

Output

Print the answer to each query of type 2.

Constraints
1≤n,q≤2⋅105
1≤a,b,s≤n
1≤vi,x≤109
Example

Input:
5 3
4 2 5 2 1
1 2
1 3
3 4
3 5
2 4
1 3 2
2 4

Output:
11
8

Solution:


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
#define Cout cout << fixed << setprecision(12)
#define fill(v, val) memset((v), val, sizeof(v))
#define fast ios::sync_with_stdio(false); cin.tie(0);
#define hey2(x, y) cerr << #x << " : " << x << "," << #y << " : " << y << '\n';
 
const int N = 2e5 + 10;
const int mod = 1e9 + 7;
const double pi = acos(-1);
 
void print(vi &a) {
    for(int i : a) cerr << i << ' ';
    cerr << "\n";
}
 
class SegmentTree {
public:
    SegmentTree(int count) {
        n = count;
        data = std::vector<int>(2 * n, 0);
    }
 
    SegmentTree(std::vector<int> const &values) {
        n = values.size();
        data = std::vector<int>(2 * n);
        std::copy(values.begin(), values.end(), &data[0] + n);
        for (int idx = n - 1; idx > 0; idx--)
            data[idx] = opr(data[idx * 2], data[idx * 2 + 1]);
    }
 
    int opr(int a, int b) {
        return a + b; // set this accordingly
    }
    void update(int idx, int value) {
        idx += n;
        data[idx] += value; // also look at this whether complete new value of old + new value;
 
        while (idx > 1) {
            idx /= 2;
            data[idx] = opr(data[2 * idx], data[2 * idx + 1]);
        }
    }
 
    int query(int left, int right) { // interval [left, right)
        int ret = 0; // Initialize accoring to the range operation
        left += n;
        right += n;
 
        while (left < right) {
            if (left & 1) ret = opr(ret, data[left++]);
            if (right & 1) ret = opr(ret, data[--right]);
            left >>= 1;
            right >>= 1;
        }
        return ret;
    }
 
private:
    int n;
    std::vector<int> data;
};
 
int val[N];
vvi g;
vi dp;
int tin[N], tout[N];
int Timer = -1;
 
void dfs(int u, int par) {
    if(par != -1)
        dp[u] = val[u] + dp[par];
    else
        dp[u] = val[u];
    tin[u] = ++Timer;
    for(int v: g[u]) {
        if(v != par)    
            dfs(v, u);
    }
    tout[u] = Timer;
}
 
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
 
    memset(tin, 0, sizeof(tin));
    memset(tout, 0, sizeof(tout));
 
    for(int i = 0; i < n; ++i) {
        cin >> val[i];
    }
    g = vvi(n + 1);
    for(int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].pb(v);
        g[v].pb(u);
    }
    dp = vi(n, 0);
    dfs(0, -1);
    
    SegmentTree st(tout[0] + 2);
    while(q--) {
        int type;
        cin >> type;
        if(type == 1) {
            int node, x;
            cin >> node >> x;
            --node;
            int oldValue = val[node];
            int change = x - oldValue;
            val[node] = x;
            st.update(tin[node], change);
            st.update(tout[node] + 1, -1*change);
        }
        else {
            int node;
            cin >> node;
            --node;
            cout << dp[node] + st.query(0, 1 + tin[node]) << '\n';
        }
    }
    
    return 0;
}
