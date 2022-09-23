#include<bits/stdc++.h>
using namespace std;

#define fast ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define ll long long

class SegTree {
private:
    vector<pair<ll, ll>> tree;
    vector<ll> arr;
    ll n;
public:
    SegTree(ll _n) {
        n = _n;
        arr.resize(n, 0);
        tree.resize(4*_n, {INT_MAX, 1});
    }
    pair<ll, ll> compute(pair<ll, ll> a, pair<ll, ll> b) {
        if(a.first == b.first)
            return {a.first, a.second + b.second};
        else if(a.first < b.first)
            return a;
        return b;
    }
    void update(ll l, ll r, ll node, ll &idx, ll &val) {
        if(l == r) {
            tree[node] = {val, 1};
            arr[idx] = val;
            return;
        }
        ll m = l + ((r-l) >> 1);
        if(idx <= m)
            update(l, m, 2*node+1, idx, val);
        else
            update(m+1, r, 2*node+2, idx, val);
        tree[node] = compute(tree[2*node+1], tree[2*node+2]);
    }
    pair<ll, ll> query(ll l, ll r, ll node, ll &gl, ll &gr) {
        if(r < gl || l > gr)
            return {INT_MAX, 1};
        if(l >= gl && r <= gr)
            return tree[node];
        ll m = l + ((r-l) >> 1);
        auto x = query(l, m, 2*node+1, gl, gr);
        auto y = query(m+1, r, 2*node+2, gl, gr);
        return compute(x, y);
    }
};

int main() {
    fast
    ll n, m;
    cin >> n >> m;
    SegTree segTree(n);
    for(ll i=0; i<n; i++) {
        ll val;
        cin >> val;
        segTree.update(0, n-1, 0, i, val);
    }
    while(m--) {
        ll type;
        cin >> type;
        switch(type) {
            case 1:
                ll i, v;
                cin >> i >> v;
                segTree.update(0, n-1, 0, i, v);
                break;
            case 2:
                ll l, r;
                cin >> l >> r;
                r--;
                auto res = segTree.query(0, n-1, 0, l, r);
                cout << res.first << " " << res.second << "\n";
                break;
        }
    }
    return 0;
}