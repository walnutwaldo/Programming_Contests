import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class friendcross {

    private static final String IN_FILE = "friendcross.in";
    private static final String OUT_FILE = "friendcross.out";
    private static int[] seq;
    private static Scanner in;
    private static Printer out;
    private static int[] arr;
    private static int[] brr;

    public static void main(String[] args) {
        in = new Scanner(IN_FILE);
        out = new Printer(OUT_FILE);
        solve();
        out.close();
        System.exit(0);
    }

    public static void solve() {
        int n = in.nextInt(), k = in.nextInt();
        arr = in.nextIntArray(n);
        brr = in.nextIntArray(n);
        int[] ra = new int[n + 1];
        int[] rb = new int[n + 1];
        for (int i = 0; i < n; i++) {
            ra[arr[i]] = i + 1;
            rb[brr[i]] = i + 1;
        }

        seq = new int[n + 1];
        for (int i = 1; i <= n; i++) {
            seq[ra[i]] = rb[i];
        }
        friendcross.SegmentTree root = new friendcross.SegmentTree(1, n);
        ArrayList<friendcross.Event>[] events = new ArrayList[n + 1];
        for (int i = 0; i <= n; i++) events[i] = new ArrayList<>();
        for (int i = 1; i <= n; i++) {
            events[Math.max(0, i - k - 1)].add(new Event(i, -1));
            events[Math.min(n, i + k)].add(new Event(i, 1));
        }
        long tinv = 0;
        BIT x = new BIT(n);
        for (int i = 1; i <= n; i++) {
            x.update(seq[i]);
            tinv += i - x.query(seq[i]);
        }
        long res = 0;
        for (int cow = 1; cow <= n; cow++) {
            root.update(ra[cow]);
            for (friendcross.Event e : events[cow]) {
                res += e.sign * root.query(1, ra[e.cow], rb[e.cow]);
            }
        }
        out.println(tinv - res);
    }

    static class Event {
        public int cow;
        public int sign;

        public Event(int cow, int sign) {
            this.cow = cow;
            this.sign = sign;
        }

    }

    static class SegmentTree {
        public int[] arr;
        public int[] pl;
        public int[] pr;
        public BIT bit;
        public int start;
        public int end;
        public friendcross.SegmentTree lchild;
        public friendcross.SegmentTree rchild;

        public SegmentTree(int start, int end) {
            this.start = start;
            this.end = end;
            arr = new int[end - start + 2];
            if (start == end) {
                arr[1] = seq[start];
            } else {
                int mid = (start + end) >> 1;
                lchild = new friendcross.SegmentTree(start, mid);
                rchild = new friendcross.SegmentTree(mid + 1, end);
                pl = new int[lchild.arr.length];
                pr = new int[rchild.arr.length];
                int lidx = 1, ridx = 1;

                int idx = 1;
                int[] larr = lchild.arr, rarr = rchild.arr;
                while (lidx < larr.length && ridx < rarr.length) {
                    if (larr[lidx] < rarr[ridx]) {
                        pl[lidx] = idx;
                        arr[idx++] = larr[lidx++];
                    } else {
                        pr[ridx] = idx;
                        arr[idx++] = rarr[ridx++];
                    }
                }
                while (lidx < larr.length) {
                    pl[lidx] = idx;
                    arr[idx++] = larr[lidx++];
                }
                while (ridx < rarr.length) {
                    pr[ridx] = idx;
                    arr[idx++] = rarr[ridx++];
                }
            }
            bit = new BIT(end - start + 2);
        }

        public int query(int s, int e, int k) {
            if (start == s && end == e) {
                if (k < arr[1]) return bit.count;
                int lo = 1, hi = arr.length - 1;
                while (lo < hi) {
                    int mid = (lo + hi + 1) / 2;
                    if (arr[mid] > k) hi = mid - 1;
                    else lo = mid;
                }
                return bit.count - bit.query(lo);
            }
            int mid = (start + end) >> 1;
            if (mid >= e) return lchild.query(s, e, k);
            else if (mid < s) return rchild.query(s, e, k);
            else return lchild.query(s, mid, k) + rchild.query(mid + 1, e, k);
        }

        public int update(int p) {
            if (start == p && end == p) {
                bit.update(1);
                return 1;
            }
            int mid = (start + end) >> 1;
            int apos = -1;
            if (mid >= p) apos = pl[lchild.update(p)];
            else apos = pr[rchild.update(p)];
            bit.update(apos);
            return apos;
        }

    }


    static class BIT {
        public int count;
        private int[] tree;
        private int N;

        public BIT(int N) {
            this.N = N;
            this.tree = new int[N + 1];
            this.count = 0;
        }

        public int query(int K) {
            int sum = 0;
            for (int i = K; i > 0; i -= (i & -i))
                sum += tree[i];
            return sum;
        }

        public void update(int K) {
            this.count++;
            for (int i = K; i <= N; i += (i & -i))
                tree[i]++;
        }

    }

    private static class Scanner {

        private String[] strings;
        private int pointer = 0;

        public Scanner(String file) {
            try {
                BufferedReader in = new BufferedReader(new FileReader(file));
                createScanner(in);
            } catch (IOException e) {
            }
        }

        public Scanner(InputStream is) {
            try {
                BufferedReader in = new BufferedReader(new InputStreamReader(is));
                createScanner(in);
            } catch (IOException e) {
            }
        }

        private void createScanner(BufferedReader in) throws IOException {
            List<String> list = new ArrayList<String>();
            String s = in.readLine();
            while (s != null) {
                for (String s2 : s.split(" "))
                    list.add(s2);
                s = in.readLine();
            }
            strings = new String[list.size()];
            for (int i = 0; i < strings.length; i++)
                strings[i] = list.get(i);
        }

        public int nextInt() {
            return Integer.parseInt(strings[pointer++]);
        }

        public long nextLong() {
            return Long.parseLong(strings[pointer++]);
        }

        public String next() {
            return strings[pointer++];
        }

        public char[] nextCharArray() {
            return strings[pointer++].toCharArray();
        }

        public int[] nextIntArray(int n) {
            int[] a = new int[n];
            for (int i = 0; i < n; i++)
                a[i] = nextInt();
            return a;
        }
    }

    private static class Printer {

        private PrintWriter out;

        public Printer(String file) {
            try {
                out = new PrintWriter(new FileWriter(file));
            } catch (IOException e) {

            }
        }

        public void print(Object o) {
            out.print(o);
        }

        public void println(Object o) {
            out.println(o);
        }

        public void println() {
            out.println();
        }

        public void close() {
            out.close();
        }
    }

}
