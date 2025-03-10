# 2D Game Engine Architecture

---

## **Main Structure**

### 1. Entity Component System (ECS)

The ECS architecture is at the core of the game engine, allowing for efficient and flexible management of game objects and their behaviors :

- **Entity** :
  - A unique identifier for a game object
  - Entities themselves do not contain data or behavior but are a container for components

- **Component** :
  - Represents a specific aspect of an entity, such as position, velocity, or health
  - Contains only data, without any behavior or logic

- **System** :
  - Implements logic and behavior for specific components
  - Systems operate on entities that have the relevant components, enabling separation of data and behavior

---

### 2. Graphics & Rendering

Responsible for managing graphics and rendering visual elements to the screen:

- **Window**:
  - Handles the creation, resizing, and management of the main game window
  - Ensures that the display context is properly initialized and managed

- **Renderer**:
  - Manages the drawing of sprites, textures, and other graphical objects onto the screen
  - Optimizes rendering performance using techniques like batching and caching

> **Note:** This module uses **SDL2** for window creation and rendering. For a detailed comparison between **SDL2** and **SFML**, refer to the [comparison document](./Comparative.md).

### 3. Input Management

A module dedicated to handling user input :

- Detects input from various devices, including keyboards, mice, and game controllers
- Handles input mappings, allowing customizable controls for users

---

### 5. Physics

This module simulates the physics and manages collisions in the game :

- Handles physical properties like velocity, acceleration, and forces applied to objects
- Manages collision detection between objects with colliders

---

### 5. Network

A module for handling multiplayer and online features :

- Provides communication between players or servers
- Manages synchronization of entities and events across multiple clients
- Includes protocols for reliable or fast data transmission (e.g., TCP, UDP)

---

## **Architecture Diagram**

```plaintext
+-------------------------+
|       Game Engine       |
| +---------------------+ |
| |         ECS         | |
| +---------------------+ |
| +---------------------+ |
| | Graphics & Rendering| |
| | +-----------------+ | |
| | |     Window      | | |
| | |    Renderer     | | |
| | +-----------------+ | |
| +---------------------+ |
| +---------------------+ |
| |  Input Management   | |
| +---------------------+ |
| +---------------------+ |
| |      Physics        | |
| +---------------------+ |
| +---------------------+ |
| |      Network        | |
| +---------------------+ |
+-------------------------+
```
