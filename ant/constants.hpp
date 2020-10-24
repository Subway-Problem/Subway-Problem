// @author: Asher Desai
// @file: constants.hpp
// @description: includes constants for all the other files

#pragma once

constexpr int NUM_TIMES = 2880;
constexpr int NUM_NODES = 472;
constexpr int NUM_ANTS = 20;
constexpr int NUM_ITER = 100000;

constexpr int startNode = 354;
constexpr int startTime = 7320;

constexpr double Q = 75000; // Constant, doesn't seem to have much effect
constexpr double ALPHA = 1; // Controls weight of pheromones in probability calculation
constexpr double BETA = 3; // Controls weight of accessibility in probability calculation

constexpr double EVAP = 0.01; // Rate of pheromone evaporation
constexpr double TAU_MAX = 50; // Maximum pheromone value, pheromone matrix is initialized to this number
constexpr double TAU_MIN = 0.02; // Minimum pheromone value, it seems like the closer this value is to TAU_MAX
                                // the more variability there will be in the solution space
constexpr int RESET_COUNT = 1000; // Defines number of unchanged iterations before pheromones are recalibrated
constexpr double RESET_FACTOR = 0.1; // Currently unused, but could be used as part of the pheromone recalibration