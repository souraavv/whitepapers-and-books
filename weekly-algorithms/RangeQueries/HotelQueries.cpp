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
 
void read(vi &a) {
    for(int &i : a) cin >> i;
}
void print(vi &a) {
    for(int i : a) cerr << i << ' ';
    cerr << "\n";
}
 
vi room, need;
 
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
        return max(a, b) ; // set this accordingly
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
        int ret = -inf; // Initialize accoring to the range operation
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
 
 
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    // Warning 0 :If need to add to prev value then seg[p += n] += val; 
    // Warning 1 : [l, r) + 1 based value of l, r : 
    // Warning 2 : ask (l, r + 1) 0 index is not used to ask query : [1, r); 
    // Warning 3 : initial opration and ret in query accordingly;
    // Warning 4 : check in update whether need to add in previous value or new value
    
    // create segment tree instance
 
    int n, m;
    cin >> n >> m;
    room = vi(n, 0);
    need = vi(m, 0);
    for(int i = 0; i < n; ++i) {
        cin >> room[i];
    }
    for(int i = 0; i < m; ++i) {
        cin >> need[i];
    }
    SegmentTree st(room);
 
    for(int i = 0; i < m; ++i) {
        int val = need[i];
        int l = 0, r = n;
        int idx = -1;
        while(l < r) {
            int mid = (l + r) / 2;
            if(st.query(l, mid + 1) >= val) {
                r = mid;
                idx = mid;
            }
            else {
                l = mid + 1;
            }
        }
        if(idx == -1) {
            cout << "0 ";
        }
        else {
            cout << idx  + 1 << ' ';
            st.update(idx, room[idx] - val);
            room[idx] -= val;
        }
 
        // for(int i = 0; i < n; ++i) {
        //     cerr << st.query(i, i + 1) << ", ";
        // }
        // cerr << "\n";
    }
 
 
    return 0;
}
