#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define int long long // To avoid overflows
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

const int N = 1e5 + 5;

int n, q;
int arr[N];

// Segment Trees
ll sumTree[4 * N], gcdTree[4 * N], lazy[4 * N];

// Utility function to compute GCD
ll gcd(ll a, ll b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// Build initial Segment Trees
void build(int node, int l, int r) {
    if (l == r) {
        sumTree[node] = arr[l];
        gcdTree[node] = arr[l];
        return;
    }
    int mid = (l + r) / 2;
    build(2 * node, l, mid);
    build(2 * node + 1, mid + 1, r);
    sumTree[node] = sumTree[2 * node] + sumTree[2 * node + 1];
    gcdTree[node] = gcd(gcdTree[2 * node], gcdTree[2 * node + 1]);
}

// Push lazy updates
void push(int node, int l, int r) {
    if (lazy[node]) {
        sumTree[node] += (r - l + 1) * lazy[node];
        gcdTree[node] += lazy[node];
        if (l != r) {
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
}

// Range update
void update(int node, int l, int r, int ql, int qr, int val) {
    push(node, l, r);
    if (r < ql || l > qr) return;
    if (ql <= l && r <= qr) {
        lazy[node] += val;
        push(node, l, r);
        return;
    }
    int mid = (l + r) / 2;
    update(2 * node, l, mid, ql, qr, val);
    update(2 * node + 1, mid + 1, r, ql, qr, val);
    sumTree[node] = sumTree[2 * node] + sumTree[2 * node + 1];
    gcdTree[node] = gcd(gcdTree[2 * node], gcdTree[2 * node + 1]);
}

// Query sum
ll query_sum(int node, int l, int r, int ql, int qr) {
    push(node, l, r);
    if (r < ql || l > qr) return 0;
    if (ql <= l && r <= qr) return sumTree[node];
    int mid = (l + r) / 2;
    return query_sum(2 * node, l, mid, ql, qr) + query_sum(2 * node + 1, mid + 1, r, ql, qr);
}

// Query GCD
ll query_gcd(int node, int l, int r, int ql, int qr) {
    push(node, l, r);
    if (r < ql || l > qr) return 0;
    if (ql <= l && r <= qr) return gcdTree[node];
    int mid = (l + r) / 2;
    return gcd(query_gcd(2 * node, l, mid, ql, qr), query_gcd(2 * node + 1, mid + 1, r, ql, qr));
}

signed main() {
    fastio

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> arr[i];

    build(1, 1, n);

    cin >> q;
    while (q--) {
        string type;
        cin >> type;

        if (type == "UPDATE") {
            int l, r, v;
            cin >> l >> r >> v;
            update(1, 1, n, l, r, v);
        }
        else if (type == "FIND") {
            ll answer = LLONG_MAX;
            // Try all possible splits
            for (int k = 0; k <= n; k++) {
                ll left_sum = 0, right_sum = 0;
                if (k >= 1) {
                    ll left_gcd = query_gcd(1, 1, n, 1, k);
                    left_sum = query_sum(1, 1, n, 1, k) / left_gcd;
                }
                if (k < n) {
                    ll right_gcd = query_gcd(1, 1, n, k + 1, n);
                    right_sum = query_sum(1, 1, n, k + 1, n) / right_gcd;
                }
                answer = min(answer, left_sum + right_sum);
            }
            cout << answer << '\n';
        }
    }

    return 0;
}

