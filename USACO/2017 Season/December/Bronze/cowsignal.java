import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class cowsignal {

    private static final String IN_FILE = "cowsignal.in";
    private static final String OUT_FILE = "cowsignal.out";

    private static Scanner in;
    private static Printer out;

    private static int N, M, K;
    private static char[][] pattern;

    private static void solve() {
        M = in.nextInt();
        N = in.nextInt();
        K = in.nextInt();
        pattern = new char[M][N];
        for (int m = 0; m < M; m++)
            pattern[m] = in.nextCharArray();

        for (int m = 0; m < M; m++) {
            String s = "";
            for (char c : pattern[m])
                for (int k = 0; k < K; k++)
                    s += c;
            for (int k = 0; k < K; k++)
                out.println(s);
        }
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
