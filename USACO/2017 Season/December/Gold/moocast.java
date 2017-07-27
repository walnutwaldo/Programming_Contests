import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class moocast {

    private static final String IN_FILE = "moocast.in";
    private static final String OUT_FILE = "moocast.out";

    private static Scanner in;
    private static Printer out;

    private static int N, count;
    private static int[] x, y;
    private static boolean[] seen;

    private static void solve() {
        N = in.nextInt();
        x = new int[N];
        y = new int[N];
        for (int i = 0; i < N; i++) {
            x[i] = in.nextInt();
            y[i] = in.nextInt();
        }

        int max = 0;

        boolean[] inMST = new boolean[N];
        int[] disTo = new int[N];
        Arrays.fill(disTo, -1);
        disTo[0] = 0;

        while (true) {
            int minI = -1;
            for (int i = 0; i < N; i++)
                if (!inMST[i] && disTo[i] != -1 && (minI == -1 || disTo[i] < disTo[minI]))
                    minI = i;
            if (minI == -1)
                break;
            inMST[minI] = true;
            max = Math.max(max, disTo[minI]);
            for (int i = 0; i < N; i++) {
                if (inMST[i])
                    continue;
                int newDis = (x[i] - x[minI]) * (x[i] - x[minI]) + (y[i] - y[minI]) * (y[i] - y[minI]);
                if (disTo[i] == -1 || newDis < disTo[i])
                    disTo[i] = newDis;
            }
        }

        out.println(max);
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
