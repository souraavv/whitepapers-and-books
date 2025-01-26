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
    
    string k;
    int d;
    cin >> k >> d;
    const int N = k.size();
    int dp[N + 1][d + 1][2]; // On ith index, sum, and tight or not ?
    for (int i = 0; i <= N; ++i) {
        for (int j = 0; j <= d; ++j) {
            dp[i][j][0] = dp[i][j][1] = 0;
        }
    }
    dp[N][0][0] = 1;
    dp[N][0][1] = 1;
    /*
    
    dp[i][j][tight] represents, right now I'm on ith index and rem of the sum 
    of the digit with the d is j, and tight tell whether I can exceed the current
    number present at s[i] where s is the input in string,
    
    s[n]: Nothing 
    s[n - 1]: MSB
    and
    s[0] : LSB
    
    We know answer for the s[n], why ? because there is not digit, so only sum
    we can obtain is 0, no matter what tight is.
    
    Now let's see how we can proceed with s[n - 1].
    I have two choices either I allow a open use of digits or restricted
    In case of open use I'm defining state as dp[i][j][0] and thus to obtain 
    sum_of_digit %  d as j we can have two different scenrario
    Case 1. If digit used to form sum_of_digit is greater than the digit, 
    then we simply need to look for dp(i + 1, sum_of_digit - digit, 0)
    Case 2: In case sum_of_digit < digit, In this case we need to look at the
    set of number which we can get from %d, in a ring. Consider if we have
    .Also note it can happen digit >= d(In that case it won't appear in the ring)
    Thus first we find rem = digit % d, now it is on the ring, to go to sum_of_digit,
    we can first go from rem -> 0 (that will taken d - rem steps) and then from 0
    we can move to the sum_of_digit and thus a total of d - rem + sum_of_digit steps
    so dp(i + 1, d - rem + sum_of_digit, 0);
    
    Other case when we don't want to exceed the s[i] for a given i, 
    In that case when we are having a for all digit < s[i] : we can still have a choice
    to use any digit, with open end. But exactly digit == s[i] we need to have tighter
    bound on (i + 1) also. 
    for digit > s[i] we will ignore as restrictions. 
    Again here will face same case1, case2.
    */
    for (int i = N - 1; i >= 0; --i) {
        for (int tight = 0; tight <= 1; ++tight) {
            for (int sum = 0; sum < d; ++sum) {
                if (tight) {
                    for (int digit = 0; digit <= k[i] - '0'; ++digit) {
                        if (sum >= digit) {
                            int val = (digit == k[i] - '0' 
                                                          ? dp[i + 1][sum - digit][1] % mod
                                                          : dp[i + 1][sum - digit][0] % mod);
                            dp[i][sum][1] = (dp[i][sum][1] % mod + val % mod) % mod;
                            // deb(val, sum, digit, sum - digit);
                        }
                        else {
                            int rem = digit % d;
                            int sum_prime = 0;
                            if (sum >= rem) {
                                sum_prime = sum - rem;
                            }
                            else {
                                sum_prime = (d - rem) + sum;
                            }
                            int val = (digit == k[i] - '0'
                                                ? dp[i + 1][sum_prime][1] % mod
                                                : dp[i + 1][sum_prime][0] % mod);
                            dp[i][sum][1] = (val % mod + dp[i][sum][1] % mod) % mod; 
                            // deb(val, sum, digit, sum_prime);                  
                        }
                    }
                }
                else {
                    for (int digit = 0; digit <= 9; ++digit) {
                        if (sum >= digit) {
                            dp[i][sum][0] = (mod + dp[i][sum][0] % mod + dp[i + 1][sum - digit][0] % mod) % mod; 
                        }
                        else {
                            int rem = digit % d;
                            int sum_prime = 0;
                            if (sum >= rem) {
                                sum_prime = sum - rem;
                            }
                            else {
                                sum_prime = (d - rem) + sum;
                            }
                            dp[i][sum][0] = (mod + dp[i][sum][0] % mod + dp[i + 1][sum_prime][0] % mod) % mod;   
                        }
                        
                    }
                }
            }
        }   
    }
    

    cout << (dp[0][0][1] + mod - 1) % mod << '\n';
    return 0;
}
