import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class mincross {

    private static final String IN_FILE = "mincross.in";
    private static final String OUT_FILE = "mincross.out";

    private static Scanner in;
    private static Printer out;

    private static int N;
    private static long numIntersections = 0;
    private static int[][] position, val;

    private static void solve() {
        N = in.nextInt();
        position = new int[N][2];
        val = new int[N][2];
        for (int i = 0; i < N; i++) {
            int next = in.nextInt() - 1;
            position[next][0] = i;
            val[i][1] = next;
        }
        for (int i = 0; i < N; i++) {
            int next = in.nextInt() - 1;
            position[next][1] = i;
            val[i][0] = next;
        }
        countIntersections(0, N);
        long min = numIntersections;
        for (int j = 0; j < 2; j++)
            for (int i = N - 1; i >= 0; i--) {
                long numInt = N - position[val[i][j]][j] - 1;
                numIntersections += (N - 1 - numInt) - (numInt);
                min = Math.min(min, numIntersections);
            }
        out.println(min);
    }

    private static int[] countIntersections(int lo, int hi) {
        if (hi == lo + 1)
            return new int[]{position[val[lo][0]][0]};
        int mid = (hi + lo) / 2;
        int[] left = countIntersections(lo, mid);
        int[] right = countIntersections(mid, hi);
        int[] combined = new int[hi - lo];
        int curr = 0, i = 0, j = 0;
        while (curr < combined.length) {
            if (j == right.length || (i < left.length && left[i] < right[j])) {
                combined[curr++] = left[i++];
            } else {
                combined[curr++] = right[j++];
                numIntersections += left.length - i;
            }
        }
        return combined;
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
