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
#define inf 1e9
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
    
    int a, b;
    cin >> a >> b;
    vector<vector<int> > dp(a + 1, vector<int> (b + 1, inf));
    // dp[i][j] = defines minimum number of cut require to make (0,0) to (i, j) a square
    // if i == j then it already a square else think...
 
    for (int i = 1; i <= a; ++i) {
        for (int j = 1; j <= b; ++j) {
            if (i == j) {
                dp[i][j] = 0;
            }
            else {
                for (int k = i - 1; k > 0; --k) {
                    dp[i][j] = min(dp[i][j], 1LL + dp[i - k][j] + dp[k][j]);
                }
                for (int k = j - 1; k > 0; --k) {
                    dp[i][j] = min(dp[i][j], 1LL + dp[i][j - k] + dp[i][k]);
                }
            }
        }
    }
    cout << dp[a][b] << '\n';
    return 0;
}
