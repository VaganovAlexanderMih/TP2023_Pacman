#pragma once

#include <iostream>
#include <filesystem>
#include <gtest/gtest.h>
#include "GameCore.hpp"
#include "Maps.hpp"

bool CheckIfFileExists(const std::string& path);

class GameInitTests: public ::testing::Test {

};

class RequirentmentFilesExist: public ::testing::Test {

};