#include "bits/stdc++.h"
using namespace std;

mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

using ll = long long;

struct dsu {
public:
    dsu() : _n(0) {}
    explicit dsu(int n) : _n(n), parent_or_size(n, -1) {}

    int merge(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        int x = leader(a), y = leader(b);
        if (x == y) return x;
        if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x, y);
        parent_or_size[x] += parent_or_size[y];
        parent_or_size[y] = x;
        return x;
    }

    bool same(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        return leader(a) == leader(b);
    }

    int leader(int a) {
        assert(0 <= a && a < _n);
        if (parent_or_size[a] < 0) return a;
        return parent_or_size[a] = leader(parent_or_size[a]);
    }

    int size(int a) {
        assert(0 <= a && a < _n);
        return -parent_or_size[leader(a)];
    }

    std::vector<std::vector<int>> groups() {
        std::vector<int> leader_buf(_n), group_size(_n);
        for (int i = 0; i < _n; i++) {
            leader_buf[i] = leader(i);
            group_size[leader_buf[i]]++;
        }
        std::vector<std::vector<int>> result(_n);
        for (int i = 0; i < _n; i++) {
            result[i].reserve(group_size[i]);
        }
        for (int i = 0; i < _n; i++) {
            result[leader_buf[i]].push_back(i);
        }
        result.erase(
            std::remove_if(result.begin(), result.end(),
                        [&](const std::vector<int>& v) { return v.empty(); }),
            result.end());
        return result;
    }

private:
    int _n;
    // root node: -1 * component size
    // otherwise: parent
    std::vector<int> parent_or_size;
};

ll generateDiscreteRandom(ll min, ll max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<ll> dis(min, max);
    return dis(gen);
}

double generateUniformRandom(double low, double high) {
    // Create a random device to seed the generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(low, high);
    return dis(gen);
}

double Sample_lowest(ll RV_cnt , double low){
    double U = generateUniformRandom(0, 1);

    return 1 - (1-low)*pow((1 - U), 1/double(RV_cnt));
}


ll hashs(ll a, ll b){
    return (ll(1e9)*a + b);
}

signed main(){

    ll n; cin>>n;
    unordered_set<ll> st;
    dsu d(n);
    double ans = 0;
    ll edge_cnt = 0;
    ll i = 0;
    double curr = 0;
    for(i = 0;  ; i++){
        if(edge_cnt == n-1) break;
        ll a = generateDiscreteRandom(0, n-1), b = generateDiscreteRandom(0, n-1);
        if(a==b) continue;
        if(a>b) swap(a, b);

        if(st.count(hashs(a, b))) continue;
        st.insert(hashs(a, b));
        curr = Sample_lowest((n*(n-1))/2 - i , curr);

        if(!d.same(a, b)){
            d.merge(a, b);
            ans += curr;
            edge_cnt++;
        }
    }

    cout<<ans<<'\n';

    cerr<<"Time:"<<1000*((double)clock())/(double)CLOCKS_PER_SEC<<"ms\n";
    return 0;
}
