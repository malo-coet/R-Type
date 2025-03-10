#ifndef CLIENT_NETWORK_MANAGER_HPP
#define CLIENT_NETWORK_MANAGER_HPP

#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#endif
#include <enet/enet.h>
#include <vector>
#include <map>
#include <unordered_map>
#include <memory>
#include <string>
#include <enet/enet.h>
#include <thread>
#include <chrono>
#include <atomic>
#include "ecs.hpp"
#include "components/typeComponent.hpp"

class ClientNetworkManager : public ecs::System {
public:
    ClientNetworkManager(const std::string& adress, uint16_t port);
    ~ClientNetworkManager();

    void onStart() override;

    void onShutdown() override;

    void onUpdate(float deltaTime) override; 

    void sendInputCommand(uint16_t inputFlags);
    void sendInitialAck();

    int getClientId() const;;

    void startPingThread();
    void stopPingThread();
    void printPing() const;

    void detectHits();

    void setPlayerUUID(const std::string& uuid) { player_uuid_ = uuid; }
    const std::string& getPlayerUUID() const { return player_uuid_; }

private:
    void processPlayerId(const uint8_t* data, size_t size);
    // void processInitialEntities(const uint8_t* data, size_t size);
    void processEntityRemove(const uint8_t* data, size_t size);
    void processEntityUpdate(const uint8_t* data, size_t size);

    std::atomic<bool> running;
    std::thread pingThread;

    const std::string adresse_;
    uint16_t port_;

    ENetHost* host_;
    ENetPeer* peer_;

    std::string player_uuid_;

    std::map<int, ecs::Entity> entityMap;
};

#endif
