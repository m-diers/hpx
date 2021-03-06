# Copyright (c) 2019 The STE||AR-Group
#
# SPDX-License-Identifier: BSL-1.0
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.6.3 FATAL_ERROR)

set(segmented_algorithms_headers
  hpx/parallel/segmented_algorithm.hpp
  hpx/parallel/segmented_algorithms/adjacent_difference.hpp
  hpx/parallel/segmented_algorithms/adjacent_find.hpp
  hpx/parallel/segmented_algorithms/all_any_none.hpp
  hpx/parallel/segmented_algorithms/count.hpp
  hpx/parallel/segmented_algorithms/detail/dispatch.hpp
  hpx/parallel/segmented_algorithms/detail/reduce.hpp
  hpx/parallel/segmented_algorithms/detail/scan.hpp
  hpx/parallel/segmented_algorithms/detail/transfer.hpp
  hpx/parallel/segmented_algorithms/exclusive_scan.hpp
  hpx/parallel/segmented_algorithms/fill.hpp
  hpx/parallel/segmented_algorithms/find.hpp
  hpx/parallel/segmented_algorithms/for_each.hpp
  hpx/parallel/segmented_algorithms/generate.hpp
  hpx/parallel/segmented_algorithms/inclusive_scan.hpp
  hpx/parallel/segmented_algorithms/minmax.hpp
  hpx/parallel/segmented_algorithms/reduce.hpp
  hpx/parallel/segmented_algorithms/transform_exclusive_scan.hpp
  hpx/parallel/segmented_algorithms/transform.hpp
  hpx/parallel/segmented_algorithms/transform_inclusive_scan.hpp
  hpx/parallel/segmented_algorithms/transform_reduce.hpp
)

include(HPX_AddModule)
add_hpx_module(segmented_algorithms
  FORCE_LINKING_GEN
  HEADERS ${segmented_algorithms_headers}
  DEPENDENCIES
    hpx_algorithms
    hpx_assertion
    hpx_config
    hpx_datastructures
    hpx_execution
    hpx_functional
    hpx_iterator_support
    hpx_serialization
    hpx_type_support
  CMAKE_SUBDIRS examples tests
)
