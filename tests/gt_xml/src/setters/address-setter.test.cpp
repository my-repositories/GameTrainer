#include <string>

#include <gtest/gtest.h>

#include <gt_xml/setters/address-setter.hpp>

TEST(address_setter, set) {
const std::string buffer = "";
gt::xml::CheatEntry entry;
gt::xml::AddressSetter setter(NULL);

setter.set(buffer, entry);

EXPECT_EQ(entry.address, 0);
}
