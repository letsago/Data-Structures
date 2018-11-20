#include <gtest/gtest.h>
#include <room.h>
#include <roombabrain.h>
#include <roombahardware.h>

using namespace std;
class RoomTests : public ::testing::TestWithParam<const char*>
{
};

TEST(DirectionTest, DirectionTest)
{
    Direction dir = RIGHT;
    dir = static_cast<Direction>((dir + 1) % COUNT);
    ASSERT_EQ(dir, DOWN);
    dir = static_cast<Direction>((dir + 1) % COUNT);
    ASSERT_EQ(dir, LEFT);
    dir = static_cast<Direction>((dir + 1) % COUNT);
    ASSERT_EQ(dir, UP);
    dir = static_cast<Direction>((dir + 1) % COUNT);
    ASSERT_EQ(dir, RIGHT);
}

TEST(RoombaTests, EmptyBatteryTest)
{
    size_t battery = 0;
    RoombaHardware roomba(battery);
    Room room("./Test/raw/invalid.room");
    ASSERT_ANY_THROW(roomba.rotate(room));
}

TEST(RoombaTests, InvalidRoomTest)
{
    size_t battery = 10;
    RoombaHardware roomba(battery);
    Room room("./Test/raw/invalid.room");
    ASSERT_ANY_THROW(room.dropRoomba({1, 1}, RIGHT, roomba););
}

TEST(RoombaTests, SimpleCleanTest)
{
    size_t battery = 50;
    Room room("./Test/raw/square.room");
    RoombaHardware roomba(battery);
    room.dropRoomba({1, 3}, LEFT, roomba);
    roomba.setCleanMode(true);
    ASSERT_FALSE(room.isClean());

    for(uint32_t i = 0; i < 2; i++)
        roomba.move(room);

    roomba.rotate(room);
    roomba.rotate(room);
    ASSERT_FALSE(room.isClean());

    for(uint32_t i = 0; i < 2; i++)
        roomba.move(room);

    roomba.rotate(room);
    ASSERT_FALSE(room.isClean());

    for(uint32_t i = 0; i < 2; i++)
        roomba.move(room);

    roomba.rotate(room);
    ASSERT_FALSE(room.isClean());

    for(uint32_t i = 0; i < 2; i++)
        roomba.move(room);

    ASSERT_FALSE(room.isClean());

    for(uint32_t i = 0; i < 2; i++)
    {
        roomba.rotate(room);
        roomba.move(room);
    }

    ASSERT_TRUE(room.isClean());
    roomba.move(room);
    ASSERT_TRUE(room.isClean());
}

INSTANTIATE_TEST_CASE_P(Tests, RoomTests,
                        ::testing::Values("./Test/raw/fourshape.room", "./Test/raw/hshape.room",
                                          "./Test/raw/lshape.room", "./Test/raw/rectangle.room",
                                          "./Test/raw/square.room", "./Test/raw/ushape.room",
                                          "./Test/raw/zshape.room"));

TEST_P(RoomTests, RoomTest)
{
    size_t battery = 500;
    Room room(GetParam());
    RoombaHardware roomba(battery);
    RoombaBrain roombaBrain(roomba);
    room.dropRoomba({1, 1}, RIGHT, roomba);

    while(!roombaBrain.isClean())
    {
        roombaBrain.step(room);
    }

    ASSERT_TRUE(roombaBrain.isClean());
    ASSERT_TRUE(room.isClean());
}

TEST_P(RoomTests, MoveTest)
{
    size_t battery = 10;
    Room room(GetParam());
    RoombaHardware roomba(battery);
    room.dropRoomba({1, 1}, UP, roomba);
    ASSERT_FALSE(roomba.move(room));
    roomba.rotate(room);
    roomba.rotate(room);
    ASSERT_TRUE(roomba.move(room));
}
