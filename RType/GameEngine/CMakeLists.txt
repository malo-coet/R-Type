file(GLOB SOURCES
    "${GAMEENGINE_DIR}/src/GameEngine.cpp"
    "${GAMEENGINE_DIR}/ecs/src/*.cpp"
    "${GAMEENGINE_DIR}/src/*.cpp"
    "${GAMEENGINE_DIR}/src/components/*.cpp"
    "${GAMEENGINE_DIR}/src/system/*.cpp"
    "${GAMEENGINE_DIR}/src/factory/*.cpp"
)

add_library(r-type_game_engine STATIC ${SOURCES})

target_include_directories(r-type_game_engine
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${GAMEENGINE_DIR}/include>
    PRIVATE
        ${GAMEENGINE_DIR}/src
        ${GAMEENGINE_DIR}/ecs/src
)

target_link_libraries(r-type_game_engine PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2_image SDL2_ttf SDL2_mixer MPG123::libmpg123)
target_link_libraries(r-type_game_engine PRIVATE ${ENET_LIBRARY})
target_compile_features(r-type_game_engine PRIVATE cxx_std_20)

target_include_directories(r-type_game_engine PUBLIC ${GAMEENGINE_DIR}/ecs/include)
target_include_directories(r-type_game_engine PRIVATE ${GAMEENGINE_DIR}/include/components)
target_include_directories(r-type_game_engine PRIVATE ${GAMEENGINE_DIR}/include/factory)
target_include_directories(r-type_game_engine PRIVATE ${GAMEENGINE_DIR}/include/system)
target_include_directories(r-type_game_engine PRIVATE ${GAMEENGINE_DIR}/include/event)
target_include_directories(r-type_game_engine PRIVATE ${GAMEENGINE_DIR}/include)
target_include_directories(r-type_game_engine PRIVATE ${COMMONLIB_DIR}/include)

if (WIN32)
    add_custom_command(
        TARGET r-type_game_engine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL2::SDL2>
        $<TARGET_FILE:SDL2::SDL2main>
        $<TARGET_FILE_DIR:r-type_game_engine>
        VERBATIM)
endif()