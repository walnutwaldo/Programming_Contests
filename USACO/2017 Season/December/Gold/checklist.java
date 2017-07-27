import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class checklist {

    private static final String IN_FILE = "checklist.in";
    private static final String OUT_FILE = "checklist.out";

    private static Scanner in;
    private static Printer out;

    private static int H, G;
    private static int[] hx, hy, gx, gy;
    private static long[][][] energySpent;

    private static void solve() {
        H = in.nextInt();
        G = in.nextInt();
        hx = new int[H];
        hy = new int[H];
        gx = new int[G];
        gy = new int[G];
        for (int i = 0; i < H; i++) {
            hx[i] = in.nextInt();
            hy[i] = in.nextInt();
        }
        for (int i = 0; i < G; i++) {
            gx[i] = in.nextInt();
            gy[i] = in.nextInt();
        }
        energySpent = new long[H + 1][G + 1][2];
        for (int i = 0; i <= H; i++)
            for (int j = 0; j <= G; j++)
                for (int k = 0; k < 2; k++)
                    energySpent[i][j][k] = -1;

        energySpent[1][0][0] = 0;
        for (int i = 1; i <= H; i++) {
            for (int j = 0; j <= G; j++) {
                if (i == 1 && j == 0)
                    continue;
                long op1 = -1, op2 = -1;
                if (i >= 2 && i - 1 <= H && j <= G && energySpent[i - 1][j][0] != -1)
                    op1 = energySpent[i - 1][j][0] + dis(hx[i - 2], hy[i - 2], hx[i - 1], hy[i - 1]);
                if (i - 1 <= H && j <= G && energySpent[i - 1][j][1] != -1)
                    op2 = energySpent[i - 1][j][1] + dis(gx[j - 1], gy[j - 1], hx[i - 1], hy[i - 1]);
                if (op1 == -1)
                    energySpent[i][j][0] = op2;
                else if (op2 == -1)
                    energySpent[i][j][0] = op1;
                else
                    energySpent[i][j][0] = Math.min(op1, op2);
                op1 = -1;
                op2 = -1;
                if (j - 1 >= 0 && j - 1 <= G && energySpent[i][j - 1][0] != -1)
                    op1 = energySpent[i][j - 1][0] + dis(hx[i - 1], hy[i - 1], gx[j - 1], gy[j - 1]);
                if (j >= 2 && i <= H && j - 1 <= G && energySpent[i][j - 1][1] != -1)
                    op2 = energySpent[i][j - 1][1] + dis(gx[j - 2], gy[j - 2], gx[j - 1], gy[j - 1]);
                if (op1 == -1)
                    energySpent[i][j][1] = op2;
                else if (op2 == -1)
                    energySpent[i][j][1] = op1;
                else
                    energySpent[i][j][1] = Math.min(op1, op2);
            }
        }

        out.println(energySpent[H][G][0]);
    }

    private static long dis(int x1, int y1, int x2, int y2) {
        return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
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
