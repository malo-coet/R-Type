file(GLOB SOURCES
    "${SERVER_DIR}/src/Main.cpp"
    "${SERVER_DIR}/src/ServerNetworkManager.cpp"
    "${SERVER_DIR}/src/SpawnFromConfigSystem.cpp"
    "${SERVER_DIR}/src/SpawnAsteroidSystem.cpp"
    "${SERVER_DIR}/src/systems/*.cpp"
)

add_executable(r-type_server ${SOURCES})
target_link_libraries(r-type_server PRIVATE r-type_game_engine)
target_link_libraries(r-type_server PRIVATE r-type_commonlib)
target_link_libraries(r-type_server PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2_image SDL2_ttf SDL2_mixer MPG123::libmpg123)
target_link_libraries(r-type_server PRIVATE ${ENET_LIBRARY})
target_compile_features(r-type_server PRIVATE cxx_std_20)

target_include_directories(r-type_server PRIVATE ${GAMEENGINE_DIR}/ecs/include)
target_include_directories(r-type_server PRIVATE ${GAMEENGINE_DIR}/include)
target_include_directories(r-type_server PRIVATE ${SERVER_DIR}/include)
target_include_directories(r-type_server PRIVATE ${CLIENT_DIR}/include)
target_include_directories(r-type_server PRIVATE ${COMMONLIB_DIR}/include)

if (WIN32)
    add_custom_command(
        TARGET r-type_server POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL2::SDL2>
        $<TARGET_FILE:SDL2::SDL2main>
        $<TARGET_FILE_DIR:r-type_server>
        VERBATIM)
endif()