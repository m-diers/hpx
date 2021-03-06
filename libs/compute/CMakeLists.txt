# Copyright (c) 2019 The STE||AR-Group
#
# SPDX-License-Identifier: BSL-1.0
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.3.2 FATAL_ERROR)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(compute_headers
  hpx/compute/detail/get_proxy_type.hpp
  hpx/compute/detail/iterator.hpp
  hpx/compute/detail/target_distribution_policy.hpp
  hpx/compute/host/block_allocator.hpp
  hpx/compute/host/block_executor.hpp
  hpx/compute/host/default_executor.hpp
  hpx/compute/host/get_targets.hpp
  hpx/compute/host.hpp
  hpx/compute/host/numa_domains.hpp
  hpx/compute/host/target_distribution_policy.hpp
  hpx/compute/host/target.hpp
  hpx/compute/host/traits/access_target.hpp
  hpx/compute/serialization/vector.hpp
  hpx/compute/traits/access_target.hpp
  hpx/compute/traits/allocator_traits.hpp
  hpx/compute/traits.hpp
  hpx/compute/vector.hpp
)

set(compute_compat_headers)

set(compute_sources
  get_host_targets.cpp
  host_target.cpp
  numa_domains.cpp
)

include(HPX_AddModule)
add_hpx_module(compute
  COMPATIBILITY_HEADERS OFF
  DEPRECATION_WARNINGS
  FORCE_LINKING_GEN
  GLOBAL_HEADER_GEN ON
  SOURCES ${compute_sources}
  HEADERS ${compute_headers}
  COMPAT_HEADERS ${compute_compat_headers}
  DEPENDENCIES
    hpx_algorithms
    hpx_config
    hpx_coroutines
    hpx_execution
    hpx_hardware
    hpx_memory
    hpx_plugin
    hpx_program_options
    hpx_resource_partitioner
    hpx_serialization
    hpx_threadmanager
    hpx_type_support
  CMAKE_SUBDIRS examples tests
)

# Temporary : this module is currently depending on main headers which
# themselves include apex. In the future, those main headers would be in a
# module that link to apex, and we'd be able to remove this.
if (TARGET hpx::apex)
  target_link_libraries(hpx_compute PRIVATE hpx::apex)
  get_target_property(_apex_inc_dir hpx::apex INTERFACE_INCLUDE_DIRECTORIES)
  target_include_directories(hpx_compute INTERFACE "${_apex_inc_dir}")
endif()
