#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "Player.h"
#include "ComputerPlayer.h"

void saveAchievement(const std::string& nickname, int score) {
    std::ofstream file("achievements.txt");
    if (file.is_open()) {
        file << "Player: " << nickname << ", Score: " << score << std::endl;
        std::cout << "Achievement saved successfully!" << std::endl;
        file.close();
    } else {
        std::cerr << "Error: Unable to open file for saving achievements!" << std::endl;
    }
}

void playNormalGame(Player& player, int startRange, int endRange) {
    srand(time(0));
    int targetNumber = rand() % (endRange - startRange + 1) + startRange;
    int guess;
    int attempts = 0;

    std::cout << "Guess the number between " << startRange << " and " << endRange << "!" << std::endl;

    do {
        std::cout << "Your guess: ";
        std::cin >> guess;
        attempts++;

        if (guess < targetNumber) {
            std::cout << "Too low!" << std::endl;
        } else if (guess > targetNumber) {
            std::cout << "Too high!" << std::endl;
        } else {
            player.setNewScore(attempts);
            std::cout << "Congratulations, you guessed it in " << attempts << " attempts!" << std::endl;
        }
    } while (guess != targetNumber);
}

void playReverseGame(Player& player, int startRange, int endRange) {
    srand(time(0));
    int targetNumber;
    int lowerBound = startRange;
    int upperBound = endRange;
    int guess;
    int attempts = 0;

    std::cout << "Choose a number between " << startRange << " and " << endRange << ", and I will guess it!" << std::endl;

    do {
        targetNumber = (lowerBound + upperBound) / 2;
        std::cout << "My guess: " << targetNumber << std::endl;
        std::cout << "1. Too low" << std::endl;
        std::cout << "2. Too high" << std::endl;
        std::cout << "3. You got it!" << std::endl;
        std::cout << "Your choice: ";
        std::cin >> guess;
        attempts++;

        if (guess == 1) {
            lowerBound = targetNumber + 1;
        } else if (guess == 2) {
            upperBound = targetNumber - 1;
        } else if (guess == 3) {
            std::cout << "Hooray! I got it!" << std::endl;
            player.setNewScore(attempts);
        } else {
            std::cout << "Invalid choice, please try again." << std::endl;
        }
    } while (guess != 3);
}

void playMixedGame(Player& player, int startRange, int endRange) {
    int maxNumber = endRange;
    std::srand(std::time(nullptr));

    std::cout << "Mixed gameplay - taking turns guessing with the program!" << std::endl;

    char choice;
    do {
        int targetNumber = std::rand() % (maxNumber - startRange + 1) + startRange;
        int lowerBound = startRange;
        int upperBound = endRange;
        int guess;
        int attempts = 0;
        bool playerTurn = (std::rand() % 2) == 0;

        while (true) {
            if (playerTurn) {
                std::cout << "Your guess: ";
                std::cin >> guess;
                attempts++;

                if (guess < lowerBound || guess > upperBound) {
                    std::cout << "Number out of range!" << std::endl;
                    continue;
                }

                if (guess < targetNumber) {
                    std::cout << "Too low!" << std::endl;
                } else if (guess > targetNumber) {
                    std::cout << "Too high!" << std::endl;
                } else {
                    std::cout << "Congratulations! You guessed it in " << attempts << " attempts." << std::endl;
                    player.setNewScore(attempts);
                    break;
                }

                playerTurn = false;
            } else {
                guess = (lowerBound + upperBound) / 2;
                std::cout << "My guess: " << guess << std::endl;
                attempts++;

                if (guess == targetNumber) {
                    std::cout << "Hooray! I got it!" << std::endl;
                    player.setNewScore(attempts);
                    break;
                } else if (guess < targetNumber) {
                    std::cout << "Too low!" << std::endl;
                    lowerBound = guess + 1;
                } else {
                    std::cout << "Too high!" << std::endl;
                    upperBound = guess - 1;
                }

                playerTurn = true;
            }
        }

        std::cout << "Do you want to play again? (Y/N): ";
        std::cin >> choice;
    } while (std::toupper(choice) == 'Y');
}

void setupTournament(std::vector<Player>& players, int startRange, int endRange) {
    int numRounds = static_cast<int>(std::log2(players.size())) + 1;

    std::cout << "Setting up tournament with " << players.size() << " players in " << numRounds << " rounds." << std::endl;

    for (int round = 1; round <= numRounds; ++round) {
        std::cout << "Round " << round << " of " << numRounds << ":" << std::endl;

        std::vector<Player> winners;

        for (size_t i = 0; i < players.size(); i += 2) {
            Player& player1 = players[i];
            Player& player2 = (i + 1 < players.size()) ? players[i + 1] : players[i];

            char choice;
            std::cout << "Player " << player1.getNickname() << " vs Player " << player2.getNickname() << std::endl;
            std::cout << "Choose game mode:" << std::endl;
            std::cout << "1. Normal (player guesses the number)" << std::endl;
            std::cout << "2. Reverse (program guesses the number)" << std::endl;
            std::cout << "3. Mixed (player and program take turns guessing)" << std::endl;
            std::cout << "Your choice: ";
            std::cin >> choice;

            switch (choice) {
                case '1':
                    playNormalGame(player1, startRange, endRange);
                    playNormalGame(player2, startRange, endRange);
                    break;
                case '2':
                    playReverseGame(player1, startRange, endRange);
                    playReverseGame(player2, startRange, endRange);
                    break;
                case '3':
                    playMixedGame(player1, startRange, endRange);
                    playMixedGame(player2, startRange, endRange);
                    break;
                default:
                    std::cout << "Invalid choice!" << std::endl;
                    break;
            }

            if (player1.getBestScore() < player2.getBestScore()) {
                winners.push_back(player1);
            } else {
                winners.push_back(player2);
            }
        }

        players = winners;

        std::cout << "Winners of round " << round << ":" << std::endl;
        for (const auto& winner : winners) {
            std::cout << winner.getNickname() << " with " << winner.getBestScore() << " attempts." << std::endl;
        }
    }

    auto champion = std::min_element(players.begin(), players.end(),
                                     [](const Player& p1, const Player& p2) { return p1.getBestScore() < p2.getBestScore(); });

    if (champion != players.end()) {
        champion->setChampion(true);
        std::cout << "The champion of the tournament is: " << champion->getNickname() << " with " << champion->getBestScore() << " attempts!" << std::endl;
    } else {
        std::cout << "No players found or no games played in the tournament." << std::endl;
    }
}

int main() {
    std::string nickname;
    std::cout << "Enter your nickname: ";
    std::cin >> nickname;

    Player player(nickname);

    char multiChoice;
    std::cout << "Multiplayer? (Y/N): ";
    std::cin >> multiChoice;

    if (std::toupper(multiChoice) == 'Y') {
        int numPlayers;
        std::cout << "Enter number of players: ";
        std::cin >> numPlayers;

        std::vector<Player> players;
        players.push_back(player);

        for (int i = 1; i < numPlayers; ++i) {
            std::string playerName;
            std::cout << "Enter name for player " << i + 1 << ": ";
            std::cin >> playerName;
            players.emplace_back(playerName);
        }

        int difficulty;
        std::cout << "Choose difficulty level:" << std::endl;
        std::cout << "1. Easy (0-100)" << std::endl;
        std::cout << "2. Medium (0-1000)" << std::endl;
        std::cout << "3. Hard (0-10000)" << std::endl;
        std::cout << "4. Custom" << std::endl;
        std::cout << "Your choice: ";
        std::cin >> difficulty;

        int startRange, endRange;

        switch (difficulty) {
            case 1:
                startRange = 0;
                endRange = 100;
                break;
            case 2:
                startRange = 0;
                endRange = 1000;
                break;
            case 3:
                startRange = 0;
                endRange = 10000;
                break;
            case 4:
                std::cout << "Enter start of range: ";
                std::cin >> startRange;
                std::cout << "Enter end of range: ";
                std::cin >> endRange;
                break;
            default:
                std::cout << "Invalid choice!" << std::endl;
                return 1;
        }

        for (auto& currentPlayer : players) {
            char choice;
            std::cout << "Player " << currentPlayer.getNickname() << ", it's your turn!" << std::endl;
            std::cout << "Choose game mode:" << std::endl;
            std::cout << "1. Normal (player guesses the number)" << std::endl;
            std::cout << "2. Reverse (program guesses the number)" << std::endl;
            std::cout << "3. Mixed (player and program take turns guessing)" << std::endl;
            std::cout << "Your choice: ";
            std::cin >> choice;

            switch (choice) {
                case '1':
                    playNormalGame(currentPlayer, startRange, endRange);
                    break;
                case '2':
                    playReverseGame(currentPlayer, startRange, endRange);
                    break;
                case '3':
                    playMixedGame(currentPlayer, startRange, endRange);
                    break;
                default:
                    std::cout << "Invalid choice!" << std::endl;
                    break;
            }
        }

        auto leader = std::min_element(players.begin(), players.end(),
                                       [](const Player& p1, const Player& p2) { return p1.getBestScore() < p2.getBestScore(); });

        if (leader != players.end()) {
            leader->setLeader(true);
            std::cout << "The leader is: " << leader->getNickname() << " with " << leader->getBestScore() << " attempts!" << std::endl;
        } else {
            std::cout << "No players found or no games played." << std::endl;
        }

        std::cout << "Setting up tournament for the players..." << std::endl;
        setupTournament(players, startRange, endRange);

    } else {
        char choice;
        int difficulty;
        do {
            std::cout << "Welcome, " << player.getNickname() << "! Your best score is " << player.getBestScore() << " attempts." << std::endl;
            std::cout << "Choose difficulty level:" << std::endl;
            std::cout << "1. Easy (0-100)" << std::endl;
            std::cout << "2. Medium (0-1000)" << std::endl;
            std::cout << "3. Hard (0-10000)" << std::endl;
            std::cout << "4. Custom" << std::endl;
            std::cout << "5. Exit" << std::endl;
            std::cout << "Your choice: ";
            std::cin >> difficulty;

            int startRange, endRange;

            switch (difficulty) {
                case 1:
                    startRange = 0;
                    endRange = 100;
                    break;
                case 2:
                    startRange = 0;
                    endRange = 1000;
                    break;
                case 3:
                    startRange = 0;
                    endRange = 10000;
                    break;
                case 4:
                    std::cout << "Enter start of range: ";
                    std::cin >> startRange;
                    std::cout << "Enter end of range: ";
                    std::cin >> endRange;
                    break;
                case 5:
                    std::cout << "Thank you for playing!" << std::endl;
                    return 0;
                default:
                    std::cout << "Invalid choice!" << std::endl;
                    continue;
            }

            std::cout << "Choose game mode:" << std::endl;
            std::cout << "1. Normal (player guesses the number)" << std::endl;
            std::cout << "2. Reverse (program guesses the number)" << std::endl;
            std::cout << "3. Mixed (player and program take turns guessing)" << std::endl;
            std::cout << "4. Exit" << std::endl;
            std::cout << "Your choice: ";
            std::cin >> choice;

            switch (choice) {
                case '1':
                    playNormalGame(player, startRange, endRange);
                    break;
                case '2':
                    playReverseGame(player, startRange, endRange);
                    break;
                case '3':
                    playMixedGame(player, startRange, endRange);
                    break;
                case '4':
                    std::cout << "Thank you for playing!" << std::endl;
                    break;
                default:
                    std::cout << "Invalid choice!" << std::endl;
                    break;
            }
        } while (choice != '4');
    }

    return 0;
}

