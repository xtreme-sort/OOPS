#include <bits/stdc++.h>

using namespace std;

#define int int64_t

const int MOD = 1e9 + 7;

class matrix{
    private:
        int mat[2][2];

    public:
        matrix(){}
        matrix(int x1, int x2, int x3, int x4){
            mat[0][0] = x1;
            mat[0][1] = x2;
            mat[1][0] = x3;
            mat[1][1] = x4;

        }

        matrix operator * (matrix m2){
            matrix m3(0,0,0,0);

            for(int i = 0 ; i < 2 ; i++){
                for(int j = 0 ; j < 2 ; j++){
                    for(int k = 0 ; k < 2 ; k++){
                        m3.mat[i][j] += (mat[i][k] * m2.mat[k][j])%MOD; 
                        m3.mat[i][j] %= MOD;
                    }
                }
            }
            return m3;
        }

        int fibonnaci(int N){
            if(N == 0) return 0;

            matrix identity(1,0,0,1);
            matrix ans(1,1,1,0);
    
            while(N){
                if(N & 1) identity  = identity*ans;
                ans = ans*ans;
                N >>= 1;
            }

            return identity.mat[0][1];
        }

};

class currencyStorer{

    public:
        currencyStorer(){}

        vector<int> quickSort(vector<int>& arr){
            int N = arr.size();
            if(N <= 1) return arr;
            int pivot = arr[N - 1];

            vector<int> left,right;
            for(auto x : arr){
                if(x < pivot) left.push_back(x);
                else if(x > pivot) right.push_back(x);
            }

            left = quickSort(left);
            right = quickSort(right);

            arr.clear();

            for(auto x : left){
                arr.push_back(x);
            }
            
            arr.push_back(pivot);

            for(auto x : right){
                arr.push_back(x);
            }

            return arr;
        }
        
        void operator () (vector<int>& arr){
            arr = quickSort(arr);
            for(auto x : arr){
                cout << x << " ";
            }
            cout << endl;
        }
};


class fibonacciGenerator{
    private:
        int N;
    public:
        fibonacciGenerator(){}

        int operator ()(int N_){
            matrix m;
            return m.fibonnaci(N_);
        }
};


class primeCalculator{
    public:
        primeCalculator(){}

        map<int,bool> genprimes(int L, int R){
            map<int,bool> primes;

            for(int i = L ; i <= R ; i++){
                primes[i] = true;
            }
            
            bool prime[1000010];
            int n = 1e6 + 9;
            for (int i = 0; i <= n; i++) prime[i] = 1;

            for (int p = 2; p * p <= n; p++) { 
            if (prime[p] == true) { 
                for (int i = p * p; i <= n; i += p) 
                    prime[i] = false; 
                } 
            } 
            prime[1] = prime[0] = 0;

            vector<int> primelist;
            for (int i = 2; i <= n; i++) if (prime[i]) primelist.push_back(i);

            for(auto i : primelist){
                for(int j = ((L + i - 1)/i) * i ; j <= R ; j += i){
                    if(i != j) primes[j] = false;
                }
            }

            return primes;
        }  

        void printPrimes(int L, int R){
            map<int,bool> prime = genprimes(L, R);
            for(int i = L ; i <= R ; i++){
                if(prime[i] and i != 1 ) cout << i << " ";
            }
            cout << endl;
        }

        int printPrimeSum(int L, int R){
            map<int,bool> prime = genprimes(L, R);

            int sum = 0;
            for(int i = L ; i <= R ; i++){
                if(prime[i] and i != 1) sum += i;
            }

            return sum;
        }

};

class numberAnalyzer{
    public:
        numberAnalyzer(){}

        bool isSquareFree(int X){
            if(X%4 == 0) return false;
            for(int i = 3 ; i*i <= X ; i+=2){
                if(X % i == 0){
                    X /= i;
                    if(X % i ==0){
                        return false;
                    }
                }
            }
            return true;
        }

        int countDivisors(int X){
            int count = 0;

            for(int i = 1 ; i*i <= X ; i++){
                if(X % i == 0){
                    count++;
                    if(X/i != i) count++;
                }
            }
            return count;
        }

        int sumOfDivisors(int X){
            int sum = 0;
            for(int i = 1 ; i*i <= X ; i++){
                if(X % i == 0){
                    sum += i;
                    if(X/i != i) sum += X/i ;
                }
            }
            return sum;
        }

};




int32_t main(){

    int type;
    cin >> type;

    if(type == 1){
        int t;
        cin >> t;

        while(t--){
            int n;
            cin >> n;

            vector<int> A(n);
            for(auto &x : A) cin >> x;

            currencyStorer curstore;
            
            curstore(A);
        }
    }

    else if(type == 2){
        int t;
        cin >> t;

        while(t--){
            int i;
            cin >> i;
            
            fibonacciGenerator fibgen;
            int ans = fibgen(i);
            cout << ans << endl;
        }
    }

    else if(type == 3){
        int t;
        cin >> t;

        while(t--){
            string s;
            int L,R;

            cin >> s >> L >> R;
            primeCalculator primecalc;

            if(s == "printPrimes"){
                primecalc.printPrimes(L, R);
            }
            else if(s == "printPrimeSum"){  
                int ans = primecalc.printPrimeSum(L, R);
                cout << ans << endl;
            }
        }
    }


    else if(type == 4){
        int t;
        cin >> t;

        while(t--){
            string s;
            int X;

            cin >> s >> X;
            numberAnalyzer numanalyze;

            if(s== "isSquareFree"){
                bool yes = numanalyze.isSquareFree(X);
                if(yes) cout << "yes" << endl;
                else cout << "no" << endl;
            }
            else if(s == "countDivisors"){
                int ans = numanalyze.countDivisors(X);
                cout << ans << endl;
            }
            else if(s == "sumOfDivisors"){
                int ans = numanalyze.sumOfDivisors(X);
                cout << ans << endl;
            }
        }
    }

    return 0;
}
