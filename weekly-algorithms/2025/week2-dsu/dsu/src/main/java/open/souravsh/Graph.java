package open.souravsh;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class Graph {
    private final int nodes;
    private final int edges;
    private final List<List<Integer>> adjacencyList;

    public Graph(int nodes, int edges) {
        this.nodes = nodes;
        this.edges = edges;
        adjacencyList = new ArrayList<List<Integer>>();
        for (int i = 0; i < nodes; i++) {
            adjacencyList.add(new LinkedList<Integer>());
        }
    }

    public void addBiEdge(int v, int w) {
        adjacencyList.get(v).add(w);
        adjacencyList.get(w).add(v);
    }

    public void addUniEdge(int v, int w) {
        adjacencyList.get(v).add(w);
    }

    public void printGraph() {
        for (int i = 0; i < nodes; i++) {
            for (int j = 0; j < edges; j++) {
                System.out.print(adjacencyList.get(i).get(j) + " ");
            }
            System.out.println();
        }
    }

    public List<List<Integer>> getAdjacencyList() {
        return adjacencyList;
    }

    public List<Integer> getAdjacentNodes(int v) {
        return adjacencyList.get(v);
    }


}
