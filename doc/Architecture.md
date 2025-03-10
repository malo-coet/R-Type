# Project Architecture

## Overview

RType is a C++ game project structured into distinct modules to separate responsibilities and promote modularity. This document outlines the project's organization, the roles of its various components, and their interconnections.

## Project Structure

```plaintext
RType
├── assets
│   ├── background.png
│   ├── bullet.png
│   ├── ship_1.png
│   └── ship_2.png
├── Client
│   ├── CMakeLists.txt
│   ├── include
│   └── src
├── CommonLib
│   ├── CMakeLists.txt
│   ├── include
│   └── src
├── GameEngine
│   ├── CMakeLists.txt
│   ├── include
│   └── src
└── Server
    ├── CMakeLists.txt
    ├── include
    └── src
```

### Component Details

#### **assets**

- Contains the graphical resources for the game, such as backgrounds, ship sprites, and projectiles.
- These files are used by the game engine for rendering.

#### **Client**

- **Role**: Implements the client application, handling the user interface and communication with the server.
- **Structure**:
  - `include`: Contains client-specific header files.
  - `src`: Contains source files for client functionalities.
  - `CMakeLists.txt`: Build script for the client module.

#### **CommonLib**

- **Role**: Shared library for both client and server, providing common functionalities such as network protocol management or shared data structures.
- **Structure**:
  - `include`: Header files for common functions.
  - `src`: Source code for the implementation.
  - `CMakeLists.txt`: Build script.

#### **GameEngine**

- **Role**: The core of the game engine, including the Entity-Component-System (ECS) management.
- **Structure**:
  - `include`: Game engine header files.
  - `src`: Source files for the implementation.
  - `CMakeLists.txt`: Build script.

#### **Server**

- **Role**: Implements the server, managing game logic, multiplayer interactions, and synchronization.
- **Structure**:
  - `include`: Header files for server functionalities.
  - `src`: Implementation of server functionalities.
  - `CMakeLists.txt`: Build script.

### **CMakeLists.txt (Root)**

- Coordinates the build of all submodules using CMake.
- Defines dependencies between project components and global options.

## Key Points

- **Modularity**: Each component is isolated to facilitate testing, maintenance, and scalability.
- **Reusability**: Shared libraries (`CommonLib`) encourage code sharing across modules.
- **Flexibility**: The ECS in `GameEngine` enables dynamic management of entities and systems.

## Conclusion

This modular architecture ensures the development of a robust and scalable game. Clearly defined responsibilities for each module enable efficient collaboration among developers and simplify project management.
