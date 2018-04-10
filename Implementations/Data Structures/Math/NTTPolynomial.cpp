// Uses NTT.cpp
// https://github.com/walnutwaldo/Programming_Contests/blob/master/Implementations/Algorithms/NTT.cpp

using namespace NTT;

struct Polynomial {

    int deg;
    ull *coefficients;

    Polynomial(int d = 0) {
        deg = d;
        coefficients = new ull[deg + 1];
        memset(coefficients, 0, (deg + 1) * sizeof(ull));
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

    Polynomial operator +(ull a) {
        Polynomial p(deg);
        F0R(i, deg + 1) p[i] = coefficients[i];
        p[0] += a;
        p[0] %= NTT_MOD;
        return p;
    }

    Polynomial operator -(ull a) {
        Polynomial p(deg);
        F0R(i, deg + 1) p[i] = coefficients[i];
        p[0] += NTT_MOD - a;
        p[0] %= NTT_MOD;
        return p;
    }

    Polynomial operator *(ull mult) {
        Polynomial p(deg);
        F0R(i, deg + 1) p[i] = coefficients[i] * mult % NTT_MOD;
        return p;
    }

    Polynomial operator /(ull div) { return *this * invMod(div); }

    Polynomial operator +(Polynomial b) {
        Polynomial res(max(deg, b.deg));
        F0R(i, max(deg, b.deg) + 1) res[i] = (((i > deg) ? 0 : coefficients[i]) + ((i > b.deg) ? 0 : b[i])) % NTT_MOD;
        return res;
    }

    Polynomial operator -(Polynomial p) { return *this + (p * (NTT_MOD - 1)); }

    Polynomial operator *(Polynomial b) {
        vul va, vb;
        F0R(i, deg + 1) va.PB((*this)[i]);
        F0R(i, b.deg + 1) vb.PB(b[i]);
        vul vc = NTT::conv(va, vb);
        Polynomial res(vc.size() - 1);
        F0R(i, vc.size()) res[i] = vc[i];
        return res;
    }

    void operator +=(ull a) { coefficients[0] += a, coefficients[0] %= NTT_MOD; }

    void operator -=(ull a) { *this += NTT_MOD - a; }

    void operator *=(ull mult) { F0R(i, deg + 1) coefficients[i] *= mult, coefficients[i] %= NTT_MOD; }

    void operator /=(ull div) { *this *= invMod(div); }

    void operator +=(Polynomial b) { *this = *this + b; }

    void operator -=(Polynomial p) { *this = *this - p; }

    void operator *=(Polynomial b) { *this = *this * b; }

    ull& operator [](int idx) { return coefficients[idx]; }

};
