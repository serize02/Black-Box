#include <bits/stdc++.h>
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,popcnt,tune=native")
#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math")
#ifdef __local_leywar
#include <debug/debugger.h>
#endif
#define int long long
#define all(x) x.begin(),x.end()
#define lb(x,v) lower_bound(all(x),v)
#define up(x,v) upper_bound(all(x),v)
#define rall(x) x.rbegin(),x.rend()
#define compress_id(x) sort(all(x)); x.erase(unique(all(x)), x.end())
#define lg(x) 31-__builtin_clz(x)
#define lowbit(x) x&(-x)
#define pb push_back
#define f first
#define s second
#define test() int t; cin >> t; for(;t;t--)
//#include <ext/pb_ds/assoc_container.hpp>


using namespace std;
//using namespace __gnu_pbds;

//typedef tree<int,null_type,less<int>,rb_tree_tag,
//    tree_order_statistics_node_update> indexed_set;

using ull = unsigned long long;
using ld = long double;
using point = complex<ld>;
const int MAX = 2e5+2;
const int INF = (1<<30);
const int mod = 1e9+7;
const ld pi = acos(-1);

struct custom_hash{
    static uint64_t splitmix64(uint64_t x){
        x+=0x9e3779b97f4a7c15,x=(x^(x>>30))*0xbf58476d1ce4e5b9,x=(x^(x>>27))*0x94d049bb133111eb;
        return x^(x>>31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM=chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x+FIXED_RANDOM);
    }
};

inline int quickpow(int a,int e){
    int aux = 1;
    while(e){
       if(e&1) aux = (aux*a)%mod;
       e >>= 1;
       a = (a*a)%mod;
    }
    return aux;
}

vector<int> tree[MAX];
vector<int> val(MAX);
map<vector<int>,int> mp;
bitset<MAX> mark;

/// dfs_hash without collision
inline void dfs(int u, int p){
    vector<int> childs;
    for(auto v: tree[u]){
        if(v == p) continue;
        dfs(v,u);
        childs.pb(val[v]);
    }
    sort(all(childs));
    if(mp.find(childs) == mp.end()) mp[childs] = mp.size();
    val[u] = mp[childs];
}

inline bool check(vector<int> &v){
    map<int,int> cnt;
    for(auto i: v) cnt[i]++;
    int odd = 0;
    for(auto i: cnt) if(i.s&1) odd++;
    return (odd <= 1);
}

int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    test(){
        int n; cin >> n;
        for(int i = 0; i < n-1; i++){
            int a, b;
            cin >> a >> b;
            tree[a].pb(b);
            tree[b].pb(a);
        }
        dfs(1,1);
        bool ans = true;
        queue<int> q;
        q.push(1);
        mark[1] = true;
        while(!q.empty()){
            int sz = (int)q.size();
            vector<int> childs;
            for(int i = 0; i < sz; i++){
                int u = q.front();
                q.pop();
                childs.pb(val[u]);
                for(auto v: tree[u]){
                    if(mark[v]) continue;
                    mark[v] = true;
                    q.push(v);
                }
            }
            ans &= check(childs);
        }
        cout << ( (ans)?"YES\n": "NO\n" );
        mark.reset();
        mp.clear();
        for(int i = 1; i <= n; i++){
            tree[i].clear();
            val[i] = 0;
        }
    }

    return 0;
}