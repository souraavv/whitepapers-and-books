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
    
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    vector<int> dp(k + 1, 0);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        dp[a[i]] = 1;
    }
    sort(a.begin(), a.end());
    for (int i = 0; i <= k; ++i) {
        bool flag = false;
        for (int j = 0; j < a.size(); ++j) {
            if (i - a[j] < 0) {
                break;
            }
            else {
                flag = flag or dp[i - a[j]];
            }
        }
        dp[i] = not(flag);
    }    
    cout << (dp[k] == 0 ? "First" : "Second") << '\n';
    return 0;
}
