#include "App.hpp"

// Main function for the client
int main() {
    App app;

    // Run the app
    try {
        app.init();
        app.run();
        app.destroy();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
