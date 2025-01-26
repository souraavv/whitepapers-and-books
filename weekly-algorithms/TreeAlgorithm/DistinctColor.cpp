You are given a rooted tree consisting of n nodes. The nodes are numbered 1,2,…,n, and node 1 is the root. Each node has a color.

Your task is to determine for each node the number of distinct colors in the subtree of the node.

Input

The first input line contains an integer n: the number of nodes. The nodes are numbered 1,2,…,n.

The next line consists of n integers c1,c2,…,cn: the color of each node.

Then there are n−1 lines describing the edges. Each line contains two integers a and b: there is an edge between nodes a and b.

Output

Print n integers: for each node 1,2,…,n, the number of distinct colors.

Constraints
1≤n≤2⋅105
1≤a,b≤n
1≤ci≤109
Example

Input:
5
2 3 2 2 1
1 2
1 3
3 4
3 5

Output:
3 1 2 1 1

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
 
const int N = 1e6 + 10;
const int mod = 1e9 + 7;
const double pi = acos(-1);
 
void print(vi &a) {
	for(int i : a) cerr << i << ' ';
	cerr << "\n";
}
 
vvi g;
vi col;
 
int32_t main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	int n;
	cin >> n;
	g = vvi(n + 1);
	col = vi(n + 1);
	for(int i = 1; i <= n; ++i)
		cin >> col[i];
	for(int i = 0; i + 1 < n; ++i) {
		int u, v;
		cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	vi ans(n + 1, 0);
	set<int> s;
	function<void(int, int)> dfs = [&](int u, int par) {
		set<int> t; // Temp set at each node.
		t.insert(col[u]);
		for(int v : g[u]) {
			if(v != par) {
				dfs(v, u);
				if(SZ(s) > SZ(t)) // Just to optimize the time.
					swap(t, s);
				for(int x: s)
					t.insert(x);
			}
		}
		ans[u] = t.size();
		// When I am done with all my subtree then I will update global
		// Data i.e set s. So that my parent can use this 
		s.swap(t);
	};
 
	dfs(1, 0);
	for(int i = 1; i <= n; ++i)
		cout << ans[i] << ' ';
	cout << '\n';
    
	return 0;
}
