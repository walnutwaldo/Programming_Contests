// pretty much follows kactl implementation

bool Q = false;

struct Line {

    ll slope, yint;
    mutable ld pass;

    bool operator<(const Line& o) const {
        return Q ? pass < o.pass : slope < o.slope;
    }
};

struct cht : multiset<Line> {

    bool isect(iterator x, iterator y) {
        if (y == end()) { x->pass = 1/0.0; return 0; }
        if (x->slope == y->slope) x->pass = ((x->yint > y->yint)? 1/0.0 : -1/0.0);
        else x->pass = (ld)(x->yint - y->yint) / (y->slope - x->slope);
        return x->pass >= y->pass;
    }

	void add(ll slope, ll yint) {
        auto z = insert({slope, yint, 0}), y = z++, x = y;
        while(isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->pass >= y->pass) isect(x, erase(y));
	}

	ll query(ll x) {
        Q = true;
        auto ptr = *LB({0, 0, (ld)x});
        Q = false;
        return ptr.slope * x + ptr.yint;
	}
};
