#include <bits/stdc++.h>
using namespace std;
 
#define hey(x) cerr << "[ "<< #x << " : " << x << " ]\n";
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
#define Cout cout << fixed << setprecision(12)
#define fill(v, val) memset((v), val, sizeof(v))
#define fast ios::sync_with_stdio(false); cin.tie(0);
#define hey2(x, y) cerr << "[ "<< #x << " : " << x << " ], [" << #y << " : " << y << " ]\n";
 
const int N = 1e6 + 10;
const int mod = 1e9 + 7;
const double pi = acos(-1);
 
void print(vi &a) {
for(int i : a) cerr << i << ' ';
cerr << "\n";
}
 
class SegmentTree {
public:
    SegmentTree(int count) {
        n = count;
        data = std::vector<int>(2 * n, 0);
    }
 
    SegmentTree(std::vector<int> const &values) {
        n = values.size();
        data = std::vector<int>(2 * n);
        std::copy(values.begin(), values.end(), &data[0] + n);
        for (int idx = n - 1; idx > 0; idx--)
            data[idx] = opr(data[idx * 2], data[idx * 2 + 1]);
    }
 
    int opr(int a, int b) {
        return a + b ; // set this accordingly
    }
    void update(int idx, int value) {
        idx += n;
        data[idx] = value; // also look at this whether complete new value of old + new value;
 
        while (idx > 1) {
            idx /= 2;
            data[idx] = opr(data[2 * idx], data[2 * idx + 1]);
        }
    }
 
    int query(int left, int right) { // interval [left, right)
        int ret = 0; // Initialize accoring to the range operation
        left += n;
        right += n;
 
        while (left < right) {
            if (left & 1) ret = opr(ret, data[left++]);
            if (right & 1) ret = opr(ret, data[--right]);
            left >>= 1;
            right >>= 1;
        }
        return ret;
    }
 
private:
    int n;
    std::vector<int> data;
};
 
int32_t main(){
ios::sync_with_stdio(false);
cin.tie(0);

    int n;
    cin >> n;
    vi a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
 
    SegmentTree st(n);
    int q = n;
    while(q--) {
        int idx;
        cin >> idx;
        idx--;
        int extra = st.query(0, idx + 1);
        if(extra == 0) {
            cout << a[idx] << ' ';
            st.update(idx, 1);
        }
        else {
            int l = 0, r = n;
            int ans = r;
            while(l <= r) {
                int mid = (l + r) / 2;
                int removed = st.query(0, mid + 1);
                if(removed + idx <= mid) {
                    r = mid - 1;
                    ans = mid;
                }
                else {
                    l = mid + 1;
                }
        }
        cout << a[ans] << " ";
        st.update(ans, 1);
        }
    }
return 0;
}
