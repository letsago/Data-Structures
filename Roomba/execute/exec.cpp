#include <ctime>
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

std::shared_ptr<Object> CreateRoomba(int battery)
{
    auto roomba = std::make_shared<Object>(std::make_shared<BatteryModule>(battery));
    addToRoomba<MovementModule>(roomba, 2, 1);
    auto dummy = std::make_shared<RandomController>();
    Object::PairControllerAndObject(roomba, dummy);
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
    srand(time(NULL));

    auto env = std::make_shared<Environment>(argv[1]);
    auto roomba = CreateRoomba(10);

    env->placeModule(roomba, Pose(Coor(1, 5), Rotation::Right()));
    roomba->On();

    while(env->isActive())
    {
        env->step();
        std::cout << "\033[2J\033[1;1H";
        std::cout << *env << std::endl;
        env->summary();
        usleep(500000);
    }

    return 0;
}
