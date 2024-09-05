// Player.h

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
    void setLeader(bool isLeader);
    void setChampion(bool isChampion);
    void resetBestScore();

private:
    std::string nickname;
    int bestScore;
    bool leader;
    bool champion;
    std::string getFileName() const;
    std::string getHistoryFileName() const;
};

#endif
