#pragma once

#include <map>
#include <algorithm>
#include <vector>
#include <cmath>
#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
#include <thread>
#include <stack>
#include <memory>
#include <utility>
#include <cmath>
#include <queue>
#include <set>
#include <iomanip>
#include <random>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <cassert>
#include <chrono>
#include <regex>
#include <ranges>
#include <future>
#include <filesystem>
#include "json.hpp"

using json = nlohmann::json;
namespace fs = std::filesystem;
#include <SFML/Graphics.hpp>

#define CURL_STATICLIB

#include "curl/curl.h"

#ifdef _DEBUG
#pragma comment (lib, "curl/libcurl_a_debug.lib")
#else
#pragma comment (lib, "curl/libcurl_a.lib")
#endif
#pragma comment (lib, "Normaliz.lib")
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Wldap32.lib")
#pragma comment (lib, "advapi32.lib")
#pragma comment (lib, "crypt32.lib")


class stdafx
{
};

