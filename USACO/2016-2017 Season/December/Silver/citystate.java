import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class citystate {

    private static final String IN_FILE = "citystate.in";
    private static final String OUT_FILE = "citystate.out";

    private static Scanner in;
    private static Printer out;

    private static int N;
    private static int[][][][] count = new int[26][26][26][26];

    private static void solve() {
        N = in.nextInt();
        long answer = 0;
        for (int i = 0; i < N; i++) {
            String city = in.next();
            String state = in.next();
            if (city.charAt(0) != state.charAt(0) || city.charAt(1) != state.charAt(1))
                answer += count[state.charAt(0) - 'A'][state.charAt(1) - 'A'][city.charAt(0) - 'A'][city.charAt(1) - 'A'];
            count[city.charAt(0) - 'A'][city.charAt(1) - 'A'][state.charAt(0) - 'A'][state.charAt(1) - 'A']++;
        }
        out.println(answer);
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
