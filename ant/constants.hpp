// @author: Asher Desai
// @file: constants.hpp
// @description: includes constants for all the other files

#pragma once

constexpr int NUM_TIMES = 2880;
constexpr int NUM_NODES = 472;
constexpr int NUM_ANTS = 20;
constexpr int NUM_ITER = 20000;

constexpr int startNode = 154;
constexpr int startTime = 5 * 3600 + 0 * 60 + 0;

constexpr double ALPHA = 1; // Controls weight of pheromones in probability calculation
constexpr double BETA = 2; // Controls weight of accessibility in probability calculation

constexpr double RHO = 0.005; // Rate of pheromone evaporation
constexpr double P_BEST = 0.0000001; // See Stutzle for explanation
constexpr int RESET_COUNT = 500; // Defines number of unchanged iterations before pheromones are recalibrated
constexpr double RESET_FACTOR = 1; // 1: resets pheromones to 1 at stall, 0: does not reset pheromones