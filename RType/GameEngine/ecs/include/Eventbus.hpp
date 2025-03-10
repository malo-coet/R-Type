/*
** EPITECH PROJECT, 2025
** RType-private
** File description:
** Eventbus
*/

#ifndef EVENTBUS_HPP_
#define EVENTBUS_HPP_

#include <functional>
#include <vector>
#include <unordered_map>
#include <typeindex>

namespace ecs {

   /**
     * @struct Event
     * @brief Base class for all events in the Eventbus system.
     *
     * All custom events should inherit from this class.
     */
    struct Event {
        virtual ~Event() = default;
    };

    /**
     * @typedef EventCallback
     * @brief Defines the type of callback functions for handling events.
     */
    using EventCallback = std::function<void(const Event &)>;

    /**
     * @class Eventbus
     * @brief Manages the publication and subscription of events in the ECS.
     *
     * The `Eventbus` provides a mechanism to publish events and notify all
     * subscribers registered for a specific event type. This is useful for
     * decoupling systems and components in an ECS architecture.
     */
    class Eventbus {
        public:
            /**
             * @brief Default constructor for Eventbus.
             */
            Eventbus() = default;

            /**
             * @brief Default destructor for Eventbus.
             */
            ~Eventbus() = default;

            /**
             * @brief Subscribe to a specific event type.
             *
             * Allows a callback function to be registered for a specific event type.
             * The callback will be invoked whenever the event is published.
             *
             * @tparam Event The type of the event to subscribe to.
             * @param callback The function to be called when the event is published.
             */
            template <class Event>
            void subscribe(EventCallback callback);

            /**
             * @brief Publish an event to all subscribers of its type.
             *
             * Notifies all registered callbacks for the specific event type.
             *
             * @tparam Event The type of the event to publish.
             * @param event The event instance to publish.
             */
            template <class Event>
            void post(const Event &event);

        private:
            /**
             * @brief Stores the list of subscribers for each event type.
             *
             * The key is the type of the event, and the value is a vector
             * of callback functions that handle the event.
             */
            std::unordered_map<std::type_index, std::vector<EventCallback>> _subscribers;
    };
}

#endif /* !EVENTBUS_HPP_ */
