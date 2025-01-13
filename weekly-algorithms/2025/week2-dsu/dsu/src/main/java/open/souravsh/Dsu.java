package open.souravsh;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Dsu {
    private final List<Integer> parent;
    private final List<Integer> size;
    int n;
    public Dsu(int n) {
        this.n = n;
        this.parent = new ArrayList<Integer>(Collections.nCopies(n, -1));
        this.size = new ArrayList<Integer>(Collections.nCopies(n, 1));
    }

    public boolean isSameSet(int u, int v) {
        return find(u) == find(v);
    }

    public int find(int u) {
        return parent.get(u) == -1 ? u : find(parent.get(u));
    }

    public int getComponentSize(int u) {
        return size.get(u);
    }

    public boolean join(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) {
            return false;
        }
        if (getComponentSize(u) < getComponentSize(v)) {
            swap(u, v);
        }
        parent.set(v, u);
        size.set(u, size.get(v) + size.get(u));
        return true;
    }

    private void swap(int u, int v) {
        int temp = u;
        u = v;
        v = temp;
    }

    public void printState() {
        System.out.println("State of Parent array");
        for (int i = 0; i < parent.size(); i++) {
            System.out.print(i + " : " + parent.get(i) + ", ");
        }
        System.out.println();
        System.out.println("State of Size array");
        for (int i = 0; i < size.size(); i++) {
            System.out.print(i + " : " + size.get(i) + ", ");
        }
        System.out.println();
    }
}
