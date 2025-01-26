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
 
const int N = 1e6 + 10;
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
    int q;
    cin >> q;
    const int n = 1e6 + 10;
    int dp[n + 1][2];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    dp[0][1] = 1;
    // 0 batata hain split, 1 batata hain no split.
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < 2; ++j) {
            dp[i][0] = ((4 * dp[i - 1][0]) % mod + dp[i - 1][1] % mod) % mod;
            dp[i][1] = (dp[i - 1][1] % mod + dp[i - 1][1] % mod + dp[i - 1][0] % mod) % mod;
        }
    }
    
    while (q--) {
        int n;
        cin >> n;
        cout << (dp[n - 1][0] + dp[n - 1][1]) % mod << "\n";
    }
    return 0;
}
