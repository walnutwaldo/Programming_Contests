// Uses NTT.cpp
// https://github.com/walnutwaldo/Programming_Contests/blob/master/Implementations/Algorithms/NTT.cpp

using namespace NTT;
ull tempPVPoly[1 << MAX_DEG];

struct Polynomial {

    int deg;
    ull *coefficients;

    Polynomial(int d = 0) {
        deg = d;
        coefficients = new ull[deg + 1];
        memset(coefficients, 0, (deg + 1) * sizeof(ull));
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

    ull& operator [](int idx) { return coefficients[idx]; }

    Polynomial operator +(ull a) {
        Polynomial p(deg);
        F0R(i, deg + 1) p[i] = coefficients[i];
        p[0] += a;
        p[0] %= NTTMod;
        return p;
    }

    Polynomial operator -(ull a) {
        Polynomial p(deg);
        F0R(i, deg + 1) p[i] = coefficients[i];
        p[0] += NTTMod - a;
        p[0] %= NTTMod;
        return p;
    }

    Polynomial operator *(ull mult) {
        Polynomial p(deg);
        F0R(i, deg + 1) p[i] = coefficients[i] * mult % NTTMod;
        return p;
    }

    Polynomial operator /(ull div) { return *this * invMod(div); }

    Polynomial operator +(Polynomial b) {
        Polynomial res(max(deg, b.deg));
        F0R(i, max(deg, b.deg) + 1) res[i] = (((i > deg) ? 0 : coefficients[i]) + ((i > b.deg) ? 0 : b[i])) % NTTMod;
        return res;
    }

    Polynomial operator -(Polynomial p) { return *this + (p * (NTTMod - 1)); }

    Polynomial operator *(Polynomial b) {
        int neededDeg = 32 - __builtin_clz(deg + b.deg);
        ntt(neededDeg, coefficients, deg + 1);
        F0R(i, (1 << neededDeg)) tempPVPoly[i] = NTTBuild[i][0];
        ntt(neededDeg, b.coefficients, b.deg + 1);
        F0R(i, (1 << neededDeg)) tempPVPoly[i] = tempPVPoly[i] * NTTBuild[i][0] % NTTMod;
        invntt(tempPVPoly, neededDeg);
        Polynomial res(deg + b.deg);
        F0R(i, res.deg + 1) res[i] = NTTBuild[i][0];
        return res;
    }

    void operator +=(ull a) { coefficients[0] += a, coefficients[0] %= NTTMod; }

    void operator -=(ull a) { *this += NTTMod - a; }

    void operator *=(ull mult) { F0R(i, deg + 1) coefficients[i] *= mult, coefficients[i] %= NTTMod; }

    void operator /=(ull div) { *this *= invMod(div); }

    void operator +=(Polynomial b) { *this = *this + b; }

    void operator -=(Polynomial p) { *this = *this - p; }

    void operator *=(Polynomial b) { *this = *this * b; }

};
