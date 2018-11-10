#include "roombabrain.h"

bool RoombaBrain::isClean() const { return false; }

void RoombaBrain::step(Room& room) { m_roomba.rotate(room); }
