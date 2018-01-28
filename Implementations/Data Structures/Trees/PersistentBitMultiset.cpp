struct PersistentBitMultiset {

    struct BitMultiset {

        int inSubtree = 0;
        BitMultiset *children[2] {NULL, NULL};

    };

    int sz = 1, autoTree = 0;
    vector<BitMultiset> trees;

    PersistentBitMultiset() { trees.PB(BitMultiset()); }

    void insert(int t, ll v) {
        v ^= (1LL << 63);
        trees.PB(BitMultiset());
        BitMultiset *newCurr = &trees[sz], *curr = &trees[t];
        int bit = 63;
        while(1) {
            if(curr != NULL) F0R(i, 2) if(i == ((v & (1LL << bit)) == 0)) newCurr->children[i] = curr->children[i];
            newCurr->inSubtree = curr ? 1 + curr->inSubtree : 1;
            if(bit == -1) break;
            if(curr) curr = curr->children[(v & (1LL << bit)) != 0];
            newCurr = newCurr->children[(v & (1LL << bit--)) != 0] = new BitMultiset();
        }
        autoTree = sz++;
    }

    int count(int t, ll v) {
        v ^= (1LL << 63);
        BitMultiset *curr = &trees[t];
        int bit = 63;
        while(bit >= 0)
            if(!curr) return 0;
            else curr = curr->children[(v & (1LL << bit--)) != 0];
        return curr->inSubtree;
    }

    void erase(int t, ll v) {
        if(!count(t, v)) return;
        v ^= (1LL << 63);
        trees.PB(BitMultiset());
        BitMultiset *newCurr = &trees[sz], *curr = &trees[t];
        int bit = 63;
        newCurr->inSubtree = curr->inSubtree - 1;
        while(1) {
            F0R(i, 2) if(i == ((v & (1LL << bit)) == 0)) newCurr->children[i] = curr->children[i];
            if(curr->children[(v & (1LL << bit)) != 0] == NULL || curr->children[(v & (1LL << bit)) != 0]->inSubtree == 1) break;
            newCurr = newCurr->children[(v & (1LL << bit)) != 0] = new BitMultiset();
            curr = curr->children[(v & (1LL << bit--)) != 0];
            newCurr->inSubtree = curr->inSubtree - 1;
        }
        autoTree = sz++;
    }

    int LB(int t, ll v) {
        v ^= (1LL << 63);
        BitMultiset *curr = &trees[t];
        int bit = 63, res = 0;
        while(curr != NULL) {
            if((v & (1LL << bit)) != 0 && curr->children[0]) res += curr->children[0]->inSubtree;
            curr = curr->children[(v & (1LL << bit--)) != 0];
        }
        return res;
    }

    void insert(ll v) {insert(autoTree, v); }

    int count(ll v) { return count(autoTree, v); }

    void erase(ll v) { erase(autoTree, v); }

    int LB(ll v) { return LB(autoTree, v); }

};
