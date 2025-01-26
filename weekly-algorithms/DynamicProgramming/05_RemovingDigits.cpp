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
#define inf 1e12
 
const int N = 1e6 + 10;
const int mod = 1e9 + 7;
const double pi = acos(-1);
 
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
 
    int n;
    cin >> n;
    vi dp(N + 1, inf);
    dp[n] = 0;
    for(int i = n; i >= 0; --i) {
        if(dp[i] != inf){
            int val = i;
            vi temp;
            while(val){
                temp.pb(val % 10);
                val /= 10;
            }
            int sz = temp.size();
            for(int j = 0; j < sz; ++j) {
                dp[i - temp[j]] = min(dp[i - temp[j]], 1 + dp[i]);
            }
        }
    }
    cout << dp[0] << '\n';
    return 0;
}
