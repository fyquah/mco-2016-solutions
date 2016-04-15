import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class Solution {
  private static Reader input = new Reader(System.in);
  private static PrintWriter output = new PrintWriter(new BufferedOutputStream(System.out));

  private static final int MAXN = 500_005;
  private static long dist[][] = new long[2][MAXN];
  private static ArrayList<ArrayList<Pair>> adjList = new ArrayList<>();

  public static void main(String[] args) {
    Arrays.fill(dist[0], -1);
    Arrays.fill(dist[1], -1);

    int N = input.nextInt();
    int M = input.nextInt();
    int A = input.nextInt();
    int B = input.nextInt();

    for (int i = 0; i <= N; i++) {
      adjList.add(new ArrayList<>());
    }

    for (int i = 0; i < M; i++) {
      int u, v;
      long w;
      u = input.nextInt();
      v = input.nextInt();
      w = input.nextLong();

      adjList.get(u).add(new Pair(w, v));
      adjList.get(v).add(new Pair(w, u));
    }

    dijkstra(A, 0);
    dijkstra(B, 1);

    long D = -1;

    for (int i = 1; i <= N; i++) {
      if (dist[0][i] != -1 && dist[1][i] != -1) {
        if (D == -1 || D > Math.max(dist[0][i], dist[1][i])) {
          D = Math.max(dist[0][i], dist[1][i]);
        }
      }
    }

    output.println(D);
    output.flush();
    output.close();
  }

  private static void dijkstra(int start, int mode) {
    dist[mode][start] = 0;
    PriorityQueue<Pair> pq = new PriorityQueue<>();
    pq.offer(new Pair(0, start));

    while (pq.size() != 0) {
      Pair front = pq.poll();

      long d = front.first;
      int  u = front.second;

      if (d > dist[mode][u]) {
        continue;
      }

      for (int i = 0; i < adjList.get(u).size(); i++) {
        Pair next = adjList.get(u).get(i);
        long vd = next.first;
        int  vv = next.second;

        if (dist[mode][vv] == -1 || dist[mode][vv] > dist[mode][u] + vd) {
          dist[mode][vv] = dist[mode][u] + vd;
          pq.offer(new Pair(dist[mode][vv], vv));
        }
      }
    }
  }

  private static class Pair implements Comparable<Pair> {
    private long first;
    private int second;

    private Pair(long first, int second) {
      this.first = first;
      this.second = second;
    }

    @Override
    public int compareTo(Pair other) {
      if (this.first != other.first) {
        return Long.compare(this.first, other.first);
      } else {
        return Integer.compare(this.second, other.second);
      }
    }
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

    long nextLong() {
      return Long.parseLong(next());
    }
  }
}
