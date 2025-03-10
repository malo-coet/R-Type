file(GLOB SOURCES
    "${TESTS_DIR}/UnitTests/GameEngine/ecs/*.cpp"
)

add_executable(UnitTests ${SOURCES})
target_link_libraries(UnitTests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(UnitTests PRIVATE r-type_commonlib)
target_link_libraries(UnitTests PRIVATE r-type_game_engine)
