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
 
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
 
    int n, x;
    cin >> n >> x;
    vi price(n), pages(n);
    for(int &i : price)
        cin >> i;
    for(int &i : pages)
        cin >> i;
    int dp[n + 2][x + 2];
    memset(dp, 0, sizeof(dp));
    // dp[i][j] = max no. of pages that we can achieve till index i with prices at most j;
    for(int i = 1; i <= n; ++i) {
        for(int j = 0; j <= x; ++j) {
            dp[i][j] = dp[i - 1][j];
            if(j - price[i - 1] >= 0)
                dp[i][j] = max(dp[i][j], dp[i - 1][j - price[i - 1]] + pages[i - 1]);
        }
    }
    cout << dp[n][x] << '\n';
    return 0;
}
