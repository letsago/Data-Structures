#pragma once

#include "queue_test.h"
#include <pyu/rollingarray.h>

class QueueArrayTests : public QueueTests<pyu::RollingArray<int, 5>>
{

};
