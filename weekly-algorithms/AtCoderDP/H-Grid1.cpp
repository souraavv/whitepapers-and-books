
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
	int a[n + 1][m + 1];
	int dp[n + 1][m + 1];
	memset(dp, 0, sizeof(dp));
	for(int row = 0; row < n; ++row) {
		for(int col = 0; col < m; ++col) {
			char c;
			cin >> c;
			a[row][col] = (c == '.' ? 1 : 0);
		}
	}
	dp[0][0] = a[0][0];
	for(int col = 1; col < m; ++col) {
		dp[0][col] = (a[0][col] ? dp[0][col - 1] : 0);
	}
	for(int row = 1; row < n; ++row) {
	 	dp[row][0] = (a[row][0] ? dp[row - 1][0] : 0);
	}
	for(int row = 1; row < n; ++row) {
		for(int col = 1; col < m; ++col) {
			dp[row][col] = (a[row][col] ? (dp[row - 1][col] + dp[row][col - 1]) % mod : 0);
		}
	}
	cout << dp[n - 1][m - 1] << '\n';
	return 0;
}
