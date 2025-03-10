# R-Type Documentation

Welcome to the **R-Type** documentation!
This guide provides information on how to build, understand, and use the project.

---

## Table of Contents

1. <a href="#introduction">Introduction</a>
2. <a href="#configuration">Configuration</a>
3. <a href="#usage">Usage</a>
4. <a href="#links-to-detailed-pages">Links to Detailed Pages</a>
    - [Project Architecture](Architecture.md)
    - [Game Engine documentation](GameEngine/README.md)
    - [How to add documentation ?](HowToAddDoc.md)
    - [How to see the coverage of the unit tests ?](TestsCoverage.md)

---

## <a id="introduction"></a>Introduction

The **R-Type** project is an advanced implementation based on the C++20 game engine. It demonstrates system development concepts and modular build techniques using CMake, focusing on flexibility and maintainability.

---

## <a id="configuration"></a>Configuration

The project uses:

- **GCC/G++** for compilation.
- **Vcpkg** as the dependency manager.
- **CMake** for generating build files with pre-configured presets.

Available presets include:

- `debug`: For development builds.
- `release`: For optimized builds.
- `doc`: For generating documentation.
- `test`: For building tests.

Available targets are:

- `r-type_client`: The client binary.
- `r-type_server`: The server binary.
- `r-type_game_engine`: The GameEngine library (including ECS).
- `r-type_commonlib`: The Common library containing shared datas structures or methods.
- `UnitTest`: For building tests. 'Doesn't work wihtout the test presets because of the compile option '--coverage''

---

## <a id="usage"></a>Usage

The `build.sh` script simplifies the build process. It supports:

- Initial configuration using presets.
- Building specific targets (default is `all`).

### Available Commands

#### Build the project in `debug` mode

- Clone the repository from GitHub:

```bash
    git clone https://github.com/EpitechPromo2027/B-CPP-500-LYN-5-2-rtype-loic.osternaud.git ./RType
```

- Navigate to the project directory.

```bash
    cd RType
```

- Install the VCPKG submodule.

```bash
    git submodule update --init --recursive
```

- Run the build script with the `debug` preset.

```bash
    ./build.sh
    # same as
    ./build.sh debug all
```

#### Build the project in `release` mode

- Follow steps 1 and 2 above.
- Run the build script with the `release` preset.

```bash
    ./build.sh release
    # same as
    ./build.sh release all
```

#### Build a specific target (e.g., `UnitTest`)

- Follow steps 1 and 2 above.
- Specify the target name while running the script.

```bash
    ./build.sh debug UnitTest
    # ‘debug’ is needed to capture options in the bash script
```

---

### Controller

 Button        | Action
 --------------|-------------
 Z             | Move to top
 Q             | Move to left
 S             | Move to down
 D             | Move to right
 F             | Shoot
TAB            | Daltonism

## <a id="links-to-detailed-pages"></a>Links to Detailed Pages

1. [Project Architecture](Architecture.md): Overview of the project's components, including their organization and roles.
2. [Game Engine documentation](GameEngine/README.md): Overview of the GameEngine's components, including their organization and roles.
3. [How to add documentation ?](HowToAddDoc.md): All the informations to correctly add documentation.
4. [How to see the coverage of the unit tests ?](TestsCoverage.md): Results of the Units tests with coverage and many others informations.
