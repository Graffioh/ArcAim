#pragma once

#include <chrono>

// window size
constexpr unsigned int WIN_WIDTH = 800;
constexpr unsigned int WIN_HEIGHT = 600;

// countdown
constexpr float COUNTDOWN = 20;

// target spawn timer
constexpr float TARGET_SPAWN_TIMER = 1.f;

// max targets spawnable
constexpr unsigned int MAX_TARGETS = 5;

// player health
constexpr unsigned int PLAYER_HEALTH = 100;

// game status
constexpr char GAME_START = '1';
constexpr char GAME_OPTIONS = '2';
constexpr char GAME_EXIT = '3';
constexpr char GAME_RESUME = '4';

// difficulty types
constexpr char DIFFICULTY_EASY = '1';
constexpr char DIFFICULTY_MEDIUM = '2';
constexpr char DIFFICULTY_HARD = '3';

// crosshair styles
constexpr char CROSS_STYLE1 = '4';
constexpr char CROSS_STYLE2 = '5';
constexpr char CROSS_STYLE3 = '6';

//back button
constexpr char GAME_GOBACK = '7';

// spawn type
constexpr char REFLEX_ENEMIES = '1';
constexpr char FALLING_ENEMIES = '2';

// frame duration for frame indipendent gameplay
constexpr std::chrono::microseconds FRAME_DURATION(3333);

