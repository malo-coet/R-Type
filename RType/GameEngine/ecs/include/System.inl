/*
** EPITECH PROJECT, 2024
** RType-private
** File description:
** System
*/

#ifndef SYSTEM_INL_
#define SYSTEM_INL_

template <class Func>
void ecs::System::forEach(Func &&function)
{
    for (ecs::Entity& entity : _enableEntities) {
        function(entity);
    }
}

#endif /* !SYSTEM_INL_ */