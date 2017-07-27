import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.Map;

public class cowbasic {

	private static Map<String, Integer> serial = new HashMap<String, Integer>();

	private static int lookingFor;

	private static void solve() {
		setup();
		defineVariables();
		out.println(moo(0, input.length - 1, 1)[lookingFor][0]);
	}

	private static int[][] moo(int start, int finish, int repeats) {
		int[][] expressions = new int[serial.size()][serial.size()];
		for (int i = 0; i < serial.size(); i++)
			expressions[i][i] = 1;
		int currentLocation = start;
		while (currentLocation < finish) {
			if (isVariable(input[currentLocation])) {
				String[] split = input[currentLocation].split(" = ");
				String rightSide = split[1];
				int[] expressionVector = evaluate(rightSide);
				int[] newExpressionVector = apply(expressions, expressionVector);
				expressions[serial.get(split[0].trim())] = newExpressionVector;
			} else {
				int r = Integer.parseInt(input[currentLocation].trim().split(" ")[0]);
				currentLocation++;
				int s = currentLocation;
				int numOpen = 1;
				while (numOpen > 0) {
					if (input[currentLocation].trim().equals("}"))
						numOpen--;
					else if (!isVariable(input[currentLocation]))
						numOpen++;
					currentLocation++;
				}
				int[][] m = moo(s, --currentLocation, r);
				expressions = mult(m, expressions);
			}
			currentLocation++;
		}
		return pow(expressions, repeats);
	}

	private static void print(int[][] m) {
		for (int y = 0; y < m.length; y++) {
			for (int x = 0; x < m.length; x++)
				System.out.print(m[y][x] + " ");
			System.out.println();
		}
	}

	private static int[][] pow(int[][] m, int r) {
		int[][] f = new int[m.length][m.length];
		for (int i = 0; i < f.length; i++)
			f[i][i] = 1;

		int[][][] pows = new int[2 + (int) Math.floor(Math.log(r) / Math.log(2))][m.length][m.length];
		pows[0] = f;
		pows[1] = m;

		for (int i = 2; i < pows.length; i++) {
			pows[i] = mult(pows[i - 1], pows[i - 1]);
		}

		int[][] total = pows[0];
		for (int i = 0; i < pows.length; i++) {
			if (((r >> i) & 1) == 1) {
				total = mult(total, pows[i + 1]);
			}
		}
		return total;
	}

	private static int[][] mult(int[][] m, int[][] n) {
		int[][] f = new int[m.length][n.length];
		for (int row = 0; row < n.length; row++) {
			for (int col = 0; col < n.length; col++) {
				int sum = 0;
				for (int j = 0; j < m.length; j++) {
					sum = add(sum, mult(m[row][j], n[j][col]));
				}
				f[row][col] = sum;
			}
		}
		return f;
	}

	private static int[] apply(int[][] m, int[] v) {
		int[] v2 = new int[v.length];
		for (int i = 0; i < v.length; i++) {
			int sum = 0;
			for (int j = 0; j < v.length; j++) {
				sum = add(sum, mult(v[j], m[j][i]));
			}
			v2[i] = sum;
		}
		return v2;
	}

	private static int[] evaluate(String expression) {
		String[] splitExp = expression.split(" ");
		int[] vector = new int[serial.size()];
		for (String s : splitExp) {
			if (!isOperation(s)) {
				if (isVariable(s)) {
					vector[serial.get(s)] = add(vector[serial.get(s)], 1);
				} else {
					vector[0] = add(vector[0], Integer.parseInt(s));
				}
			}
		}
		return vector;
	}

	private static boolean isOperation(String string) {
		return string.equals("(") || string.equals(")") || string.equals("+");
	}

	private static int add(int a, int b) {
		return (int) (((long) a + (long) b) % 1000000007);
	}

	private static int mult(int a, int b) {
		return (int) (((long) a * (long) b) % 1000000007);
	}

	private static void defineVariables() {
		for (int i = 0; i < input.length; i++) {
			if (isVariable(input[i]))
				addVariable(input[i].trim().split(" ")[0]);
			if (i == input.length - 1)
				lookingFor = serial.get(input[i].split(" ")[1]);
		}
	}

	private static void setup() {
		serial.put("1", 0);
	}

	private static void addVariable(String string) {
		if (!serial.containsKey(string))
			serial.put(string, serial.size());
	}

	private static boolean isVariable(String string) {
		int disToA = (int) (string.trim().charAt(0) - 'a');
		return (disToA < 26 && disToA >= 0);
	}

	private static final String NAME = "cowbasic";

	private static BufferedReader in;
	private static PrintWriter out;

	private static String[] input = null;

	public static void main(String[] args) throws IOException {
		in = new BufferedReader(new FileReader(NAME + ".in"));
		out = new PrintWriter(new FileWriter(NAME + ".out"));
		readInput();
		solve();
		out.close();
		System.exit(0);
	}

	private static void readInput() {
		try {
			StringBuilder sb = new StringBuilder();
			String s = in.readLine();
			while (s != null) {
				sb.append(s);
				sb.append("//");
				s = in.readLine();
			}
			input = sb.toString().split("//");
		} catch (Exception e) {
		}
	}

}
