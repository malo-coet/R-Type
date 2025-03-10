file(GLOB SOURCES
"${CLIENT_DIR}/src/InputManager.cpp"
    "${CLIENT_DIR}/src/MainClient.cpp"
    "${CLIENT_DIR}/src/App.cpp"
    "${CLIENT_DIR}/src/Renderer.cpp"
    "${CLIENT_DIR}/src/ClientNetworkManager.cpp"
    "${CLIENT_DIR}/src/Menu.cpp"
    "${CLIENT_DIR}/src/systems/InputActionSystem.cpp"
    "${CLIENT_DIR}/src/systems/ParalaxResetSystem.cpp"
)

add_executable(r-type_client ${SOURCES})
target_link_libraries(r-type_client PRIVATE r-type_game_engine)
target_link_libraries(r-type_client PRIVATE r-type_commonlib)
target_link_libraries(r-type_client PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2_image SDL2_ttf SDL2_mixer MPG123::libmpg123)
target_link_libraries(r-type_client PRIVATE ${ENET_LIBRARY})
target_compile_features(r-type_client PRIVATE cxx_std_20)

target_include_directories(r-type_client PRIVATE ${CLIENT_DIR}/include)
target_include_directories(r-type_client PRIVATE ${GAMEENGINE_DIR}/ecs/include)
target_include_directories(r-type_client PRIVATE ${GAMEENGINE_DIR}/include/factory)
target_include_directories(r-type_client PRIVATE ${GAMEENGINE_DIR}/include/system)
target_include_directories(r-type_client PRIVATE ${GAMEENGINE_DIR}/include)
target_include_directories(r-type_client PRIVATE ${GAMEENGINE_DIR}/include/components)
target_include_directories(r-type_client PRIVATE ${SERVER_DIR}/include)
target_include_directories(r-type_client PRIVATE ${COMMONLIB_DIR}/include)
target_include_directories(r-type_client PRIVATE ${COMMONLIB_DIR})

add_dependencies(r-type_client r-type_game_engine)

if (WIN32)
    add_custom_command(
        TARGET r-type_client POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL2::SDL2>
        $<TARGET_FILE:SDL2::SDL2main>
        $<TARGET_FILE_DIR:r-type_client>
        VERBATIM)
endif()