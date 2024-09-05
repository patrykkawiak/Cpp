#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "Player.h"

void saveAchievement(const std::string& nickname, int score) {
    std::ofstream file("achievements.txt", std::ios::app);
    if (file.is_open()) {
        file << "Player: " << nickname << ", Score: " << score << std::endl;
        file.close();
    } else {
        std::cerr << "Unable to open file for saving achievements!" << std::endl;
    }
}

void playNormalGame(Player& player, int difficulty) {
    srand(time(0));
    int maxNumber;
    if (difficulty == 1)
        maxNumber = 100;
    else if (difficulty == 2)
        maxNumber = 1000;
    else
        maxNumber = 10000;

    int targetNumber = rand() % (maxNumber + 1);
    int guess;
    int attempts = 0;

    std::cout << "Zgadnij numer od 0 do " << maxNumber << "!" << std::endl;

    do {
        std::cout << "Twoj typ: ";
        std::cin >> guess;
        attempts++;

        if (guess < targetNumber) {
            std::cout << "Za malo!" << std::endl;
        } else if (guess > targetNumber) {
            std::cout << "Za duzo!" << std::endl;
        } else {
            player.setNewScore(attempts);
            saveAchievement(player.getNickname(), attempts);
        }
    } while (guess != targetNumber);
}

void playReverseGame(Player& player, int difficulty) {
    srand(time(0));
    int targetNumber;
    int lowerBound = 0;
    int maxNumber;
    if (difficulty == 1)
        maxNumber = 100;
    else if (difficulty == 2)
        maxNumber = 1000;
    else
        maxNumber = 10000;

    int upperBound = maxNumber;
    int guess;
    int attempts = 0;

    std::cout << "Wybierz liczbe od 0 do " << maxNumber << ", a ja ja zgadne!" << std::endl;

    do {
        targetNumber = (lowerBound + upperBound) / 2;
        std::cout << "Zgaduje: " << targetNumber << std::endl;
        std::cout << "1. Za malo" << std::endl;
        std::cout << "2. Za duzo" << std::endl;
        std::cout << "3. Zgadles!" << std::endl;
        std::cout << "Twoj wybor: ";
        std::cin >> guess;
        attempts++;

        if (guess == 1) {
            lowerBound = targetNumber + 1;
        } else if (guess == 2) {
            upperBound = targetNumber - 1;
        } else if (guess == 3) {
            std::cout << "Hurra! Udalo sie!" << std::endl;
            player.setNewScore(attempts);
            saveAchievement(player.getNickname(), attempts);
        } else {
            std::cout << "Nieprawidlowy wybor, sprobuj ponownie." << std::endl;
        }
    } while (guess != 3);
}

void playMixedGame(Player& player, int difficulty) {
    int maxNumber;
    if (difficulty == 1)
        maxNumber = 100;
    else if (difficulty == 2)
        maxNumber = 1000;
    else
        maxNumber = 10000;

    std::srand(std::time(nullptr));

    std::cout << "Rozgrywka mieszana - na zmiane zgadujesz z programem!" << std::endl;

    char choice;
    do {
        int targetNumber = std::rand() % (maxNumber + 1);
        int lowerBound = 0;
        int upperBound = maxNumber;
        int guess;
        int attempts = 0;
        bool playerTurn = (std::rand() % 2) == 0;

        while (true) {
            if (playerTurn) {
                std::cout << "Twoj typ: ";
                std::cin >> guess;
                attempts++;

                if (guess < lowerBound || guess > upperBound) {
                    std::cout << "Liczba spoza zakresu!" << std::endl;
                    continue;
                }

                if (guess < targetNumber) {
                    std::cout << "Za malo!" << std::endl;
                } else if (guess > targetNumber) {
                    std::cout << "Za duzo!" << std::endl;
                } else {
                    std::cout << "Super! Zgadles za " << attempts << " proba." << std::endl;

                    player.saveGameHistory(player.getBestScore());

                    break;
                }

                playerTurn = false;
            } else {
                guess = (lowerBound + upperBound) / 2;
                std::cout << "Zgaduje: " << guess << std::endl;
                attempts++;

                if (guess == targetNumber) {
                    std::cout << "Hurra! Udalo sie!" << std::endl;
                    player.setNewScore(attempts);
                    break;
                } else if (guess < targetNumber) {
                    std::cout << "Za malo!" << std::endl;
                    lowerBound = guess + 1;
                } else {
                    std::cout << "Za duzo!" << std::endl;
                    upperBound = guess - 1;
                }

                playerTurn = true;
            }
        }

        std::cout << "Czy chcesz zagrac jeszcze raz? (T/N): ";
        std::cin >> choice;
    } while (std::toupper(choice) == 'T');
}



int main() {
    std::string nickname;
    std::cout << "Wpisz swoj nick: ";
    std::cin >> nickname;

    Player player(nickname);

    char choice;
    int difficulty;
    do {
        std::cout << "Witaj, " << player.getNickname() << "! Twoj najlepszy wynik to " << player.getBestScore() << " prob." << std::endl;
        std::cout << "Wybierz poziom trudnosci:" << std::endl;
        std::cout << "1. Latwy (0-100)" << std::endl;
        std::cout << "2. Sredni (0-1000)" << std::endl;
        std::cout << "3. Trudny (0-10000)" << std::endl;
        std::cout << "4. Wyjscie" << std::endl;
        std::cout << "Twoj wybor: ";
        std::cin >> difficulty;

        switch (difficulty) {
            case 1:
                std::cout << "Wybrano poziom latwy." << std::endl;
                break;
            case 2:
                std::cout << "Wybrano poziom sredni." << std::endl;
                break;
            case 3:
                std::cout << "Wybrano poziom trudny." << std::endl;
                break;
            case 4:
                std::cout << "Dzieki za gre!" << std::endl;
                return 0;
            default:
                std::cout << "Nieprawidlowy wybor!" << std::endl;
                continue;
        }

        std::cout << "Wybierz rodzaj rozgrywki:" << std::endl;
        std::cout << "1. Normalna (gracz zgaduje liczbe)" << std::endl;
        std::cout << "2. Odwrotna (program zgaduje liczbe)" << std::endl;
        std::cout << "3. Mieszana (gracz i program na zmiane zgaduja)" << std::endl;
        std::cout << "4. Wyjscie" << std::endl;
        std::cout << "Twoj wybor: ";
        std::cin >> choice;

        switch (choice) {
            case '1':
                playNormalGame(player, difficulty);
                break;
            case '2':
                playReverseGame(player, difficulty);
                break;
            case '3':
                playMixedGame(player, difficulty);
                break;
            case '4':
                std::cout << "Dzieki za gre!" << std::endl;
                break;
            default:
                std::cout << "Nieprawidlowy wybor!" << std::endl;
                break;
        }
    } while (choice != '4');

    return 0;
}
