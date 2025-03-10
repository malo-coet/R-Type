file(GLOB SOURCES
    "${COMMONLIB_DIR}/src/CommonLib.cpp"
    "${COMMONLIB_DIR}/src/script/*.cpp"
    "${COMMONLIB_DIR}/src/factory/*.cpp"
    "${COMMONLIB_DIR}/src/EnemyMovementSystem.cpp"
    "${COMMONLIB_DIR}/src/EnemyShootGun.cpp"
    "${COMMONLIB_DIR}/src/CollisionSystem.cpp"
    "${COMMONLIB_DIR}/src/HitSystem.cpp"
    "${COMMONLIB_DIR}/src/WindowHitboxSystem.cpp"
)

add_library(r-type_commonlib STATIC ${SOURCES})
target_include_directories(r-type_commonlib
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${COMMONLIB_DIR}/include>
    PRIVATE
        ${COMMONLIB_DIR}/src
)

target_link_libraries(r-type_commonlib PRIVATE r-type_game_engine)
target_compile_features(r-type_commonlib PRIVATE cxx_std_20)
target_include_directories(r-type_commonlib PRIVATE ${GAMEENGINE_DIR}/ecs/include)
target_include_directories(r-type_commonlib PRIVATE ${COMMONLIB_DIR}/include)
target_include_directories(r-type_commonlib PRIVATE ${CLIENT_DIR}/include)

if (WIN32)
    add_custom_command(
        TARGET r-type_commonlib POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL2::SDL2>
        $<TARGET_FILE:SDL2::SDL2main>
        $<TARGET_FILE_DIR:r-type_commonlib>
        VERBATIM)
endif()