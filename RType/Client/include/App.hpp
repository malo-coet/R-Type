#ifndef APP_HPP
#define APP_HPP

#include <memory>
#include "ecs.hpp"
#include "ClientNetworkManager.hpp"
#include "InputManager.hpp"
#include "components/component.hpp"

class App {
public:
    App();
    ~App();

    void init();
    void run();
    void destroy();

private:
    void update(float deltaTime);

    // ClientNetworkManager networkManager_;

    ecs::Registry registry;
    bool is_initialized_;
    int player_id;
};

#endif // APP_HPP
