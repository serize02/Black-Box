
struct mat{
    int m[SIZE][SIZE];
    mat(){
        //init mat
    }
    mat friend operator *(const mat &a, const mat &b){
        mat c;
        for(int i = 0; i < 5; i++){
            for(int j = 0; j < 5; j++){
                c.m[i][j] = 0;
                for(int k = 0; k < 5; k++){
                    c.m[i][j] = (c.m[i][j]+( a.m[i][k]*b.m[k][j] )%mod)%mod;
                }
            }
        }
        return c;
    }
};

inline mat pow_mod(int n){
    mat ans, a;
    mat();
    // set ans as unity matrix
    for(;n ;n >>= 1){
        if(n&1) ans = ans*a;
        a = a*a;
    }
    return ans;
}