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
 
void print(vi &a, int start = 0) {
    int n = a.size();
    for(int i = start; i < n; ++i) cerr << a[i] << ' ';
    cerr << "\n";
}
 
void print2D(vvi& a) {
    int n = a.size();
    for (int i = 0; i < n; ++i) print(a[i]);
}
 
 
int32_t main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int n, maxW;
    cin >> n >> maxW;
    vector<int> weight(n);
    for (int i = 0; i < n; ++i) {
        cin >> weight[i];
    }
    int mx = (1 << n) - 1;
    vector<pair<int, int> > dp(mx + 1, {inf, -inf});
    for (int i = 1; i <= mx; ++i) {
        dp[i] = {inf, -inf};
    }
    int i = 0;
    dp[0] = {0, maxW};
    
    for (int curBitSet = 0; curBitSet <= mx; ++curBitSet) {
        for (int i = n - 1; i >= 0; --i) {
            if (((1LL << i) & curBitSet) == 0) {
            
                int newBitSet = curBitSet | (1LL << i);
                int curW = weight[i];
                pair<int, int> info = dp[curBitSet];
                int turn = info.first;
                int remW = info.second;
                if (curW > remW) {
                    turn++;
                    remW = maxW - curW;    
                }
                else {
                    remW -= curW;
                }
                pair<int, int> infoNew = dp[newBitSet];
                int alreadyTurn = infoNew.first;
                int alreadyWeight = infoNew.second;
                // deb(alreadyTurn, turn);
                if (alreadyTurn > turn) {
                    dp[newBitSet] = {turn, remW};
                }
                else if (alreadyTurn == turn) {
                    if (alreadyWeight < remW) {
                        dp[newBitSet] = {turn, remW};
                    }
                }
            }
        }
    }
    
    cout << dp[mx].first + 1 << '\n';
    return 0;
}
