import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class haybales {

    private static final String IN_FILE = "haybales.in";
    private static final String OUT_FILE = "haybales.out";

    private static Scanner in;
    private static Printer out;

    private static int N, Q;
    private static int[] haybales;

    private static void solve() {
        N = in.nextInt();
        Q = in.nextInt();

        haybales = new int[N];
        for (int i = 0; i < N; i++) {
            haybales[i] = in.nextInt();
        }
        Arrays.sort(haybales);
        for (int q = 0; q < Q; q++) {
            int A = in.nextInt(), B = in.nextInt();
            int hi = search(B, -1);
            int lo = search(A, 0);
            out.println(hi - lo + 1);
        }
    }

    private static int search(int i, int change) {
        int lo = 0, hi = N - 1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (haybales[mid] == i)
                return mid;
            if (haybales[mid] > i)
                hi = mid - 1;
            else
                lo = mid + 1;
        }
        return lo + change;
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
