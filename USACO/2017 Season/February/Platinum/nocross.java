import java.io.*;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class nocross {

    private static final String IN_FILE = "nocross.in";
    private static final String OUT_FILE = "nocross.out";

    private static Scanner in;
    private static Printer out;

    private static int N, upperN;
    private static int[] value, rightIndex;
    private static int[] tree;

    private static void solve() {
        N = in.nextInt();
        upperN = (int) Math.pow(2, Math.ceil(Math.log(N) / Math.log(2)));
        tree = new int[2 * upperN + 1];
        value = new int[N];
        rightIndex = new int[N];
        for (int i = 0; i < N; i++)
            value[i] = in.nextInt() - 1;
        for (int i = 0; i < N; i++)
            rightIndex[in.nextInt() - 1] = i;

        for (int i = 0; i < N; i++) {
            List<Integer> indicies = new ArrayList<Integer>();
            for (int connection = Math.max(0, value[i] - 4); connection <= Math.min(N - 1, value[i] + 4); connection++)
                indicies.add(rightIndex[connection]);
            Collections.sort(indicies);
            for (int index = indicies.size() - 1; index >= 0; index--) {
                update(indicies.get(index), max(0, indicies.get(index) - 1) + 1);
            }
        }
        out.println(max(0, N - 1));
    }

    private static void update(int index, int val) {
        index += upperN;
        while (index > 0) {
            tree[index] = Math.max(tree[index], val);
            index /= 2;
        }
    }

    private static int max(int lo, int hi) {
        lo += upperN;
        hi += upperN;
        int max = 0;
        while (lo <= hi) {
            if (lo % 2 == 1) max = Math.max(max, tree[lo++]);
            if (hi % 2 == 0) max = Math.max(max, tree[hi--]);
            lo /= 2;
            hi /= 2;
        }
        return max;
    }

    public static void main(String[] args) {
        in = new Scanner(IN_FILE);
        out = new Printer(OUT_FILE);
        solve();
        out.close();
        System.exit(0);
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
