#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
public:
    Player(const std::string& nickname);
    virtual ~Player();
    void saveGameHistory(int score) const;
    void loadBestScore();
    void saveBestScore();
    void setNewScore(int score);
    int getBestScore() const;
    const std::string& getNickname() const;

private:
    std::string nickname;
    int bestScore;
    std::string getFileName() const;
    std::string getHistoryFileName() const;
};

#endif
