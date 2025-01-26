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

int dp[101][100001];
int32_t main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, W;
	cin >> n >> W;
	vi w(n), val(n);
	for(int i = 0; i < n; ++i) {
		cin >> w[i] >> val[i];
	}
	for(int i = 0; i <= 100; ++i) {
		for(int j = 0; j <= 100000; ++j) {
			dp[i][j] = inf;
		}
	}
	dp[0][0] = 0;
	dp[0][val[0]] = w[0];
	for(int i = 1; i < n; ++i) {
		dp[i][0] = 0;
		for(int j = 1; j <= 100000; ++j) {
			dp[i][j] = dp[i - 1][j];
			if(j - val[i] >= 0) {
				dp[i][j] = min(dp[i][j], dp[i - 1][j - val[i]] + w[i]);
			}
		}
	}
	for(int i = 100000; i >= 0; --i) {
		if(dp[n - 1][i] <= W) {
		cout << i << '\n';
		return 0;
		}
	}
	return 0;
}
