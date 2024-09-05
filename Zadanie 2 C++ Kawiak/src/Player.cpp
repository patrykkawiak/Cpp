#include "Player.h"
#include <fstream>
#include <limits>

Player::Player(const std::string& nickname) : nickname(nickname), bestScore(9999) {
    loadBestScore();
}

Player::~Player() {
    saveBestScore();
}

void Player::loadBestScore() {
    std::ifstream file(getFileName());
    if (file.is_open()) {
        file >> bestScore;
        file.close();
    }
}

void Player::saveBestScore() {
    std::ofstream file(getFileName());
    if (file.is_open()) {
        file << bestScore;
        file.close();
    }
}

void Player::setNewScore(int score) {
    if (score < bestScore || bestScore == 0) {
        bestScore = score;
    }
}

void Player::saveGameHistory(int score) const {
    std::ofstream file(getHistoryFileName(), std::ios::app);
    if (file.is_open()) {
        file << "Score: " << score << std::endl;
        file.close();
    }
}


int Player::getBestScore() const {
    return bestScore;
}

const std::string& Player::getNickname() const {
    return nickname;
}

std::string Player::getFileName() const {
    return nickname + ".txt";
}

std::string Player::getHistoryFileName() const {
    return nickname + "_history.txt";
}
