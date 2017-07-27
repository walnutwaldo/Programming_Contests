import java.io.*;
import java.util.*;

public class lasers {

    private static final String IN_FILE = "lasers.in";
    private static final String OUT_FILE = "lasers.out";

    private static Scanner in;
    private static Printer out;

    private static int N, xl, yl, xb, yb;

    private static HashMap<Integer, List<Integer>> connections = new HashMap<Integer, List<Integer>>();

    private static void solve() {
        N = in.nextInt();
        xl = in.nextInt();
        yl = in.nextInt() + 1000000001;
        xb = in.nextInt();
        yb = in.nextInt() + 1000000001;

        for (int i = 0; i < N; i++) {
            int x = in.nextInt();
            int y = in.nextInt() + 1000000001;
            if (!connections.containsKey(x))
                connections.put(x, new ArrayList<Integer>());
            if (!connections.containsKey(y))
                connections.put(y, new ArrayList<Integer>());

            connections.get(x).add(y);
            connections.get(y).add(x);
        }

        Queue<Case> queue = new LinkedList<Case>();
        queue.add(new Case(xl, 0));
        queue.add(new Case(yl, 0));
        Set<Integer> seen = new HashSet<Integer>();
        seen.add(xl);
        seen.add(yl);
        while (!queue.isEmpty()) {
            Case c = queue.poll();
            if (c.pos == xb || c.pos == yb) {
                out.println(c.moves);
                return;
            }
            if (connections.get(c.pos) != null)
                for (int next : connections.get(c.pos))
                    if (!seen.contains(next)) {
                        queue.add(new Case(next, c.moves + 1));
                        seen.add(next);
                    }
        }

        out.println(-1);
    }

    public static void main(String[] args) {
        in = new Scanner(IN_FILE);
        out = new Printer(OUT_FILE);
        solve();
        out.close();
        System.exit(0);
    }

    private static class Case {

        int pos;
        int moves;

        public Case(int pos, int moves) {
            this.pos = pos;
            this.moves = moves;
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
