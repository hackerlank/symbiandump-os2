// Copyright 2004 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine

/*
 * � Portions copyright (c) 2006-2007 Nokia Corporation.  All rights reserved.
*/

#ifndef BOOST_GRAPH_DIJKSTRA_TESTING_DIETMAR
#  define BOOST_GRAPH_DIJKSTRA_TESTING
#endif

#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/test/minimal.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/timer.hpp>
#include <vector>
#include <iostream>

#include <iterator>
#include <utility>
#include <boost/random/uniform_int.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/erdos_renyi_generator.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/type_traits/is_same.hpp>
#ifdef __SYMBIAN32__
#include "std_log_result.h"
#define LOG_FILENAME_LINE __FILE__, __LINE__
#endif
using namespace boost;

#ifdef BOOST_GRAPH_DIJKSTRA_TESTING_DIETMAR

struct show_events_visitor : dijkstra_visitor<>
{
  template<typename Vertex, typename Graph>
  void discover_vertex(Vertex v, const Graph&)
  {
    std::cerr << "on_discover_vertex(" << v << ")\n";
  }

  template<typename Vertex, typename Graph>
  void examine_vertex(Vertex v, const Graph&)
  {
    std::cerr << "on_discover_vertex(" << v << ")\n";
  }
};


template<typename Graph, typename Kind>
void run_test(const Graph& g, const char* name, Kind kind, 
              const std::vector<double>& correct_distances)
{
  std::vector<double> distances(num_vertices(g));

  std::cout << "Running Dijkstra's with " << name << "...";
  std::cout.flush();
  timer t;
  dijkstra_heap_kind = kind;

  dijkstra_shortest_paths(g, vertex(0, g),
                          distance_map(&distances[0]).
                          visitor(show_events_visitor()));
  double run_time = t.elapsed();
  std::cout << run_time << " seconds.\n";

  BOOST_TEST(distances == correct_distances);

  if (distances != correct_distances)
    {
      std::cout << "Expected: ";
      std::copy(correct_distances.begin(), correct_distances.end(),
                std::ostream_iterator<double>(std::cout, " "));
      std::cout << "\nReceived: ";
      std::copy(distances.begin(), distances.end(),
                std::ostream_iterator<double>(std::cout, " "));
      std::cout << std::endl;
    }
}
#endif

int test_main(int argc, char* argv[])
{
  unsigned n = (argc > 1? lexical_cast<unsigned>(argv[1]) : 100u);
  unsigned m = (argc > 2? lexical_cast<unsigned>(argv[2]) : 10*n);
  int seed = (argc > 3? lexical_cast<int>(argv[3]) : 1);

  // Build random graph
  typedef adjacency_list<vecS, vecS, directedS, no_property,
                         property<edge_weight_t, double> > Graph;
  std::cout << "Generating graph...";
  std::cout.flush();
  minstd_rand gen(seed);
  double p = double(m)/(double(n)*double(n));
  Graph g(erdos_renyi_iterator<minstd_rand, Graph>(gen, n, p),
          erdos_renyi_iterator<minstd_rand, Graph>(),
          n);
  std::cout << n << " vertices, " << num_edges(g) << " edges.\n";
  uniform_real<double> rand01(0.0, 1.0);
  graph_traits<Graph>::edge_iterator ei, ei_end;
  for (tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
    put(edge_weight, g, *ei, rand01(gen));

  std::vector<double> binary_heap_distances(n);
  std::vector<double> relaxed_heap_distances(n);

  // Run binary heap version
  std::cout << "Running Dijkstra's with binary heap...";
  std::cout.flush();
  timer t;
#ifdef BOOST_GRAPH_DIJKSTRA_TESTING_DIETMAR
  dijkstra_heap_kind = dijkstra_binary_heap;
#else
  dijkstra_relaxed_heap = false;
#endif
  dijkstra_shortest_paths(g, vertex(0, g),
                          distance_map(&binary_heap_distances[0]));
  double binary_heap_time = t.elapsed();
  std::cout << binary_heap_time << " seconds.\n";

  // Run relaxed heap version
  std::cout << "Running Dijkstra's with relaxed heap...";
  std::cout.flush();
  t.restart();
#ifdef BOOST_GRAPH_DIJKSTRA_TESTING_DIETMAR
  dijkstra_heap_kind = dijkstra_relaxed_heap;
#else
  dijkstra_relaxed_heap = true;
#endif
  dijkstra_shortest_paths(g, vertex(0, g),
                          distance_map(&relaxed_heap_distances[0]));
  double relaxed_heap_time = t.elapsed();
  
  if(relaxed_heap_time==0)
  {
     std::cout << "relaxed_heap_time is Zero \n";	
  }
  else
  {
  	std::cout << relaxed_heap_time  <<" seconds \n";	
    std::cout << "Speedup = " << (binary_heap_time / relaxed_heap_time) << ".\n";
  }
  // Verify that the results are equivalent
  BOOST_CHECK(binary_heap_distances == relaxed_heap_distances);

#ifdef BOOST_GRAPH_DIJKSTRA_TESTING_DIETMAR
  run_test(g, "d-ary heap (d=2)", dijkstra_d_heap_2, binary_heap_distances);
  run_test(g, "d-ary heap (d=3)", dijkstra_d_heap_3, binary_heap_distances);
  run_test(g, "Fibonacci heap", dijkstra_fibonacci_heap, binary_heap_distances);
  run_test(g, "Lazy Fibonacci heap", dijkstra_lazy_fibonacci_heap, binary_heap_distances);
  run_test(g, "Pairing heap", dijkstra_pairing_heap, binary_heap_distances);
  run_test(g, "Splay heap", dijkstra_splay_heap, binary_heap_distances);
#endif
  
#ifdef __SYMBIAN32__
	std_log(LOG_FILENAME_LINE,"[End Test Case ]");

	testResultXml("dijkstra_heap_performance");
	close_log_file();
#endif
  return 0;
}
