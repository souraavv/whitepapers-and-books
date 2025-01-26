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

	string s, d;
	cin >> s >> d;
	int n = SZ(s);
	int m = SZ(d);
	int dp[n + 1][m + 1];
	for(int i = 0; i <= n; ++i) {
		for(int j = 0; j <= m; ++j) {
			dp[i][j] = 0;
		}
	}
	string ans = "";
	for(int i = n - 1; i >= 0; --i) {
		for(int j = m - 1; j >= 0; --j) {
			if(s[i] == d[j]) {
				dp[i][j] = 1 + dp[i + 1][j + 1];
			}
			else {
				dp[i][j] = max({dp[i + 1][j], dp[i][j + 1]});
			}
		}
	}
	int i = 0, j = 0;
	while(i < n && j < m) {
		if(dp[i][j] == dp[i + 1][j]) {
			i++;
		}
		else if(dp[i][j] == dp[i][j + 1]) {
			j++;
		}
		else if(dp[i][j] == 1 + dp[i + 1][j + 1]) {
			ans += s[i];
			i++, j++;
		} 
	}
	cout << ans;
	return 0;
}
