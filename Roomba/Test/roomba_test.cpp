#include <gtest/gtest.h>
#include <limits>
#include <room.h>
#include <roombabrain.h>
#include <roombahardware.h>
#include <string>

using namespace std;
class RoomTests : public ::testing::TestWithParam<const char*>
{
};

TEST(RoombaTests, EmptyBatteryTest)
{
    size_t battery = 0;
    RoombaHardware roomba(battery);
    ASSERT_ANY_THROW(roomba.rotate());
}

INSTANTIATE_TEST_CASE_P(Tests, RoomTests,
                        ::testing::Values("./Test/raw/fourshape.room", "./Test/raw/hshape.room",
                                          "./Test/raw/invalid.room", "./Test/raw/lshape.room",
                                          "./Test/raw/rectangle.room", "./Test/raw/square.room",
                                          "./Test/raw/ushape.room", "./Test/raw/zshape.room"));

TEST_P(RoomTests, RoomTest)
{
    size_t battery = 10;
    Room room(GetParam());
    RoombaHardware roomba(battery);
    RoombaBrain roombaBrain(roomba);
    room.dropRoomba(1, 1, 1, roomba);

    while(!roombaBrain.isClean())
    {
        roombaBrain.step();
    }

    ASSERT_TRUE(roombaBrain.isClean());
    ASSERT_TRUE(room.isClean());
}
