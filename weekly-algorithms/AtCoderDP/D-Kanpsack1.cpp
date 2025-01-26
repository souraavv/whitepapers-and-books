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
#define fill(v, val) memset((v), val, sizeof(v))
#define PI 3.1415926535897932384626
#define out cout << fixed << setprecision(12)
#define fast ios::sync_with_stdio(false); cin.tie(0);
#define hey2(x, y) cerr << #x << " : " << x << "," << #y << " : " << y << '\n';

const int N = 1e6 + 10;
const int mod = 1e9 + 7;
const double pi = acos(-1);

void read(vi &a) {
    for(int &i : a)
        cin >> i;
}
void print(vi &a) {
    for(int i : a)
        cerr << i << ' ';
    cerr << '\n';
}

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n, w;
    cin >> n >> w;
    int dp[n + 1][w + 1];
    vi W(n + 1), val(n + 1);
    for(int i = 1; i <= n; ++i)
        cin >> W[i] >> val[i];
    fill(dp, -1e9);
    for(int item = 0; item <= n; ++item) {
        dp[item][0] = 0;
    }
    for(int weight = 1; weight <= w; ++weight) { 
        for(int item = 1; item <= n; ++item) {
            dp[item][weight] = dp[item - 1][weight];
            if(weight - W[item] >= 0) {
                dp[item][weight] = max(dp[item - 1][weight - W[item]] + val[item], dp[item][weight]);
            }
        }
    }
    cout << dp[n][w];
    return 0;
}
