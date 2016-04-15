import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class Solution {
  private static Reader input = new Reader(System.in);
  private static PrintWriter output = new PrintWriter(new BufferedOutputStream(System.out));

  private static final int MAXN = 1_000_005;

  public static void main(String[] args) {
    int a[] = new int[MAXN];
    int N = input.nextInt();

    for (int i = 1; i <= N; i++) {
      a[i] = input.nextInt();
    }

    int l, r, answer = 0;

    for (l = 1, r = 2; r <= N; r++) {
      if (a[r] >= a[l]) {
        answer = Math.max(answer, r-l);
        l = r;
      }
    }

    for (r = N, l = N-1; l > 0; l--) {
      if (a[l] >= a[r]) {
        answer = Math.max(answer, r-l);
        r = l;
      }
    }

    output.println(answer);
    output.flush();
    output.close();
  }

  private static class Reader {
    BufferedReader reader;
    StringTokenizer tokenizer;

    Reader(InputStream input) {
      reader = new BufferedReader(new InputStreamReader(input));
    }

    String next() {
      while (tokenizer == null || !tokenizer.hasMoreTokens()) {
        try {
          tokenizer = new StringTokenizer(reader.readLine());
        } catch (IOException e) {
          e.printStackTrace();
        }
      }

      return tokenizer.nextToken();
    }

    int nextInt() {
      return Integer.parseInt(next());
    }
  }
}
