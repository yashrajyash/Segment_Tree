#include<bits/stdc++.h>
using namespace std;

#define fast ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define ll long long

class SegTree {
private:
    vector<unordered_map<ll, ll>> tree;
    static ll n;
public:
    SegTree(ll _n) {
        n = _n;
        tree.resize(4*_n);
    }
    unordered_map<ll, ll> merge(unordered_map<ll, ll> a, unordered_map<ll, ll> b) {
        for(auto it : b) {
            a[it.first] += it.second;
        }
        return a;
    }
    void build(vector<ll> &arr, ll l = 0, ll r = n-1, ll node = 0) {
        if(l == r) {
            tree[node][arr[l]]++;
            return;
        }
        ll m = l + ((r-l) >> 1);
        build(arr, l, m, 2*node+1);
        build(arr, m+1, r, 2*node+2);
        tree[node] = merge(tree[2*node+1], tree[2*node+2]);
    }
    ll count(unordered_map<ll, ll> &mp) {
        ll res = 0;
        for(auto it : mp) {
            if(it.second > 1)
                res++;
        }
        return res;
    }
    unordered_map<ll, ll> query(ll gl, ll gr, ll l = 0, ll r = n-1, ll node = 0) {
        if(r < gl || l > gr) {
            unordered_map<ll, ll> w;
            w[-1] = 1;
            return w;
        }
        if(l >= gl && r <= gr)
            return tree[node];
        ll m = l + ((r-l) >> 1);
        auto lc = query(gl, gr, l, m, 2*node+1);
        auto rc = query(gl, gr, m+1, r, 2*node+2);
        auto res = merge(lc, rc);
        return res;
};

int main() {
    fast
    ll n;
    cin >> n;
    map<ll, vector<ll>> mp;
    SegTree sgt(n);
    vector<ll> arr(n);
    for(ll i=0; i<n; i++) {
        cin >> arr[i];
        mp[arr[i]].push_back(i);
    }
    sgt.build(arr);
    for(auto it : mp) {
        ll l = it.second[0], r = it.second[1];
        auto res = sgt.query(l, r);
        cout << count(res) << " ";
    }
    return 0;
}