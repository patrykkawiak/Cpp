#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Player.h"

void playGame(Player& player) {
    srand(time(0));
    int targetNumber = rand() % 101;
    int guess;
    int attempts = 0;

    std::cout << "Zgadnij numer od 0 do 100!" << std::endl;

    do {
        std::cout << "Twoj typ: ";
        std::cin >> guess;
        attempts++;

        if (guess < targetNumber) {
            std::cout << "Za malo!" << std::endl;
        } else if (guess > targetNumber) {
            std::cout << "Za duzo!" << std::endl;
        } else {
            std::cout << "Brawo! Zgadles za " << attempts << " razem." << std::endl;
            player.setNewScore(attempts);
        }
    } while (guess != targetNumber);
}

int main() {
    std::string nickname;

    std::cout << "Podaj swoj nick: ";
    std::cin >> nickname;

    Player player(nickname);

    char choice;
    do {
        if (player.getBestScore() <= 0) {
            std::cout << "Jeszcze nie grales!" << std::endl;
        } else {
            std::cout << "Witaj, " << player.getNickname() << "! Twoj najlepszy wynik to " << player.getBestScore() << " prob." << std::endl;
        }
        std::cout << "Czy chcesz zagrac? (t/n): ";
        std::cin >> choice;

        if (choice == 't' || choice == 'T') {
            playGame(player);
        }
    } while (choice == 't' || choice == 'T');

    std::cout << "Dzieki za gre!" << std::endl;
    return 0;
}
