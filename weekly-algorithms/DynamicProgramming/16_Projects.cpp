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
#define inf 1e16
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
    int n;
    cin >> n;
    vector<int> startTime(n), endTime(n), profit(n);
    for (int i = 0; i < n; ++i) {
        cin >> startTime[i] >> endTime[i] >> profit[i];
    }
    vector<array<int,3> > a;
    for (int i = 0; i < n; ++i) {
        a.push_back({startTime[i], endTime[i], profit[i]});
    }
    sort (a.begin(), a.end(), [&](array<int, 3>& p1, array<int, 3>& p2){
        return p1[0] < p2[0] || p1[0] == p2[0] && p1[1] < p2[1];
    });
    
    int dp[n + 1];
    memset(dp, 0, sizeof(dp));
    dp[n - 1] = a[n - 1][2];
    for (int i = n - 2; i >= 0; --i) {
        int endPoint = a[i][1];
        array<int, 3> temp = {endPoint + 1, 0, 0};
        auto it = lower_bound(a.begin() + i + 1, a.end(), temp) - a.begin();
        dp[i] = max(dp[i + 1], a[i][2] + dp[it]);
    }
    cout << dp[0] << '\n';
    return 0;
}
 
