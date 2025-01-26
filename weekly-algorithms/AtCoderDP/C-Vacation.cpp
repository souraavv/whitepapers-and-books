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
    for(int i : a)
        cin >> i;
}
void print(vi &a) {
    for(int i : a)
        cout << i << ' ';
}

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n;
    cin >> n;
    int a[n][3], dp[n][3];
    fill(dp, 0);
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < 3; ++j) {
            cin >> a[i][j];
        }
    }

    for(int i = 0; i < 3; ++i) {
        dp[0][i] = a[0][i];
    }
    // dp[i][0] = max(dp[i - 1][1], dp[i - 2]) + a[i][0];
    for(int i = 1; i < n; ++i) {
        for(int j = 0; j < 3; ++j) {
            dp[i][j] = a[i][j] + max(dp[i - 1][(j + 1) % 3], dp[i - 1][(j + 2) % 3]);
        }
    }

    int ans = -inf;
    for(int i = 0; i < 3; ++i)
        ans = max(ans, dp[n - 1][i]);
    cout << ans << '\n';

    return 0;
}
