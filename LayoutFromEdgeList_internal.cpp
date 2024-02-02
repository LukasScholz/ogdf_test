#include <stdint.h>
#include <tuple>
#include <vector>
#include <iostream>
#include "layout.hh"
#include "LayoutFromEdgeList_internal.hpp"

float* LayoutFromEdgeList_internals(int number_of_nodes, int* sources, int* destinations, float* weights, int number_of_edges, size_t& result_size) {

    // Try Find GraphProperties
    auto gp = tmap::GraphProperties();
    //std::cout << gp.mst_weight << std::endl;

    // Create a vector of tuples
    std::vector<std::tuple<uint32_t, uint32_t, float>> edges;

    // Populate the vector with tuples
    for (int i = 0; i < number_of_nodes; ++i) {
        edges.push_back(std::make_tuple(static_cast<uint32_t>(sources[i]), static_cast<uint32_t>(destinations[i]), weights[i]));
    }

    // generate LayoutConfig
    tmap::LayoutConfiguration config  = tmap::LayoutConfiguration();

    // call function
    std::tuple<std::vector<float>, std::vector<float>, std::vector<uint32_t>, std::vector<uint32_t>, tmap::GraphProperties> returned = tmap::LayoutFromEdgeList(number_of_nodes, edges, config, false, true);

    // Extract the vectors from the tuple
    std::vector<float>& vector1 = std::get<0>(returned);
    std::vector<float>& vector2 = std::get<1>(returned);
    std::vector<uint32_t>& vector3 = std::get<2>(returned);
    std::vector<uint32_t>& vector4 = std::get<3>(returned);

    // Concatenate the vectors into a single 1D array
    result_size = vector1.size() + vector2.size() + vector3.size() + vector4.size();
    float* result = new float[result_size];
    size_t index = 0;

    for (float value : vector1) {
        result[index++] = value;
    }
    for (float value : vector2) {
        result[index++] = value;
    }
    for (float value : vector3) {
        result[index++] = static_cast<float>(value);
    }
    for (float value : vector4) {
        result[index++] = static_cast<float>(value);
    }

    return result;
}
