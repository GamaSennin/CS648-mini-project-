#include "bits/stdc++.h"
using namespace std;

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

double generateUniformRandom(double low, double high) {
    // Create a random device to seed the generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(low, high);
    return dis(gen);
}


double simulate(int n){
    random_device rd;  
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0, 1);
    dsu d(n);
    vector<pair<double, pair<int, int>>> edges;
    for(int i = 0; i<n; i++){
        for(int j = i+1; j<n; j++){
            edges.push_back({generateUniformRandom(0, 1), {i, j}});
        }
    }
    sort(edges.begin(), edges.end());
    double ans = 0;
    for(auto &[w, p]: edges){
        auto &[u, v] = p;
        if(d.same(u, v)) continue;
        d.merge(u, v);
        ans += w;
    }
    return ans;
}


signed main(){

    int n; 
    cin>>n;
    cout<<simulate(n)<<'\n';

    cerr<<"Time:"<<1000*((double)clock())/(double)CLOCKS_PER_SEC<<"ms\n";

    return 0;
}
