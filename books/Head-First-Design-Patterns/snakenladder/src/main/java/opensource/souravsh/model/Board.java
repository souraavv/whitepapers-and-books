package opensource.souravsh.model;

import lombok.Getter;

@Getter
public class Board {
    private int boardSize;
    private final int start;
    private final int end;

    public Board(int boardSize) {
        this.start = 1;
        this.end = start + boardSize - 1;
        this.boardSize = boardSize;
    }
}
