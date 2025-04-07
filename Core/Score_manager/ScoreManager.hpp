/*
** EPITECH PROJECT, 2024
** Core_Arcade
** File description:
** ScoreManager.hpp
*/

#pragma once

#include <string>
#include <map>
#include <vector>
#include <utility>

class ScoreManager {
public:
    ScoreManager();
    ~ScoreManager();

    void addScore(const std::string& playerName, const std::string& gameName, int score);
    int getHighScore(const std::string& playerName, const std::string& gameName) const;
    
    void saveScores();
    void loadScores();
    
    std::map<std::string, int> getGameScores(const std::string& gameName) const;
    std::map<std::string, int> getPlayerScores(const std::string& playerName) const;

    std::vector<std::pair<std::string, int>> getFormattedScores(const std::string& gameName) const;

private:
    // Scores: game -> player -> score
    std::map<std::string, std::map<std::string, int>> scores;

    const std::string SCORE_FILE = "arcade_scores.dat";
};