#include <bits/stdc++.h>
#define int long long
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define compress_id(x) sort(all(x)); x.erase(unique(all(x)), x.end())
#define lowbit(x) x&(-x)
#define pb push_back
#define f first
#define s second
#define test() int t; cin >> t; for(;t;t--)
#define sz(x) (int)x.size()
#define cyes cout << "YES\n"
#define cno cout << "NO\n"

using namespace std;

using ull = unsigned long long;
using ld = long double;
using point = complex<double>;
const int MAX = 1e6+2;
const int inf = (1e18);
const int mod = 1e9+7;
const double pi = acos(-1);

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

inline int pow_mod(int a, int n){
    int ans = 1;
    for(;n ;n >>= 1){
        if(n&1) ans = (ans*a)%mod;
        a = (a*a)%mod;
    }
    return ans;
}

int ar[MAX], bl[MAX], k[MAX], solution[MAX];

struct qr{
    int l, r, id;
    qr(int a, int b, int c){
        l = a, r = b, id = c;
    }
};
vector<qr> qry;

inline bool cmp(const qr &a, const qr &b){
    if(bl[a.l] == bl[b.l]){
        if(bl[a.l]&1) return a.r < b.r;
        return a.r > b.r;
    }
    return bl[a.l] < bl[b.l];
}

int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    int n, q;
    cin >> n >> q;
    const int sq = (int)(sqrtl(n));
    for(int i = 1; i <= n; i++){
        cin >> ar[i];
        bl[i] = i/sq;
    }
    for(int i = 0; i < q; i++){
        int a, b;
        cin >> a >> b;
        qry.emplace_back(a,b,i);
    }
    sort(all(qry),cmp);
    int lf = 1, rg = 1, ans = 0;
    k[ar[1]]++;
    ans = ar[1];
    for(auto i: qry){
        while(lf > i.l){
            lf--;
            ans -= ar[lf]*k[ar[lf]]*k[ar[lf]];
            k[ar[lf]]++;
            ans += ar[lf]*k[ar[lf]]*k[ar[lf]];
        }
        while(lf < i.l){
            ans -= ar[lf]*k[ar[lf]]*k[ar[lf]];
            k[ar[lf]]--;
            ans += ar[lf]*k[ar[lf]]*k[ar[lf]];
            lf++;
        }
        while(rg < i.r){
            rg++;
            ans -= ar[rg]*k[ar[rg]]*k[ar[rg]];
            k[ar[rg]]++;
            ans += ar[rg]*k[ar[rg]]*k[ar[rg]];
        }
        while(rg > i.r){
            ans -= ar[rg]*k[ar[rg]]*k[ar[rg]];
            k[ar[rg]]--;
            ans += ar[rg]*k[ar[rg]]*k[ar[rg]];
            rg--;
        }
        solution[i.id] = ans;
    }
    for(int i = 0; i < q; i++){
        cout << solution[i] << "\n"[i == q-1];
    }
    return 0;
}