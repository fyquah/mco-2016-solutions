import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.StringTokenizer;

public class Solution {
  private static Reader input = new Reader(System.in);
  private static PrintWriter output = new PrintWriter(new BufferedOutputStream(System.out));

  public static void main(String[] args) {
    ArrayList<Line> v = new ArrayList<Line>();

    int N = input.nextInt();

    for (int i = 0; i < N; i++) {
      int a = input.nextInt();
      int b = input.nextInt();

      v.add(new Line(b, -a * b));
    }

    Collections.sort(v, (Line a, Line b) -> {
      return a.m == b.m ? Long.compare(a.c, b.c) : Long.compare(a.m, b.m);
    });

    ConvexHull h = new ConvexHull();

    for (int i = 0; i < N; i++) {
      if (i + 1 < N && v.get(i).m == v.get(i + 1).m) {
        continue;
      }
      h.pushLine(v.get(i));
    }

    output.println(h.query(N));
    output.flush();
    output.close();
  }

  private static class Line {
    private long m, c;

    private Line() {
      this.m = this.c = 0;
    }

    private Line(long m, long c) {
      this.m = m;
      this.c = c;
    }

    private double xIntersect(Line other) {
      return (double) (other.c - this.c) / (double) (this.m - other.m);
    }

    private double pass(double x) {
      return this.m * x + this.c;
    }
  }

  private static class ConvexHull {
    private ArrayDeque<Line> d = new ArrayDeque<Line>();

    private boolean lower(Line newLine) {
      if (d.size() < 2) {
        return false;
      }

      Iterator<Line> it = d.descendingIterator();
      Line last = it.next();
      Line cmp  = it.next();

      return cmp.xIntersect(newLine) <= cmp.xIntersect(last);
    }

    private void pushLine(Line l) {
      while (lower(l)) {
        d.pollLast();
      }
      d.offerLast(l);
    }

    private int query(int N) {
      int bad = N - d.size();


      while (d.size() > 1) {
        Iterator<Line> it = d.iterator();
        Line first = it.next();
        Line second = it.next();

        if (first.pass(first.xIntersect(second)) > (double) 0) {
          break;
        }

        d.pollFirst();
        bad++;
      }

      Line[] content = new Line[d.size()];
      d.toArray(content);

      for (int i = 1; i + 1 < content.length; i++) {
        if ((long)content[i].xIntersect(content[i-1]) == (long)content[i].xIntersect(content[i+1])) {
          bad++;
        }
      }

      return bad;
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
  }
}
