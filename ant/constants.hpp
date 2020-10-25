// @author: Asher Desai
// @file: constants.hpp
// @description: includes constants for all the other files

#pragma once

constexpr int NUM_TIMES = 2880;
constexpr int NUM_NODES = 472;
constexpr int NUM_ANTS = 20;
constexpr int NUM_ITER = 100000;

constexpr int startNode = 116;
constexpr int startTime = 7 * 3600;

constexpr double ALPHA = 1; // Controls weight of pheromones in probability calculation
constexpr double BETA = 1; // Controls weight of accessibility in probability calculation

constexpr double RHO = 0.01; // Rate of pheromone evaporation
constexpr double P_BEST = 0.0000001; // See Stutzle for explanation
constexpr int RESET_COUNT = 1000; // Defines number of unchanged iterations before pheromones are recalibrated