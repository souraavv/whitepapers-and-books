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
#define inf 1e11
 
const int N = 1e6 + 10;
const int mod = 1e9 + 7;
const double pi = acos(-1);
 
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
 
    string s, d;
    cin >> s >> d;
    int n = s.size();
    int m = d.size();
 
    int dp[n + 1][m + 1];
    memset(dp, 0, sizeof(dp));
 
    for(int i = 0; i < n; ++i) {
        dp[i][m] = n - i;
    }
    for(int i = 0; i < m; ++i) {
        dp[n][i] = m - i;
    }
 
    for(int i = n - 1; i >= 0; --i) {
        for(int j = m - 1; j >= 0; --j) {
            if(s[i] == d[j]) {
                dp[i][j] = dp[i + 1][j + 1];
            }
            else{
                dp[i][j] = 1 + min({dp[i + 1][j + 1], dp[i][j + 1], dp[i + 1][j]});
            }
        }
    }
    cout << dp[0][0] << '\n';
    return 0;
}
