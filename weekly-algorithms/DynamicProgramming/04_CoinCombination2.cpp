#include <bits/stdc++.h>
using namespace std;
 
#define hey(x) cerr << #x << " is " << x << endl;
//#define int long long int
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
 
int dp[101][N];
 
int add(int a, int b) {
    a += b;
    if(a >= mod)
        return a - mod;
    return a;
}
 
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
 
    int n, x;
    cin >> n >> x;
    vi a(n);
    for(int i = 0; i < n; ++i)
        cin >> a[i];
 
    for(int i = 0; i <= n; ++i) 
        dp[i + 1][0] = 1;
 
    for(int i = 0; i < n; ++i) {
        for(int j = 1; j <= x; ++j) {
            if(j - a[i] < 0)
                dp[i + 1][j] = add(dp[i + 1][j], dp[i][j]);
            else
                dp[i + 1][j] = add(dp[i + 1][j], add(dp[i][j], dp[i + 1][j - a[i]]));
        }
    }
    cout << dp[n][x] << '\n';
    return 0;
}
