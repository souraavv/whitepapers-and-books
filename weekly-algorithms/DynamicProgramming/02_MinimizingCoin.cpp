
#include <bits/stdc++.h>
using namespace std;
 
#define hey(x) cerr << #x << " is " << x << endl;
#define int long long int
#define ll long long
#define vi vector<int>
#define vvi vector<vector<int> >
#define vpi vector<pair<int, int> >
#define vvpi vector<vector<pair<int, int> > >
#define all(v) (v).begin(), (v).end()   
#define pii pair<int, int>
#define pb push_back
#define F first
#define S second
#define PI 3.1415926535897932384626
#define out cout << fixed << setprecision(12)
#define fast ios::sync_with_stdio(false); cin.tie(0);
#define inf 1e10
 
const int N = 1e6 + 10;
const int mod = 1e9 + 7;
const double pi = acos(-1);
 
int add(int a, int b) {
    a += b;
    if(a >= mod)
        return a - mod;
    return a;
}
 
int32_t main(){
    
    int n, x;
    cin >> n >> x;
    vi c(n);
    for(int i = 0; i < n; ++i) {
        cin >> c[i];
    }    
 
    vi dp(N, inf);
    dp[0] = 0;
    for(int i = 0; i < n; ++i) 
        dp[c[i]] = 1;
    for(int i = 1; i <= x; ++i) {
        int mn = inf;
        for(int j = 0; j < n; ++j) {
            if(i - c[j] > 0) {
                mn = min(mn, dp[i - c[j]]);
            }
        }
        if(mn != inf) {
            dp[i] = min(dp[i], 1 + mn);
        }
    }
    if(dp[x] == inf)
        cout << "-1\n";
    else
        cout << dp[x] << '\n';
    return 0;
}

