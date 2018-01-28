struct PersistantTrieMap {

    struct TrieMap {

        ll val = -1;
        int inSubtree = 0;
        TrieMap *children[26];

        TrieMap() { memset(children, 0, 26 * sizeof(TrieMap*)); }

    };

    int sz = 1, autoTree = 0;
    vector<TrieMap> trees;

    PersistantTrieMap() { trees.PB(TrieMap()); }

    void set(int t, string key, ll val) {
        bool first = (get(t, key) == -1);
        trees.PB(TrieMap());
        TrieMap *newCurr = &trees[sz], *curr = &trees[t];
        int pos = 0;
        while(1) {
            if(curr) F0R(i, 26) if(pos == key.size() || i != key[pos] - 'a') newCurr->children[i] = curr->children[i];
            if(curr) newCurr->val = curr->val;
            newCurr->inSubtree = (curr ? first + curr->inSubtree : 1);
            if(pos == key.size()) {
                newCurr->val = val;
                break;
            }
            newCurr = newCurr->children[key[pos] - 'a'] = new TrieMap();
            if(curr) curr = curr->children[key[pos] - 'a'];
            pos++;
        }
        autoTree = sz++;
    }

    void erase(int t, string key) {
        if(get(t, key) == -1) return;
        trees.PB(TrieMap());
        TrieMap *newCurr = &trees[sz], *curr = &trees[t];
        int pos = 0;
        while(1) {
            F0R(i, 26) if(pos == key.size() || i != key[pos] - 'a') newCurr->children[i] = curr->children[i];
            newCurr->val = curr->val;
            newCurr->inSubtree = curr->inSubtree - 1;
            if(pos == key.size() || (curr = curr->children[key[pos] - 'a'])->inSubtree == 1) {
                if(pos == key.size()) newCurr->val = -1;
                break;
            }
            newCurr = newCurr->children[key[pos++] - 'a'] = new TrieMap();
        }
        autoTree = sz++;
    }

    ll get(int t, string key) {
        TrieMap *curr = &trees[t];
        int pos = 0;
        while(1) {
            if(curr == NULL) return -1;
            if(pos == key.size()) return curr->val;
            curr = curr->children[key[pos++] - 'a'];
        }
    }

    void set(string key, ll val) { set(autoTree, key, val); }

    ll get(string key) { return get(autoTree, key); }

    void erase(string key) { erase(autoTree, key); }

};
