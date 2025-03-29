#include <bits/stdc++.h>

using namespace std;


#define int long long
#define float long double


// This is the Class for complex number of the form ** real + i(imaginary) **
class Complex{
    private:
        int real;
        int imaginary;

    public:
        // Costructor
        Complex(int real_ = 0, int imaginary_ = 0){
            real = real_;
            imaginary = imaginary_;
        }

        // overloaded + operator to suppot C1 + C2
        Complex operator+(const Complex& C) const {
            return Complex(real + C.real, imaginary + C.imaginary);
        }

        // overloaded - operator to suppot C1 - C2
        Complex operator-(const Complex& C) const {
            return Complex(real - C.real, imaginary - C.imaginary);
        }

        // overloaded * operator to support C * x
        Complex operator*(int x) const {
            return Complex(real * x, imaginary * x);
        }

        // overloaded * operator to support C1 * C2 
        Complex operator*(const Complex& C) const {
            return Complex(real * C.real - imaginary * C.imaginary, real * C.imaginary + imaginary * C.real);
        }

        // overloaded = operator to support C1 = C2
        Complex operator=(const Complex& C) {
            real = C.real;
            imaginary = C.imaginary;
            return *this;
        }
        
        // Overloaded == operator to compare two Complex numbers
        bool operator==(const Complex& C) const {
            return real == C.real && imaginary == C.imaginary;
        }
        
        // overloaded >> operator to support cin >> C
        friend istream& operator>>(istream& in, Complex& C) {
            in >> C.real >> C.imaginary;
            return in;
        }

        // overloaded << operator to support cout << C
        friend ostream& operator<<(ostream& out, Complex& C) {
            out << C.real << " " << C.imaginary;
            return out;
        } 
};


string operator*(string s, int x){
    string ans = "";
    for(int i = 0 ; i < x ; i++){
        ans += s;
    }
    return ans;
}

// This is the polynomial class 
// It contains coeff vector of polynomial
template<typename T>
class Polynomial{
    private:
    vector<T> coeff;
    
    public:
        Polynomial<T>() {}
        Polynomial<T>(vector<T> coeff_){
            int N = coeff_.size();
            coeff.resize(N);
            coeff = coeff_;
        }

        vector<T> get_coeff(){
            return coeff;
        }

        Polynomial<T> operator = (const Polynomial<T>& P){
            if(this != &P){
                coeff = P.coeff;
            }
            return *this;
        }

        friend istream& operator >> (istream& in, Polynomial<T>& P){
            int deg;
            in >> deg;
            P.coeff.resize(deg);
            
            for (int i = 0; i < deg; i++) {
                in >> P.coeff[i];
            }
            
            return in;
        }

        void print(){
            for(auto x : coeff){
                cout << fixed << setprecision(6) << x << " ";
            }
            cout << endl;
        }
};


// This is the PolynomialMultiplication class which supports Multiplication using karastuba's algo
template<typename T>
class PolynomialMultiplication{
    private:
        
    public:
        // Constructor
        PolynomialMultiplication() {}


        vector<T> karatsubaMultiply(vector<T>& A, vector<T>& B) {
            int n = A.size();
            if (n == 1) {
                vector<T> result(1);
                result[0] = A[0] * B[0];
                return result;
            }
    
            int k = n / 2;
    
            vector<T> A_low(A.begin(), A.begin() + k);
            vector<T> A_high(A.begin() + k, A.end());
            vector<T> B_low(B.begin(), B.begin() + k);
            vector<T> B_high(B.begin() + k, B.end());

    
            vector<T> P1 = karatsubaMultiply(A_low, B_low);
            vector<T> P2 = karatsubaMultiply(A_high, B_high);
    
            vector<T> A_sum(k, T()), B_sum(k, T());
            for (int i = 0; i < k; i++) {
                A_sum[i] = A_low[i] + A_high[i];
                B_sum[i] = B_low[i] + B_high[i];
            }
    
            vector<T> P3 = karatsubaMultiply(A_sum, B_sum);
    
            vector<T> result(2 * n - 1 , T());
    
            for (int i = 0; i < (int) P1.size(); i++)
                result[i] = result[i] + P1[i];
    
            for (int i = 0; i < (int) P2.size(); i++)
                result[i + 2*k] = result[i + 2*k] + P2[i];
    
            for (int i = 0; i < (int) P3.size(); i++)
                result[i + k] = result[i + k] + (P3[i] - P1[i] - P2[i]);
            
            return result;
        }
    
        Polynomial<T> multiply(Polynomial<T>& P1, Polynomial<T>& P2) {
            vector<T> P1coeff = P1.get_coeff();
            vector<T> P2coeff = P2.get_coeff();
            int deg1 = P1coeff.size();
            int deg2 = P2coeff.size();
    
            int N = max(P1coeff.size(), P2coeff.size());
            int size = 1;
            while (size < N) size *= 2;
            size *= 2;
    
            P1coeff.resize(size, T());
            P2coeff.resize(size, T());
    
            vector<T> result_coeff = karatsubaMultiply(P1coeff, P2coeff);
            result_coeff.resize(deg1 + deg2 - 1);
            return Polynomial<T>(result_coeff);
        }


        Polynomial<T> operator *(Polynomial<T>& P){
            return multiply(*this, P);
        }
};



// This is the PolynomialEvaluation class which supports evaluation in O(N)
template<typename T>
class PolynomialEvaluation{
    private:

    public:
        // Constructor
        PolynomialEvaluation() {}

        T evaluate(Polynomial<T>& P, int x){
            T ans = 0;
            vector<T> coeff = P.get_coeff();
    
            int N = coeff.size();
            for(int i = N - 1 ; i >= 0 ; i--){
                ans += coeff[i] * (int)pow(x, i);
            }
            return ans;
        }
};

template <>
string PolynomialEvaluation<string>::evaluate(Polynomial<string>& P, int x) {
    string ans;
    vector<string> coeff = P.get_coeff();
    int N = coeff.size();
    for (int i = N - 1; i >= 0; i--) {
        ans += coeff[i] * ((int)pow(x, i));
    }
    return ans;
}



// This is the PolynomialDifferentiation class which supports differentiation in O(N)
template<typename T>
class PolynomialDifferentiation{
    private:

    public:
        // Constructor
        PolynomialDifferentiation() {}
        Polynomial<T> differentitate(Polynomial<T>& P){

            vector<T> coeff = P.get_coeff();
            int N = coeff.size();

            vector<T> rescoeff(N - 1);

            for(int i = 1 ; i < N ; i++){
                rescoeff[i - 1] = coeff[i] * (T)(i);
            }

            Polynomial<T> res(rescoeff);
            return res;
        }
};


int32_t main(){
    int Q;
    cin >> Q;


    while(Q--){
        int op;
        cin >> op;

        if(op == 1){
            string s;
            cin >> s;
            if(s == "integer"){
                Polynomial<int> P1;
                Polynomial<int> P2;
                Polynomial<int> P3;
                
                cin >> P1;
                cin >> P2;

                PolynomialMultiplication<int> multiply;
                P3 = multiply.multiply(P1, P2);
                P3.print();
            }
            else if(s == "float"){
                Polynomial<float> P1;
                Polynomial<float> P2;
                Polynomial<float> P3;
                
                cin >> P1;
                cin >> P2;
                PolynomialMultiplication<float> multiply;
                P3 = multiply.multiply(P1, P2);
                P3.print();
            }
            else if(s == "complex"){
                Polynomial<Complex> P1;
                Polynomial<Complex> P2;
                Polynomial<Complex> P3;

                cin >> P1;
                cin >> P2;

                PolynomialMultiplication<Complex> multiply;
                P3 = multiply.multiply(P1, P2);
                P3.print();
            }
        }

        if(op == 2){
            string s;
            cin >> s;

            if(s == "integer"){
                Polynomial<int> Pint;
                cin >> Pint;
                PolynomialEvaluation<int> evaluateint; 
                int x;
                cin >> x;
                cout << evaluateint.evaluate(Pint, x) << endl;


            }
            else if(s == "float"){
                Polynomial<float> Pfloat;
                cin >> Pfloat;
                PolynomialEvaluation<float> evaluatefloat;
                int x;
                cin >> x;
                cout << fixed << setprecision(6) << evaluatefloat.evaluate(Pfloat, x) << endl;
            }

            else if(s == "string"){
                Polynomial<string> Pstring;
                cin >> Pstring;
                PolynomialEvaluation<string> evaluatestring;
                int x;
                cin >> x;
                cout << evaluatestring.evaluate(Pstring, x) << endl;
            }
        }
        else if(op == 3){
            string s;
            cin >> s;

            if(s == "integer"){
                Polynomial<int> Pint;
                Polynomial<int> P3;
                cin >> Pint;
                PolynomialDifferentiation<int> differentiateint;
                P3 = differentiateint.differentitate(Pint);
                P3.print();

            }
            else if(s == "float"){
                Polynomial<float> Pfloat;
                Polynomial<float> P3;
                cin >> Pfloat;
                
                PolynomialDifferentiation<float> differentiatefloat;
                P3 = differentiatefloat.differentitate(Pfloat);
                P3.print();
            }
        }
    }
    return 0;
}
