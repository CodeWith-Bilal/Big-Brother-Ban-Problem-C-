#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

// Custom gcd for C++11 or earlier
ll gcd(ll a, ll b) {
    while (b) {
        ll t = a % b;
        a = b;
        b = t;
    }
    return a;
}

// Segment Tree for Range Add and Point Query
struct SegmentTree {
    int n;
    vector<ll> tree;

    SegmentTree(int size) {
        n = size;
        tree.assign(4 * n, 0);
    }

    void update(int node, int l, int r, int ul, int ur, ll val) {
        if (ul > r || ur < l) return;
        if (ul <= l && r <= ur) {
            tree[node] += val;
            return;
        }
        int mid = (l + r) / 2;
        update(2 * node, l, mid, ul, ur, val);
        update(2 * node + 1, mid + 1, r, ul, ur, val);
    }

    ll query(int node, int l, int r, int idx) {
        if (l == r) return tree[node];
        int mid = (l + r) / 2;
        if (idx <= mid) return tree[node] + query(2 * node, l, mid, idx);
        else return tree[node] + query(2 * node + 1, mid + 1, r, idx);
    }

    void rangeAdd(int l, int r, ll val) {
        update(1, 0, n - 1, l, r, val);
    }

    ll pointQuery(int idx) {
        return query(1, 0, n - 1, idx);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;
    vector<ll> base(N);
    for (int i = 0; i < N; ++i) {
        cin >> base[i];
    }

    SegmentTree seg(N);

    int Q;
    cin >> Q;
    while (Q--) {
        string type;
        cin >> type;
        if (type == "UPDATE") {
            int L, R;
            ll V;
            cin >> L >> R >> V;
            seg.rangeAdd(L - 1, R - 1, V);
        } else if (type == "FIND") {
            vector<ll> a(N);
            for (int i = 0; i < N; ++i) {
                a[i] = base[i] + seg.pointQuery(i);
            }

            ll answer = 1e18;
            for (int k = 1; k < N; ++k) {
                ll x1 = a[0];
                for (int i = 1; i < k; ++i) {
                    x1 = gcd(x1, a[i]);
                }
                ll x2 = a[k];
                for (int i = k + 1; i < N; ++i) {
                    x2 = gcd(x2, a[i]);
                }
                ll sum = 0;
                for (int i = 0; i < k; ++i) sum += a[i] / x1;
                for (int i = k; i < N; ++i) sum += a[i] / x2;
                answer = min(answer, sum);
            }

            cout << answer << '\n';
        }
    }

    return 0;
}

