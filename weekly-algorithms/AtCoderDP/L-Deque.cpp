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

const int N = 3e3 + 10;
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

int cache[N + 1][N + 1][2];

int dp(int i, int j, vector<int>& a, int flag = 1) {
    if (i > j) {
        return 0;
    }
    int& ans = cache[i][j][flag];
    if (ans != -1) {
        return ans;
    }
    if (flag == 1) {
        return ans = max(a[i] + dp(i + 1, j, a, 1 - flag), a[j] + dp(i, j - 1, a, 1 - flag));
    }
    return ans = min(dp(i + 1, j, a, 1 - flag), dp(i, j - 1, a, 1 - flag));
    
}

int32_t main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }    
    memset(cache, -1, sizeof(cache));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cache[i][j][0] = cache[i][j][1] = -1;
        }
    }
    int score = dp(0, n - 1, a);
    int other = accumulate(a.begin(), a.end(), 0LL) - score;
    
    cout << score - other;
    return 0;
}
