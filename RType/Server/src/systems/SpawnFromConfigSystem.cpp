/*
** EPITECH PROJECT, 2025
** RType-private
** File description:
** spawnFromConfigSystem
*/

#include "systems/SpawnFromConfigSystem.hpp"
#include "ServerNetworkManager.hpp"
#include "CommonLib/factory/EntityFactory.hpp"
#include "CommonLib/FactionComponent.hpp"
#include "components/component.hpp"
#include "components/typeComponent.hpp"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>

using json = nlohmann::json;

SpawnFromConfigSystem::SpawnFromConfigSystem()
{
    getFilter().require<position>();
    getFilter().require<FactionEnemy>();
}

SpawnFromConfigSystem::~SpawnFromConfigSystem() = default;

void SpawnFromConfigSystem::onStart()
{
    std::string rtypePath = std::getenv("PWD");
    std::ifstream file(rtypePath + "/RType/Server/waveConfig.json");
    if (!file) {
        throw std::runtime_error("Could not open file");
    }

    json jsonData;
    file >> jsonData;

    for (const auto& waveData : jsonData) {
        Wave wave;
        for (const auto& enemyData : waveData) {
            Enemy enemy = {
                enemyData.at("size"),
                {enemyData.at("position")[0], enemyData.at("position")[1]},
                enemyData.at("number")
            };
            wave.enemies.push_back(enemy);
        }
        waves_.push_back(wave);
    }
}

void SpawnFromConfigSystem::spawnWave(const Wave& wave) {
    for (const auto& enemy : wave.enemies) {
        for (int i = 0; i < enemy.number; i++) {
            if (enemy.size == 1)
                EntityFactory::createEnemy(getRegistry(), enemy.position.first, enemy.position.second);
            if (enemy.size == 2)
                EntityFactory::createEnemyMed(getRegistry(), enemy.position.first, enemy.position.second);
            if (enemy.size == 3)
                EntityFactory::createEnemyBig(getRegistry(), enemy.position.first, enemy.position.second);
        }
    }
}

void SpawnFromConfigSystem::onUpdate(float deltaTime)
{
    auto& serverNetworkManager = getRegistry().getSystem<ServerNetworkManager>();
    
    /*if (serverNetworkManager.getConnectedPeersCount() < 2) {
        return;
    }*/

    if (getEntityCount() == 0) {
        if (waveIndex_ < waves_.size()) {
            spawnWave(waves_[waveIndex_]);
            ++waveIndex_;
        } else {
            // palceholeder
        }
    }
}

