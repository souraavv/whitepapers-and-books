package open.souravsh;

public class Main {
    public static void main(String[] args) {
        int n = 5;
        int m = 6;
        Dsu dsu = new Dsu(n);
        Graph g = new Graph(n, m);
        g.addUniEdge(0, 1);
        g.addUniEdge(0, 2);
        g.addUniEdge(1, 2);
        g.addUniEdge(2, 3);
        g.addUniEdge(3, 4);
        g.addUniEdge(4, 2);

        for (int u = 0; u < n; ++u) {
            for (int v : g.getAdjacentNodes(u)) {
                if (dsu.join(u, v)) {
                    dsu.printState();
                } else {
                    System.out.println("Already same set - Skipping");
                }

            }
        }

    }
}