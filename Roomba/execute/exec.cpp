#include <iostream>
#include <roombabrain.h>
#include <unistd.h>

using namespace std;

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        if(argv[0])
            cout << "Usage: " << argv[0] << " <file>" << endl;
        else
            cout << "Usage: <program name> <file>" << endl;

        exit(1);
    }

    size_t battery = 800;
    Room room(argv[1]);
    RoombaHardware roomba(battery);

    for(size_t i = 0; i < Direction::COUNT; ++i)
    {
        roomba.addSensor(static_cast<Direction>(i));
    }

    RoombaBrain roombaBrain(roomba);
    room.dropRoomba({1, 1}, RIGHT, roomba);

    while(!roombaBrain.isClean())
    {
        for(size_t i = 0; i < Direction::COUNT; ++i)
        {
            Sensor& sensor = roomba.getSensor(static_cast<Direction>(i));
            room.updateSensor(sensor, static_cast<Direction>(i));
        }

        roombaBrain.step(room);
        cout << "\033[2J\033[1;1H";
        cout << room;
        cout << roombaBrain;
        usleep(200000);
    }

    return 0;
}
