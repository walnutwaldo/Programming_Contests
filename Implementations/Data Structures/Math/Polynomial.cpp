// Uses FFT.cpp
// https://github.com/walnutwaldo/Programming_Contests/tree/master/Implementations/Algorithms

using namespace FFT;
cld tempPVPoly[1 << MAX_DEG];

struct Polynomial {

    int deg;
    cld *coefficients;

    Polynomial(int d = 0) {
        deg = d;
        coefficients = new cld[deg + 1];
        memset(coefficients, 0, (deg + 1) * sizeof(cld));
        buildRT();
    }

    Polynomial operator ()(Polynomial p) {
        Polynomial curr;
        curr[0] = 1;
        Polynomial res;
        F0R(i, deg + 1) {
            res += curr * coefficients[i];
            curr *= p;
        }
        return res;
    }

    cld& operator [](int idx) { return coefficients[idx]; }

    Polynomial operator +(cld a) {
        Polynomial p(deg);
        F0R(i, deg + 1) p[i] = coefficients[i];
        p[0] += a;
        return p;
    }

    Polynomial operator -(cld a) {
        Polynomial p(deg);
        F0R(i, deg + 1) p[i] = coefficients[i];
        p[0] -= a;
        return p;
    }

    Polynomial operator *(cld mult) {
        Polynomial p(deg);
        F0R(i, deg + 1) p[i] = coefficients[i] * mult;
        return p;
    }

    Polynomial operator /(cld div) { return *this * (cld(1, 0) / div); }

    Polynomial operator +(Polynomial b) {
        Polynomial res(max(deg, b.deg));
        F0R(i, max(deg, b.deg) + 1) res[i] = ((i > deg) ? 0 : coefficients[i]) + ((i > b.deg) ? 0 : b[i]);
        return res;
    }

    Polynomial operator -(Polynomial p) { return *this + (p * -cld(1, 0)); }

    Polynomial operator *(Polynomial b) {
        int neededDeg = 32 - __builtin_clz(deg + b.deg);
        fft(neededDeg, coefficients, deg + 1);
        F0R(i, (1 << neededDeg)) tempPVPoly[i] = FFTBuild[i][0];
        fft(neededDeg, b.coefficients, b.deg + 1);
        F0R(i, (1 << neededDeg)) tempPVPoly[i] = tempPVPoly[i] * FFTBuild[i][0];
        invfft(neededDeg, tempPVPoly, 1 << neededDeg);
        Polynomial res(deg + b.deg);
        F0R(i, res.deg + 1) res[i] = FFTBuild[i][0];
        return res;
    }

    void operator +=(ull a) { coefficients[0] += a; }

    void operator -=(ull a) { *this += -a; }

    void operator *=(ull mult) { F0R(i, deg + 1) coefficients[i] *= mult; }

    void operator /=(ull div) { *this *= 1 / div; }

    void operator +=(Polynomial b) { *this = *this + b; }

    void operator -=(Polynomial p) { *this = *this - p; }

    void operator *=(Polynomial b) { *this = *this * b; }

};
