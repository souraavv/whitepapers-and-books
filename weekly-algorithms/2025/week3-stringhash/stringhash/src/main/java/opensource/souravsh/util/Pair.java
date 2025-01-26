package opensource.souravsh.util;


public class Pair<T, U> {
    public final T first;
    public final U second;
    public Pair(T first, U second) {
        this.first = first;
        this.second = second;
    }

    public T getFirst() {
        return first;
    }

    public U getSecond() {
        return second;
    }

}
