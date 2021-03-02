#pragma once

#pragma warning(disable: 4244)
#pragma warning(disable: 26812)

#define DLL_EXPORT extern "C" __declspec(dllexport)
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <functional>
#include <mutex>
#include <string>
#include <vector>

using namespace std::literals;

#include "utils/pointer.hpp"
#include "utils/memory.hpp"
#include "utils/hook.hpp"
#include "utils/string.hpp"

#include "game/chaiscript/chaiscript.hpp"
#include "game/structs.hpp"
#include "game/variables.hpp"
#include "game/functions.hpp"

#include "component/scheduler.hpp"
#include "component/command.hpp"
