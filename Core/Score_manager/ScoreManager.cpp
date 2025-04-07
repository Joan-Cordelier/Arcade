/*
** EPITECH PROJECT, 2024
** Core_Arcade
** File description:
** ScoreManager.cpp
*/

#include "ScoreManager.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

ScoreManager::ScoreManager()
{
    loadScores();
}

ScoreManager::~ScoreManager()
{
    saveScores();
}

void ScoreManager::addScore(const std::string& playerName, const std::string& gameName, int score)
{
    if (scores[gameName][playerName] < score) {
        scores[gameName][playerName] = score;
        saveScores();
    }
}

int ScoreManager::getHighScore(const std::string& playerName, const std::string& gameName) const
{
    auto gameIt = scores.find(gameName);
    if (gameIt != scores.end()) {
        auto playerIt = gameIt->second.find(playerName);
        if (playerIt != gameIt->second.end()) {
            return playerIt->second;
        }
    }
    return 0;
}

void ScoreManager::saveScores()
{
    std::ofstream file(SCORE_FILE);
    
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open score file for writing: " << SCORE_FILE << std::endl;
        return;
    }
    
    for (const auto& [gameName, players] : scores) {
        for (const auto& [playerName, score] : players) {
            file << gameName << "," << playerName << "," << score << "\n";
        }
    }
    
    file.close();
}

void ScoreManager::loadScores()
{
    std::ifstream file(SCORE_FILE);
    
    if (!file.is_open()) {
        std::ofstream newFile(SCORE_FILE);
        if (!newFile.is_open()) {
            std::cerr << "Error: Unable to create score file: " << SCORE_FILE << std::endl;
        } else {
            newFile.close();
        }
        return;
    }
    
    scores.clear();
    
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string gameName, playerName;
        int score;
        
        std::getline(iss, gameName, ',');
        std::getline(iss, playerName, ',');
        iss >> score;
        
        if (!gameName.empty() && !playerName.empty()) {
            scores[gameName][playerName] = score;
        }
    }
    
    file.close();
}

std::map<std::string, int> ScoreManager::getGameScores(const std::string& gameName) const
{
    std::map<std::string, int> topScores;
    
    auto gameIt = scores.find(gameName);
    if (gameIt != scores.end()) {
        topScores = gameIt->second;
    }
    
    return topScores;
}

std::map<std::string, int> ScoreManager::getPlayerScores(const std::string& playerName) const
{
    std::map<std::string, int> playerScores;
    
    for (const auto& [gameName, players] : scores) {
        auto playerIt = players.find(playerName);
        if (playerIt != players.end()) {
            playerScores[gameName] = playerIt->second;
        }
    }
    
    return playerScores;
}

std::vector<std::pair<std::string, int>> ScoreManager::getFormattedScores(const std::string& gameName) const
{
    std::vector<std::pair<std::string, int>> formattedScores;
    
    auto gameScores = getGameScores(gameName);
    
    // Convert map to vector for sorting
    for (const auto& [player, score] : gameScores) {
        formattedScores.emplace_back(player, score);
    }
    
    std::sort(formattedScores.begin(), formattedScores.end(), 
              [](const auto& a, const auto& b) { return a.second > b.second; });
    
    // Top 5 scores
    // TODO: change to what we want
    if (formattedScores.size() > 5) {
        formattedScores.resize(5);
    }
    
    return formattedScores;
}