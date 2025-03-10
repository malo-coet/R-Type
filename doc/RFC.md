```plaintext
Abstract
This document specifies the network protocol used in the RType game for communication between clients and the server. The protocol is designed to handle various aspects of the game, such as player inputs, entity updates, and connection management. The primary transport layer protocol used is ENet, which provides reliable UDP communication.

1. Introduction
The RType network protocol facilitates communication between the client and server to ensure a seamless multiplayer experience. This protocol handles player inputs, entity state synchronization, connection management, and other essential game mechanics.

2. Protocol Overview
The protocol operates over ENet, a reliable UDP-based networking library. Communication is achieved through the exchange of packets, each identified by a specific type. The following packet types are defined:

PACKET_PLAYER_ID
PACKET_INITIAL_ENTITIES
PACKET_INITIAL_ACK
PACKET_ENTITY_UPDATE
PACKET_INPUT
PACKET_ENTITY_REMOVE
3. Packet Types and Structures
3.1. Packet Types
PACKET_PLAYER_ID (0x01)

Sent by the server to assign a unique player ID to the client.
Structure: [PacketType (1 byte)] [PlayerID (4 bytes)]
PACKET_INITIAL_ENTITIES (0x02)

Sent by the server to provide initial entity states to the client.
Structure: [PacketType (1 byte)] [EntityCount (2 bytes)] [EntityStates (variable)]
PACKET_INITIAL_ACK (0x07)

Sent by the client to acknowledge the receipt of initial entity states.
Structure: [PacketType (1 byte)]
PACKET_ENTITY_UPDATE (0x03)

Sent by the server to update the states of entities.
Structure: [PacketType (1 byte)] [EntityCount (2 bytes)] [EntityStates (variable)]
PACKET_INPUT (0x04)

Sent by the client to convey player input commands.
Structure: [PacketType (1 byte)] [InputFlags (2 bytes)]
PACKET_ENTITY_REMOVE (0x05)

Sent by the server to notify the client of an entity removal.
Structure: [PacketType (1 byte)] [EntityID (4 bytes)]
3.2. EntityState Structure
The EntityState structure represents the state of an entity in the game. It is used in the PACKET_INITIAL_ENTITIES and PACKET_ENTITY_UPDATE packets.

C++
struct EntityState {
    std::array<uint8_t, 16> entityId; // Unique entity identifier
    float x, y;                       // Position coordinates
    float vx, vy;                     // Velocity components
    int type;                         // Entity type
    bool isYoursServ;                 // Ownership flag
};
4. Client-Side Implementation
4.1. ClientNetworkManager Class
The ClientNetworkManager class manages the client's network operations, including connection setup, packet handling, and sending input commands.

C++
class ClientNetworkManager {
public:
    ClientNetworkManager(const std::string& address, uint16_t port);
    ~ClientNetworkManager();

    void onStart();
    void onShutdown();
    void onUpdate(float deltaTime);

    void sendInputCommand(uint16_t inputFlags);
    void sendInitialAck();

private:
    void processPlayerId(const uint8_t* data, size_t size);
    void processEntityUpdate(const uint8_t* data, size_t size);
    void processEntityRemove(const uint8_t* data, size_t size);

    std::string address_;
    uint16_t port_;
    ENetHost* host_;
    ENetPeer* peer_;
    int player_id_;
};
4.2. InputComponent Structure
The InputComponent structure stores the current inputs for an entity.

C++
struct InputComponent {
    std::unordered_map<SDL_Keycode, InputInfo> currentInputs;
    std::queue<SDL_Keycode> keyLog;
    std::size_t maxHistory = 10;
};
5. Server-Side Implementation
5.1. ServerNetworkManager Class
The ServerNetworkManager class manages the server's network operations, including connection handling, packet processing, and broadcasting entity updates.

C++
class ServerNetworkManager : public ecs::System {
public:
    ServerNetworkManager();
    ~ServerNetworkManager();

    bool initializeServer(uint16_t port);
    void onStart() override;
    void onUpdate(float deltaTime) override;

    void sendPlayerId(ENetPeer* peer, int entityId);
    void broadcastEntityRemoval(int entityId);
    void processInitialAck(ENetPeer* fromPeer);
    void sendInitialEntities(ENetPeer* peer, const std::vector<EntityState>& states);
    void sendEntityUpdates(const std::vector<EntityState>& states);

private:
    void handleNewConnection(ENetPeer* peer);

    ENetHost* host_;
    std::vector<ENetPeer*> connectedPeers_;
    std::map<ENetPeer*, bool> peerInitialAck_;
    std::map<ENetPeer*, bool> initialEntitiesSent_;
};
6. Protocol Workflow
Connection Establishment

The client connects to the server using ENet.
The server assigns a unique player ID and sends a PACKET_PLAYER_ID packet to the client.
Initial Entity Synchronization

The server sends the initial state of all entities using a PACKET_INITIAL_ENTITIES packet.
The client acknowledges receipt with a PACKET_INITIAL_ACK packet.
Entity Updates

The server periodically sends PACKET_ENTITY_UPDATE packets to update entity states.
The client processes these updates to synchronize the game state.
Player Input

The client sends player input commands using PACKET_INPUT packets.
The server processes these inputs to update the game state.
Entity Removal

The server sends PACKET_ENTITY_REMOVE packets to notify clients of entity removals.
The clients update their game state accordingly.
7. Conclusion
The RType network protocol is designed to provide efficient and reliable communication between clients and the server, ensuring smooth gameplay. By using ENet and defining specific packet types and structures, the protocol handles player inputs, entity synchronization, and connection management effectively.

For further information or clarifications, please refer to the implementation details in the provided source code or contact the author.
```
