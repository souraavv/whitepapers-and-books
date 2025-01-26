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

const int N = 302;
double cache[N][N][N];

double dp(int i, int j, int k, int N) {
    if (i < 0 || j < 0 || k < 0) {
        return 0;
    }
    if (i == 0 && j == 0 && k == 0) {
        return 0;
    }
    double& ans = cache[i][j][k];
    if (ans > 0.0) {
        return ans;
    }
    int rem = i + j + k;
    ans = N + (dp(i - 1, j + 1, k, N) * i 
            + dp(i, j - 1, k + 1, N) * j 
            + dp(i, j, k - 1, N) * k);
    ans = ans / (double)(rem);
    return ans;
}

int32_t main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> ar(4, 0);
   /*
  	* We first defined our state of game, we have ar[0] number of empty Dish
      and ar[1], ar[2] and ar[3] similarly have 1, 2 and 3 sushi, for us it order
      doesn't matter, only count matter.
      
    * Let's see how to solve, Our dp(i, j, k) defined 
    	: Number of Dish with 3 sushi i.e i
        : Number of Dish with 2 sushi i.e j
  		: Number of Dish with 1 sushi i.e k
        : Number of Dish with 0 sushi i.e N - i - j - k, where N is known to us, that
          why it is not important to keep an additional state
    * How to think for transitions ? 
        : dp(i, j, k) = dp(i - 1, j + 1, k) with prob (i / N)
                       + dp(i, j - 1, k + 1) with prob (j / N)
                       + dp(i, j, k - 1) with prob (k / N)
                       or no sushie has eaten ? 
                       + dp(i, j, k) with prob (N - (i + j + k)) / N
        : Solving this bring dp(i, j, k) with prob (N - (i + j + k)) / N
          to Lhs, 
          dp(i, j, k) = (N / (i + j + k)) (1 + dp(i - 1, j + 1, k) * i / N
          									 + dp(i, j - 1, k + 1) * j / N
                                             + dp(i, j, k - 1) * k / N)
                                             
                         (N + dp(i - 1, j + 1, k) * i + dp(i, j - 1, k + 1) * j + ..)
        dp(i, j, k)    =   ----------------------------------------------------------
                                              ( i + j + k)
                                          
        : Add 1 because we have taken a step to reach these states
        : We know base cases. simple rt? 
        : You know where our answer is ? We want to eat every sushie.
        : Rem the mod.
  
   */
  
    for (int i = 0; i < n; ++i) {
          int val;
          cin >> val;
          ar[val]++;
    }
  
    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                cache[i][j][k] = -1.0;
            }
        }
    }
    Cout << dp(ar[3], ar[2], ar[1], n);
    return 0;
}
