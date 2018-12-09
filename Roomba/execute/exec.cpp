#include <environment.h>
#include <iostream>
#include <object.h>
#include <unistd.h>
#include <utility>

template <typename T, class... Args>
void addToRoomba(std::shared_ptr<Object> roomba, Args&&... args)
{
    auto object = std::make_shared<T>(std::forward<Args>(args)...);
    roomba->insert(object);
}
std::shared_ptr<Object> CreateRoomba()
{
    auto roomba = std::make_shared<Object>(std::make_shared<BatteryModule>(10));
    addToRoomba<MovementModule>(roomba, 2, 1);
    return roomba;
}

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        if(argv[0])
            std::cout << "Usage: " << argv[0] << " <file>" << std::endl;
        else
            std::cout << "Usage: <program name> <file>" << std::endl;

        exit(1);
    }

    auto env = std::make_shared<Environment>(argv[1]);
    auto roomba = CreateRoomba();

    env->placeModule(roomba, Coor(1, 1));
    roomba->On();

    while(env->isActive())
    {
        env->step();
        std::cout << *env << std::endl;
    }

    env->summary();

    return 0;
}
