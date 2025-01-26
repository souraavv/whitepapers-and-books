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
 
const int N = 1e6 + 10;
const int mod = 1e9 + 7;
const double pi = acos(-1);
 
void read(vi &a) {
    for(int &i : a) cin >> i;
}
void print(vi &a) {
    for(int i : a) if (i != 0)cerr << i << ' ';
    cerr << "\n";
}
 
 
#define deb(...) logger(#__VA_ARGS__, __VA_ARGS__)
template<typename ...Args>
void logger(string vars, Args&&... values) {
    cout << "[";
    cout << vars << "] = [";
    string delim = "";
    (..., (cout << delim << values, delim = ", "));
    cout << "]\n";
}
 
int32_t main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<vector<int> > dp(n, vector<int> (m + 2, 0));
    
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (a[i] == 0) {
                if (i - 1 >= 0) {
                    if (a[i - 1] == 0) {
                        dp[i][j] = (dp[i - 1][j] % mod);
                        if (j + 1 <= m)
                            dp[i][j] = (dp[i][j] + dp[i - 1][j + 1]) % mod;
                        if (j - 1 >= 1) 
                            dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % mod;
                    }
                    else {
                        if (abs(a[i - 1] - j) <= 1) {
                            dp[i][j] = (dp[i - 1][a[i - 1]]) % mod;
                        }
                    }
                }
                else {
                    dp[i][j] = 1;
                }
            }
            else {
                if (i - 1 >= 0) {
                    if (a[i - 1] > 0) {
                        if (abs(a[i] - a[i - 1]) > 1) {
                            cout << "0\n";
                            return 0;
                        }
                        dp[i][a[i]] = dp[i - 1][a[i - 1]] % mod;
                        // break;
                    }
                    else if (abs(a[i] - j) <= 1) {
                        dp[i][a[i]] = (dp[i][a[i]] + dp[i - 1][j]) % mod;  
                    }
                }
                else {
                    dp[i][a[i]] = 1;
                    // break;
                }
            }
        }
    }
    int ans = 0;
    for (int j = 1; j <= m; ++j) {
        ans = (ans + dp[n - 1][j]) % mod;
    }
    cout << ans << '\n';
    
    return 0;
}

// Link to this code: https://cses.fi/paste/8966b5dd731d7f592e7c1e/
