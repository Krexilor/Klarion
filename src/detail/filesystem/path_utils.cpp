// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <filesystem>

// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/detail/filesystem/path_utils.hpp"

// PATH UTILS IMPLEMENTATION -----------------------------------------------------------------------------------------------------------------------|
namespace klarion::detail {
    void ensure_parent_directory_exists(const std::string& path) {
        std::filesystem::path p(path);
        std::filesystem::path parent = p.parent_path();

        if (parent.empty()) {
            return;
        }

        std::error_code ec;
        std::filesystem::create_directories(parent, ec);
    }
}
