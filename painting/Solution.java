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

  public static void main(String[] args) {
    int R[][] = new int[1005][1005];
    int C[][] = new int[1005][1005];

    int N = input.nextInt();
    int M = input.nextInt();
    int Q = input.nextInt();

    for (int i = 0; i < Q; i++) {
      int op = input.nextInt();
      int x  = input.nextInt();
      int y  = input.nextInt();
      int z  = input.nextInt();

      if (op != 0) {
        C[y][x]++;
        C[z+1][x]--;
      } else {
        R[x][y]++;
        R[x][z+1]--;
      }
    }

    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= M; j++) {
        R[i][j] += R[i][j-1];
        C[j][i] += C[j-1][i];
      }
    }

    int maxNum = 0, cnt = 0;
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= M; j++) {
        if (R[i][j] + C[i][j] == maxNum) {
          cnt++;
        } else if (R[i][j] + C[i][j] > maxNum) {
          maxNum = R[i][j] + C[i][j];
          cnt = 1;
        }
      }
    }

    long answer = (long) maxNum * (long) cnt;
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
