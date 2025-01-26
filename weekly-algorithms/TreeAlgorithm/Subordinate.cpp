Given the structure of a company, your task is to calculate for each employee the number of their subordinates.

Input

The first input line has an integer n: the number of employees. The employees are numbered 1,2,.,n, and employee 1 is the general director of the company.

After this, there are n-1 integers: for each employee 2,3,.,n their direct boss in the company.

Output

Print n integers: for each employee 1,2,.,n the number of their subordinates.

Constraints
1髇�2�105
Example

Input:
5
1 1 2 3

Output:
4 1 1 0 0

Solution : 
Code
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
#define PI 3.1415926535897932384626
#define out cout << fixed << setprecision(12)
#define fill(v, val) memset((v), val, sizeof(v))
#define fast ios::sync_with_stdio(false); cin.tie(0);
#define hey2(x, y) cerr << #x << " : " << x << "," << #y << " : " << y << '\n';
 
const int N = 1e6 + 10;
const int mod = 1e9 + 7;
const double pi = acos(-1);
 
void print(vi &a) {
    for(int i : a) cerr << i << ' ';
    cerr << "\n";
}
 
vvi g;
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n;
    cin >> n;
    g = vvi(n + 1);
    for(int i = 2; i <= n; ++i) {
        int val;
        cin >> val;
        g[val].pb(i), g[i].pb(val);
    }
    vi dp(n + 1, 0);
    function<void(int, int) > dfs = [&](int u, int par) {
        for(int v : g[u]) if(v != par) {
            dfs(v, u);
            dp[u] += dp[v] + 1;
        }
    };
    dfs(1, 0);
    for(int i = 1; i <= n; ++i) {
        cout << dp[i] << ' '; 
    }
    cout << '\n';
    
    return 0;
}

Link : https://cses.fi/paste/15aa4451f5bb4c17c7935/