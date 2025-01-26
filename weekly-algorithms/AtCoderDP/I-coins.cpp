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

	int n;
	cin >> n;
	vector<double> p(n + 1), q(n + 1);
	for(int i = 1; i <= n; ++i) {
		cin >> p[i];
		q[i] = 1 - p[i];
	}
	double dp[n + 1][n + 1];
	for(int i = 0; i <= n; ++i) {
		for(int j = 0; j <= n; ++j) {
			dp[i][j] = 0;
		}
	}
	// dp[i][j] : till ith index we have taken j heads and i - j tails.
	// ans = summation of j = n / 2 + 1 till J < n;
	dp[0][0] = 1;
	for(int i = 0; i <= n; ++i) {
		for(int j = 0; j <= n; ++j) {
			if(i - 1 >= 0) 
				dp[i][j] += 1.0*(dp[i - 1][j] * q[i]);
			if(j - 1 >= 0) 
				dp[i][j] += 1.0*(dp[i - 1][j - 1] * p[i]);
		}
	}
	double ans = 0.0;
	for(int head = (n / 2) + 1; head <= n; ++head) {
		ans += dp[n][head];
	}
	cout << fixed << setprecision(10) << ans << '\n';
	return 0;
}
