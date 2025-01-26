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
 
const int N = 500;
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
 
void print(vi &a) {
    for(int i : a) cerr << i << ' ';
    cerr << "\n";
}
 
 
 
int32_t main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    int sum = (n * (n + 1LL)) / 2;
    if (sum & 1) {
        cout << 0 << "\n";
        return 0;
    }
    int needSum = sum / 2;
    int dp[n + 1][needSum + 1];
    memset(dp, 0, sizeof(dp));
 
    dp[0][0] = 1;
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j <= needSum; ++j) {
            dp[i][j] = (dp[i - 1][j]);
            if (j - i >= 0) {
                dp[i][j] = (dp[i][j] + dp[i - 1][j - i]) % mod;
            }
        }
    }
    cout << dp[n - 1][needSum] % mod << '\n';
    return 0;
}
 
