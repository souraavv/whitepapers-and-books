package opensource.souravsh.model;

import lombok.extern.slf4j.Slf4j;

import java.util.*;


public class Game {
    private final int numberOfSnakes;
    private final int numberOfLadders;

    private final List<Ladder> ladders;
    private final List<Snake> snakes;
    private final Queue<Player> players;

    private final Board board;
    private final Dice dice;


    public Game(int numberOfSnakes, int numberOfLadders, int boardSize,
                int diceMinValue, int diceMaxValue) {
        this.numberOfSnakes = numberOfSnakes;
        this.numberOfLadders = numberOfLadders;
        this.ladders = new ArrayList<>(numberOfSnakes);
        this.snakes = new ArrayList<>(numberOfLadders);
        // round-robin fashion
        this.players = new ArrayDeque<>();

        board = new Board(boardSize);
        dice = new Dice(diceMinValue, diceMaxValue);

        initBoard();

    }

    public void initBoard() {
        Random random = new Random();
        Set<String> snakePositions = new HashSet<>();
        Set<String> ladderPositions = new HashSet<>();
        int boardSize = this.board.getBoardSize();

        while (snakePositions.size() < this.numberOfSnakes) {
            int head = 1 + random.nextInt(boardSize);
            int tail = 1 + random.nextInt(boardSize);
            if (head > tail) {
                String snakePosition = String.format("%s-%s", head, tail);
                if (snakePositions.add(snakePosition)) {
                    this.snakes.add(new Snake(head, tail));
                }

            }
        }

        while (ladderPositions.size() < this.numberOfLadders) {
            int start = 1 + random.nextInt(boardSize);
            int end = 1 + random.nextInt(boardSize);
            if (start > end) {
                String ladderPosition = String.format("%s-%s", start, end);
                if (ladderPositions.add(ladderPosition)) {
                    this.ladders.add(new Ladder(start, end));
                }
            }
        }
    }

    public void addPlayer(Player player) {
        players.add(player);
    }

    public void playGame() {
        while (true) {
            Player player = players.poll();
            if (player != null) {
                int val = dice.roll();

                int newPosition = getNewPosition(player.getPosition() + val);
                if (newPosition > this.board.getEnd()) {
                    players.offer(player);
                } else {
                    player.setPosition(newPosition);
                    if (player.getPosition() == board.getEnd()) {
                        player.setWon(true);
                        System.out.println("Player " + player.getName() + " won!");
                    } else {
                        players.offer(player);
                    }
                }
            }
            if (players.size() < 2) {
                break;
            }
        }
    }

    private int getNewPosition(int newPosition) {
        for (Snake snake: this.snakes) {
            if (newPosition == snake.getHead()) {
                return snake.getTail();
            }
        }

        for (Ladder ladder: this.ladders) {
            if (newPosition == ladder.getEnd()) {
                return ladder.getStart();
            }
        }
        return newPosition;

    }

}
