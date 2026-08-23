#pragma once

// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <string>

// PATH UTILS DEFINITION ---------------------------------------------------------------------------------------------------------------------------|
namespace klarion::detail {
    void ensure_parent_directory_exists(const std::string& path);
}
