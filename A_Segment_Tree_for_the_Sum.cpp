#include<bits/stdc++.h>
using namespace std;

#define fast ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define ll long long

class SegTree {
private:
    vector<ll> tree;
    vector<ll> arr;
    ll n;
public:
    SegTree(ll _n) {
        n = _n;
        arr.resize(n, 0);
        tree.resize(4*_n, 0);
    }
    void update(ll l, ll r, ll node, ll &idx, ll &val) {
        if(l == r) {
            tree[node] = val;
            arr[idx] = val;
            return;
        }
        ll m = l + ((r-l) >> 1);
        if(idx <= m)
            update(l, m, 2*node+1, idx, val);
        else
            update(m+1, r, 2*node+2, idx, val);
        tree[node] = tree[2*node+1] + tree[2*node+2];
    }
    ll query(ll l, ll r, ll node, ll &gl, ll &gr) {
        if(r < gl || l > gr)
            return 0;
        if(l >= gl && r <= gr)
            return tree[node];
        ll m = l + ((r-l) >> 1);
        return query(l, m, 2*node+1, gl, gr) + query(m+1, r, 2*node+2, gl, gr);
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
                cout << segTree.query(0, n-1, 0, l, r) << "\n";
                break;
        }
    }
    return 0;
}