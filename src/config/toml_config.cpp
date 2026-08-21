// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <fstream> 
#include <sstream>
#include <stdexcept>

// EXTERNAL LIBRARIES ------------------------------------------------------------------------------------------------------------------------------|
#include <toml++/toml.hpp>

// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/config/config.hpp"

// TOML CONFIG IMPLEMENTATION ----------------------------------------------------------------------------------------------------------------------|
namespace klarion {
    namespace {
        detail::ColorMode parse_color_mode(const std::string& str) {
            if (str == "always") return detail::ColorMode::Always;
            if (str == "never") return detail::ColorMode::Never;
            return detail::ColorMode::Auto;
        }

        detail::Color parse_color(const std::string& str) {
            if (str == "black") return detail::Color::Black;
            if (str == "red") return detail::Color::Red;
            if (str == "green") return detail::Color::Green;
            if (str == "yellow") return detail::Color::Yellow;
            if (str == "blue") return detail::Color::Blue;
            if (str == "magenta") return detail::Color::Magenta;
            if (str == "cyan") return detail::Color::Cyan;
            if (str == "white") return detail::Color::White;
            if (str == "bright_black") return detail::Color::BrightBlack;
            if (str == "bright_red") return detail::Color::BrightRed;
            if (str == "bright_green") return detail::Color::BrightGreen;
            if (str == "bright_yellow") return detail::Color::BrightYellow;
            if (str == "bright_blue") return detail::Color::BrightBlue;
            if (str == "bright_magenta") return detail::Color::BrightMagenta;
            if (str == "bright_cyan") return detail::Color::BrightCyan;
            if (str == "bright_white") return detail::Color::BrightWhite;
            return detail::Color::Default;
        }

        detail::Style parse_style(const std::string& str) {
            if (str == "bold") return detail::Style::Bold;
            if (str == "dim") return detail::Style::Dim;
            return detail::Style::Normal;
        }

        void parse_color_config(const toml::table& colors_table, std::map<Level, std::pair<detail::Color, detail::Style>>& level_colors) {
            for (auto&& [key, value] : colors_table) {
                Level level = level_from_string(key.str());
                std::string color_str = value.value_or<std::string>("");

                detail::Style style = detail::Style::Normal;
                detail::Color color = detail::Color::Default;

                size_t space_pos = color_str.find(' ');
                if (space_pos != std::string::npos) {
                    std::string style_str = color_str.substr(0, space_pos);
                    std::string color_part = color_str.substr(space_pos + 1);
                    style = parse_style(style_str);
                    color = parse_color(color_part);
                }
                else {
                    color = parse_color(color_str);
                }

                level_colors[level] = {color, style};
            }
        }
    }

    Config Config::from_toml_file(const std::string& path) {
        try {
            toml::table tbl = toml::parse_file(path);
            std::ostringstream oss;
            oss << tbl;
            return Config::from_toml_string(oss.str());
        }
        catch (const toml::parse_error& e) {
            throw std::runtime_error(std::string("Failed to parse TOML config: ") + e.what());
        }
    }

    Config Config::from_toml_string(const std::string& toml) {
        Config config;

        try {
            toml::table tbl = toml::parse(toml);

            // Parse default logger settings
            if (auto default_table = tbl["default"].as_table()) {
                if (auto level_val = (*default_table)["level"].as_string()) {
                    config.set_level(level_from_string(level_val->get()));
                }

                if (auto pattern_val = (*default_table)["pattern"].as_string()) {
                    config.set_pattern(pattern_val->get());
                }

                if (auto sinks_val = (*default_table)["sinks"].as_array()) {
                    for (auto&& v : *sinks_val) {
                        if (auto s = v.as_string()) {
                            config.default_sinks_.push_back(s->get());
                        }
                    }
                }
            }

            // Parse sink configurations
            if (auto sinks_table = tbl["sinks"].as_table()) {
                for (auto&& [sink_name, sink_config] : *sinks_table) {
                    if (!sink_config.is_table()) continue;

                    const auto& table = *sink_config.as_table();
                    SinkConfig sc;
                    sc.name = std::string(sink_name.str());

                    if (auto type_val = table["type"].as_string()) {
                        sc.type = type_val->get();
                    }

                    if (auto path_val = table["path"].as_string()) {
                        sc.path = path_val->get();
                    }

                    if (auto pattern_val = table["pattern"].as_string()) {
                        sc.pattern = pattern_val->get();
                    }

                    if (auto level_val = table["level"].as_string()) {
                        sc.level = level_from_string(level_val->get());
                    }

                    if (auto append_val = table["append"].as_boolean()) {
                        sc.append = append_val->get();
                    }

                    if (auto color_val = table["color"].as_string()) {
                        sc.color_mode = parse_color_mode(color_val->get());
                    }

                    if (auto colors_table = table["colors"].as_table()) {
                        parse_color_config(*colors_table, sc.level_colors);
                    }

                    config.sink_configs_.push_back(sc);
                }
            }

            // Parse named logger configurations
            if (auto loggers_table = tbl["logger"].as_table()) {
                for (auto&& [logger_name, logger_configs] : *loggers_table) {
                    if (!logger_configs.is_table()) continue;

                    const auto& table = *logger_configs.as_table();
                    LoggerConfig lc;
                    lc.name = std::string(logger_name.str());

                    if (auto level_val = table["level"].as_string()) {
                        lc.level = level_from_string(level_val->get());
                    }

                    if (auto sinks_val = table["sinks"].as_array()) {
                        for (auto&& sink_ref : *sinks_val) {
                            if (auto sink_str = sink_ref.as_string()) {
                                lc.sinks.push_back(sink_str->get());
                            }
                        }
                    }

                    if (auto pattern_val = table["pattern"].as_string()) {
                        lc.pattern = pattern_val->get();
                    }

                    config.logger_configs_.push_back(lc);
                }
            }
        }
        catch (const toml::parse_error& e) {
            throw std::runtime_error(std::string("TOML parse error: ") + e.what());
        }

        return config;
    }
}
