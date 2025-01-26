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
    
    int a[6] = {1, 2, 3, 4, 5, 6};
    int n;
    cin >> n;
    vi dp(N, 0);
    for(int i = 0; i < 6; ++i)
        dp[a[i]] = 1;
    dp[0] = 1;
    
    for(int i = 1; i <= n; ++i) {
        for(int j = 0; j < 6; ++j) {
            if(i - a[j] > 0) {
                dp[i] = add(dp[i], dp[i - a[j]]);
            }
        }
    }
    cout << dp[n] << '\n';
    return 0;
}

