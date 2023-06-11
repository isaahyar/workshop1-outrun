#ifndef OUTRUN_SCORE_HPP
#define OUTRUN_SCORE_HPP

#include <string>
#include <vector>


struct Score {
    unsigned long score;
    std::string name;
    int minutes;
    int secs;
    int cents_second;

    
    Score(unsigned long score, const std::string &name, int minutes, int secs, int centsSecond);
};


std::vector<Score> getGlobalScores();


int isNewRecord(const std::vector<Score> &globalScores, unsigned long score);


bool saveNewRecord(const std::vector<Score> &globalScores, const Score &newRecord);

#endif //OUTRUN_SCORE_HPP
