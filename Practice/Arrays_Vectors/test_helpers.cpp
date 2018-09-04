#include "headers/test_helpers.h"

uint32_t UnitTests::s_refCounters = 0;
std::vector<std::pair<std::string, bool>> UnitTests::s_summary;
typemap & UnitTests::s_registry() { static typemap impl; return impl; }
