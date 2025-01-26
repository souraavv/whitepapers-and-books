#include <bits/stdc++.h>
using namespace std;
 
#define hey(x) cerr << #x << " : " << x << "\n";
//#define int long long int
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
 
const int N = 1e7 + 10;
const int mod = 1e9 + 7;
const double pi = acos(-1);
 
void read(vi &a) {
    for(int &i : a) cin >> i;
}
void print(vi &a) {
    for(int i : a) cerr << i << ' ';
    cerr << "\n";
}
 
bool dp[N];
 
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n;
    cin >> n;
    vi a(n);
    for(int i = 0; i < n; ++i)
        cin >> a[i];
    //  dp[i][j] = achieve sum j using first i indexes;
    int mx = n * 1000;
    bool dp[n + 1][mx + 1];
    memset(dp, 0, sizeof(dp));
    
    dp[0][0] = 1;
    for(int i = 1; i <= n; ++i) {
        for(int j = 0; j <= mx; ++j) {
            dp[i][j] = dp[i - 1][j]; // if sum j is achievable using i - 1
            if(j - a[i - 1] >= 0) {
                dp[i][j] = dp[i][j] or dp[i - 1][j - a[i - 1]];
            }
        }
    }
    vi ans;
    for(int i = 1; i <= mx; ++i) {
        if(dp[n][i]) {
            ans.pb(i);
        }
    }
    cout << SZ(ans) << '\n';
    for(int i : ans)
        cout << i << ' ';
    cout << '\n';
    return 0;
}
