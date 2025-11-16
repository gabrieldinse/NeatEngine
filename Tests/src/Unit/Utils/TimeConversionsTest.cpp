#include <gtest/gtest.h>

#include <Utils/TimeConversions.hpp>
#include <Core/Types.hpp>

namespace Neat {
TEST(TimeConversionsTest, NanosecondsCast) {
  EXPECT_EQ(nanosecondsCast<Int64>(std::chrono::nanoseconds(1)), 1);
  EXPECT_EQ(nanosecondsCast<Int64>(std::chrono::microseconds(1)), 1000);
  EXPECT_EQ(nanosecondsCast<Int64>(std::chrono::milliseconds(1)), 1000000);
  EXPECT_EQ(nanosecondsCast<Int64>(std::chrono::seconds(1)), 1000000000);
  EXPECT_EQ(nanosecondsCast<Int64>(std::chrono::minutes(1)), 60000000000);
  EXPECT_EQ(nanosecondsCast<Int64>(std::chrono::hours(1)), 3600000000000);
}

TEST(TimeConversionsTest, MicrosecondsCast) {
  EXPECT_EQ(microsecondsCast<Int64>(std::chrono::nanoseconds(1000)), 1);
  EXPECT_EQ(microsecondsCast<Int64>(std::chrono::microseconds(1)), 1);
  EXPECT_EQ(microsecondsCast<Int64>(std::chrono::milliseconds(1)), 1000);
  EXPECT_EQ(microsecondsCast<Int64>(std::chrono::seconds(1)), 1000000);
  EXPECT_EQ(microsecondsCast<Int64>(std::chrono::minutes(1)), 60000000);
  EXPECT_EQ(microsecondsCast<Int64>(std::chrono::hours(1)), 3600000000);
}

TEST(TimeConversionsTest, MillisecondsCast) {
  EXPECT_EQ(millisecondsCast<Int64>(std::chrono::nanoseconds(1000000)), 1);
  EXPECT_EQ(millisecondsCast<Int64>(std::chrono::microseconds(1000)), 1);
  EXPECT_EQ(millisecondsCast<Int64>(std::chrono::milliseconds(1)), 1);
  EXPECT_EQ(millisecondsCast<Int64>(std::chrono::seconds(1)), 1000);
  EXPECT_EQ(millisecondsCast<Int64>(std::chrono::minutes(1)), 60000);
  EXPECT_EQ(millisecondsCast<Int64>(std::chrono::hours(1)), 3600000);
}

TEST(TimeConversionsTest, SecondsCast) {
  EXPECT_EQ(secondsCast<Int64>(std::chrono::nanoseconds(1000000000)), 1);
  EXPECT_EQ(secondsCast<Int64>(std::chrono::microseconds(1000000)), 1);
  EXPECT_EQ(secondsCast<Int64>(std::chrono::milliseconds(1000)), 1);
  EXPECT_EQ(secondsCast<Int64>(std::chrono::seconds(1)), 1);
  EXPECT_EQ(secondsCast<Int64>(std::chrono::minutes(1)), 60);
  EXPECT_EQ(secondsCast<Int64>(std::chrono::hours(1)), 3600);
}

TEST(TimeConversionsTest, MinutesCast) {
  EXPECT_EQ(minutesCast<Int64>(std::chrono::microseconds(60000000)), 1);
  EXPECT_EQ(minutesCast<Int64>(std::chrono::milliseconds(60000)), 1);
  EXPECT_EQ(minutesCast<Int64>(std::chrono::seconds(60)), 1);
  EXPECT_EQ(minutesCast<Int64>(std::chrono::minutes(1)), 1);
  EXPECT_EQ(minutesCast<Int64>(std::chrono::hours(1)), 60);
  EXPECT_EQ(minutesCast<Int64>(std::chrono::days(1)), 1440);
}

TEST(TimeConversionsTest, HoursCast) {
  EXPECT_EQ(hoursCast<Int64>(std::chrono::milliseconds(3600000)), 1);
  EXPECT_EQ(hoursCast<Int64>(std::chrono::seconds(3600)), 1);
  EXPECT_EQ(hoursCast<Int64>(std::chrono::minutes(60)), 1);
  EXPECT_EQ(hoursCast<Int64>(std::chrono::hours(1)), 1);
  EXPECT_EQ(hoursCast<Int64>(std::chrono::days(1)), 24);
  EXPECT_EQ(hoursCast<Int64>(std::chrono::days(100)), 2400);
}

TEST(TimeConversionsTest, DaysCast) {
  EXPECT_EQ(daysCast<Int64>(std::chrono::milliseconds(86400000)), 1);
  EXPECT_EQ(daysCast<Int64>(std::chrono::seconds(86400)), 1);
  EXPECT_EQ(daysCast<Int64>(std::chrono::minutes(1440)), 1);
  EXPECT_EQ(daysCast<Int64>(std::chrono::hours(24)), 1);
  EXPECT_EQ(daysCast<Int64>(std::chrono::days(1)), 1);
  EXPECT_EQ(daysCast<Int64>(std::chrono::days(100)), 100);
}
}  // namespace Neat