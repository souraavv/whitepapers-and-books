You are given a rooted tree consisting of n nodes. The nodes are numbered 1,2,…,n, and node 1 is the root. Each node has a value.

Your task is to process following types of queries:
change the value of node s to x
calculate the sum of values in the subtree of node s
Input

The first input line contains two integers n and q: the number of nodes and queries. The nodes are numbered 1,2,…,n.

The next line has n integers v1,v2,…,vn: the value of each node.

Then there are n−1 lines describing the edges. Each line contans two integers a and b: there is an edge between nodes a and b.

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
2 3
1 5 3
2 3

Output:
8
10

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
#define fill(v, val) memset((v), val, sizeof(v))
#define fast ios::sync_with_stdio(false); cin.tie(0);
#define hey2(x, y) cerr << #x << " : " << x << "," << #y << " : " << y << '\n';
 
const int N = 1e6 + 10;
const int mod = 1e9 + 7;
const double pi = acos(-1);
 
int val[N];
vvi g;
vi store;
 
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
        data[idx] = value; // also look at this whether complete new value of old + new value;
 
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
 
 
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    // Warning 0 :If need to add to prev value then seg[p += n] += val; 
    // Warning 1 : [l, r) + 1 based value of l, r : 
    // Warning 2 : ask (l, r + 1) 0 index is not used to ask query : [1, r); 
    // Warning 3 : initial operation and ret in query accordingly;
    // Warning 4 : check in update whether need to add in previous value or new value
    
    // create segment tree instance
 
    int n, q;
    cin >> n >> q;
    for(int i = 1; i <= n; ++i) {
        cin >> val[i];
    }
    g = vvi(n + 1);
    for(int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].pb(v), g[v].pb(u);
    }
    int Timer = -1;
    vi in(n + 1, 0), out(n + 1, 0);
    function<void(int, int) > dfs = [&](int u, int par) {
        in[u] = ++Timer;
        store.pb(val[u]);
        for(int v : g[u]) {
            if(v != par) {
                dfs(v, u);
            }
        }
        out[u] = Timer;
    };
 
    dfs(1, 0);
    SegmentTree st(store);
 
    while(q--) {
        int type;
        cin >> type;
        if(type == 1) {
            int s, x;
            cin >> s >> x; 
            st.update(in[s] , x);
        }
        else {
            int s;
            cin >> s;
            cout << st.query(in[s], out[s] + 1) << "\n";
        }
    }
    return 0;
}
