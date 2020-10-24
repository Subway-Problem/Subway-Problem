// @author: Asher Desai
// @file: constants.hpp
// @description: includes constants for all the other files

#pragma once

constexpr int NUM_TIMES = 2880;
constexpr int NUM_NODES = 472;
constexpr int NUM_ANTS = 25;
constexpr int NUM_ITER = 2000;

constexpr int startNode = 0;
constexpr int startTime = 0;

constexpr double Q = 10000;
constexpr double alpha = 1.2;
constexpr double beta = 2.5;

constexpr double EVAP = 0.01;
constexpr double TAU_MAX = 50;
constexpr double TAU_MIN = 0.05;