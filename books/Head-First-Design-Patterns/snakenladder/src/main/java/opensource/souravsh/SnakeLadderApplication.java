package opensource.souravsh;

import opensource.souravsh.model.Game;
import opensource.souravsh.model.Player;

import java.util.Scanner;

public class SnakeLadderApplication {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter board size: ");
        int boardSize = scanner.nextInt();
        System.out.println("Enter Min Dice Value: ");
        int minDiceValue = scanner.nextInt();
        System.out.println("Enter Max Dice Value: ");
        int maxDiceValue = scanner.nextInt();
        System.out.println("Enter number of players: ");
        int numberOfPlayers = scanner.nextInt();
        System.out.println("Enter number of snakes: ");
        int numberOfSnakes = scanner.nextInt();
        System.out.println("Enter number of ladders: ");
        int numberOfLadders = scanner.nextInt();

        Game game = new Game(numberOfSnakes, numberOfLadders, boardSize,
                minDiceValue, maxDiceValue);

        for (int i = 0; i < numberOfPlayers; i++) {
            System.out.println("Player " + (i + 1) + ": ");
            String playerName = scanner.next();
            Player player = new Player(playerName);

            game.addPlayer(player);
        }

        game.playGame();
    }
}
