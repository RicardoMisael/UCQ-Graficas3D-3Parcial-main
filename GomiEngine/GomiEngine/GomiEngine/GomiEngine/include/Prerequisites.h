#pragma once

// Librer?as STD
#include <iostream> 
#include <string> 
#include <sstream> 
#include <vector> 
#include <thread>
#include <map>
#include <fstream> 
#include <unordered_map>

// Third Parties
#include <SFML/Graphics.hpp>
#include "Memory/TSharedPointer.h"
#include "Memory/TStaticPtr.h"
#include "Memory/TUniquePtr.h"
#include "Memory/TWeakPointer.h"

// Libreria Matematica
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"

// Imgui
#include <imgui.h>
#include <imgui-SFML.h>

// Enums
enum
    ShapeType {
    EMPTY = 0,
    CIRCLE = 1,
    RECTANGLE = 2,
    TRIANGLE = 3
};

enum
    ConsolErrorType {
    NORMAL = 0,
    WARNING = 1,
    ERROR = 2
};

// MACRO for safe release of resources 
#define SAFE_PTR_RELEASE(x) if(x != nullptr) { delete x; x = nullptr; }

#define MESSAGE(classObj, method, state)                      \
{                                                             \
    std::ostringstream os_;                                   \
    os_ << classObj << "::" << method << " : "                \
        << "[CREATION OF RESOURCE" << ": " << state << "] \n";\
    std::cerr << os_.str();                                   \
}                                                      

#define ERROR(classObj, method, errorMSG)                   \
{                                                           \
  std::ostringstream os_;                                   \
  os_ << "ERROR: " << classObj << "::" << method << " : "   \
    << " Error in data from params [" << errorMSG << "] \n"; \
  std::cerr << os_.str();                                   \
  exit(1);                                                  \
}                                