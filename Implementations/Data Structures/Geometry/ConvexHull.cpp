// pretty much follows kactl implementation

bool Q = false;

struct Line {

    ll slope, yint;
    mutable ld pnt;

    bool operator<(const Line& o) const {
        return Q ? pnt < o.pnt : slope < o.slope;
    }
};

struct cht : multiset<Line> {

    bool isect(iterator x, iterator y) {
        if (y == end()) { x->pnt = 1/0.0; return 0; }
        if (x->slope == y->slope) x->pnt = ((x->yint > y->yint)? 1/0.0 : -1/0.0);
        else x->pnt = (ld)(x->yint - y->yint) / (y->slope - x->slope);
        return x->pnt >= y->pnt;
    }

	void add(ll slope, ll yint) {
        auto z = insert({slope, yint, 0}), y = z++, x = y;
        while(isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->pnt >= y->pnt) isect(x, erase(y));
	}

	ll query(ll x) {
        Q = true;
        auto ptr = *LB({0, 0, (ld)x});
        Q = false;
        return ptr.slope * x + ptr.yint;
	}
};
