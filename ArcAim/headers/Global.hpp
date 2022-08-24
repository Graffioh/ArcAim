#pragma once

#include <chrono>

// window size
constexpr unsigned int WIN_WIDTH = 800;
constexpr unsigned int WIN_HEIGHT = 600;

// countdown
constexpr float COUNTDOWN = 20;

// target spawn timer
constexpr float TARGET_SPAWN_TIMER = 0.5f;

// max targets spawnable
constexpr unsigned int MAX_TARGETS = 5;

// player health
constexpr unsigned int PLAYER_HEALTH = 800;

// game status
constexpr char GAME_START = '1';
constexpr char GAME_OPTIONS = '2';
constexpr char GAME_EXIT = '3';
constexpr char GAME_RESUME = '4';

// spawn type
constexpr char REFLEX_ENEMIES = '1';
constexpr char FALLING_ENEMIES = '2';

// frame
constexpr std::chrono::microseconds FRAME_DURATION(3333);

