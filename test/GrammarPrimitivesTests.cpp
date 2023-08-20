// This is an open source non-commercial project. Dear PVS-Studio, please check it.
//
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
// Copyright 2023 Roman Ishchenko
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <gtest/gtest.h>
#include <IO/readers/grammar/misc_grammar.h>

class GrammarPrimitiveTests : public ::testing::Test
{
    void SetUp() override
    {};

    void TearDown() override
    {};
};

TEST_F(GrammarPrimitiveTests, AtomSymbol)
{
    auto c = tao::pegtl::string_input<>("C", "string");
    ASSERT_TRUE(tao::pegtl::parse<atom_symbol>(c));

    auto ca = tao::pegtl::string_input<>("Ca", "string");
    ASSERT_TRUE(tao::pegtl::parse<atom_symbol>(ca));

    auto caa = tao::pegtl::string_input<>("Caa", "string");
    ASSERT_FALSE(tao::pegtl::parse<atom_symbol>(caa));
}

TEST_F(GrammarPrimitiveTests, CoordinateInt)
{
    std::vector<std::string> passing_cases{"1", "-1", "1e3", "1e-3", "-1e3", "-1e-3"};
    for (const auto& str : passing_cases) {
        auto in = tao::pegtl::string_input<>(str, "string");
        ASSERT_TRUE(tao::pegtl::parse<num_int>(in));
    }
}

TEST_F(GrammarPrimitiveTests, CoordinateFloat)
{
    std::vector<std::string> passing_cases{"1.2", "-1.2", "1.2e3", "1.2e-3", "-1.2e3", "-1.2e-3"};
    for (const auto& str : passing_cases) {
        auto in = tao::pegtl::string_input<>(str, "string");
        ASSERT_TRUE(tao::pegtl::parse<num_float>(in));
    }
}

