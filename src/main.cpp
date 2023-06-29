// This is a personal academic project. Dear PVS-Studio, please check it.
//
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
//
// Copyright 2023 Roman Ishchenko
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.
//
//

#include <iostream>
#include <fstream>

#include <Eigen/Core>
#include <cxxopts.hpp>
#include <spdlog/spdlog.h>

#include "parsers/grammar/xyz_grammar.h"
#include <tao/pegtl/contrib/analyze.hpp>
#include <tao/pegtl/contrib/parse_tree.hpp>
#include <tao/pegtl.hpp>
#include <tao/pegtl/contrib/trace.hpp>
#include <tao/pegtl/contrib/parse_tree_to_dot.hpp>


int main(int argc, char *argv[]) {
  cxxopts::Options opt("Bassenji", "A MD-based conformer generator");
  opt.allow_unrecognised_options();
  opt.add_options()
      ("i,input", "Input file", cxxopts::value<std::string>())
      ("o,output", "Output file", cxxopts::value<std::string>())
      ("v,verbose", "Logging level", cxxopts::value<int>()->default_value("2"));

  cxxopts::ParseResult options = opt.parse(argc, argv);

  spdlog::info("Bassenji started");
  spdlog::set_level(static_cast<spdlog::level::level_enum>(options["verbose"].as<int>()));

  for (auto const &arg : options.arguments()) {
    spdlog::debug("Argument \"{0}\" with value \"{1}\" received", arg.key(), arg.value());
  }
  for (auto unknown_arg : options.unmatched()) {
    spdlog::warn("Unknown argument received {}", unknown_arg);
  }

  auto in = tao::pegtl::file_input<>(options["input"].as<std::string>());
  TrajectoryBuilder tb = TrajectoryBuilder();
  tao::pegtl::parse<grammar::xyz_file, grammar::xyz_action>(in, tb);
  spdlog::debug("Parsing done");

}