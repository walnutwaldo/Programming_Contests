struct StringTokenizer {

    int ptr = 0;
    string s;

    void takeString(string ss) {
        s = ss;
        ptr = 0;
    }

    string nextToken() {
        if(ptr == s.size()) return "";
        string token = "";
        while(ptr < s.size() && s[ptr] == ' ') ptr++;
        if(ptr == s.size()) return "";
        while(ptr < s.size() && s[ptr] != ' ') token += s[ptr++];
        return token;
    }

};
