#include <gtest/gtest.h>
#include <engine/version.hpp>

using namespace engine;

TEST(Engine, Version) {
    ASSERT_EQ(get_version(), "1.0.0");
}
