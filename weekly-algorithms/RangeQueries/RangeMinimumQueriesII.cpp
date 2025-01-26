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
 
const int N = 2e5 + 10;
const int mod = 1e9 + 7;
const double pi = acos(-1);
 
void read(vi &a) {
    for(int &i : a) cin >> i;
}
void print(vi &a) {
    for(int i : a) cerr << i << ' ';
    cerr << "\n";
}
 
int seg[2 * N];
int n;
 
int opr(int a, int b) {
    return min(a, b);
}
void build() {
    for(int i = n - 1; i > 0; --i)
        seg[i] = opr(seg[2 * i], seg[2 * i + 1]);
}
 
void update(int idx, int val) {
    for(seg[idx += n] = val; idx > 1; idx >>= 1) {
        seg[idx >> 1] = opr(seg[idx], seg[idx ^ 1]);
    }
}
int query(int l, int r) {
    int ans = inf;
    for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if(l & 1)
            ans = opr(ans, seg[l++]);
        if(r & 1)
            ans = opr(ans, seg[--r]);
    }
    return ans;
}
 
int32_t main() {
    fast;
    int q;
    cin >> n >> q;
    memset(seg, 1e9, sizeof(seg));
    for(int i = 0; i < n; ++i) {
        cin >> seg[i + n];
    }
    build();
    while(q--) {
        int type;
        cin >> type;
        if(type == 1) {
            int idx, val;
            cin >> idx >> val;
            update(idx - 1, val);
            continue;
        }
        int l, r;
        cin >> l >> r;
        cout << query(l - 1, r) << "\n";
    }
 
}
