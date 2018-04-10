// Uses FFT.cpp
// https://github.com/walnutwaldo/Programming_Contests/tree/master/Implementations/Algorithms

using namespace FFT;

struct Polynomial {

    int deg;
    ld *coefficients;

    Polynomial(int d = 0) {
        deg = d;
        coefficients = new ld[deg + 1];
        memset(coefficients, 0, (deg + 1) * sizeof(ld));
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

    Polynomial operator +(ld a) {
        Polynomial p(deg);
        F0R(i, deg + 1) p[i] = coefficients[i];
        p[0] += a;
        return p;
    }

    Polynomial operator -(ld a) {
        Polynomial p(deg);
        F0R(i, deg + 1) p[i] = coefficients[i];
        p[0] -= a;
        return p;
    }

    Polynomial operator *(ld mult) {
        Polynomial p(deg);
        F0R(i, deg + 1) p[i] = coefficients[i] * mult;
        return p;
    }

    Polynomial operator /(ld div) { return *this / div; }

    Polynomial operator +(Polynomial b) {
        Polynomial res(max(deg, b.deg));
        F0R(i, max(deg, b.deg) + 1) res[i] = ((i > deg) ? 0 : coefficients[i]) + ((i > b.deg) ? 0 : b[i]);
        return res;
    }

    Polynomial operator -(Polynomial p) { return *this + (p * -1); }

    Polynomial operator *(Polynomial b) {
        vector<cld> va, vb;
        F0R(i, deg + 1) va.PB((*this)[i]);
        F0R(i, b.deg + 1) vb.PB(b[i]);
        vector<cld> vc = FFT::conv(va, vb);
        Polynomial res(vc.size() - 1);
        F0R(i, vc.size()) res[i] = vc[i].real();
        F0R(i, vc.size()) if(abs(res[i] - round(res[i])) < 1e-9)
            res[i] = round(res[i]);
        return res;
    }

    void operator +=(ld a) { coefficients[0] += a; }

    void operator -=(ld a) { *this += -a; }

    void operator *=(ld mult) { F0R(i, deg + 1) coefficients[i] *= mult; }

    void operator /=(ld div) { *this *= 1 / div; }

    void operator +=(Polynomial b) { *this = *this + b; }

    void operator -=(Polynomial p) { *this = *this - p; }

    void operator *=(Polynomial b) { *this = *this * b; }

    ld& operator [](int idx) { return coefficients[idx]; }

};
