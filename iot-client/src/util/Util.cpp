//
// Created by julian on 24.05.18.
//

#include "Util.h"

#include <boost/filesystem.hpp>
#include <boost/dll/runtime_symbol_info.hpp>

#include <fstream>
#include <iostream>

const std::string Util::CONFIGURATION_FILE = buildDataFilePath("configuration.json"); // NOLINT

nlohmann::json Util::readConfig() {
    if(!boost::filesystem::exists(CONFIGURATION_FILE)) {
        throw std::runtime_error(CONFIGURATION_FILE + " is missing");
    }

    std::ifstream stream(CONFIGURATION_FILE);

    nlohmann::json json;

    stream >> json;

    return json;
}

void Util::writeConfig(const nlohmann::json &config) {
    std::ofstream ofs(CONFIGURATION_FILE, std::ofstream::out | std::ofstream::trunc);

    ofs << config.dump(2) << std::endl;
}

void Util::checkConfig(const nlohmann::json &config, const std::vector<std::string> &attributes) {
    for(const auto& attribute : attributes) {
        if(config.find(attribute) == config.end()) {
            throw std::runtime_error(CONFIGURATION_FILE + " is missing " + attribute + " attribute");  // NOLINT
        }
    }
}

std::string Util::buildDataFilePath(const std::string &fileStr) {
    auto programLocation = boost::dll::program_location();
    programLocation = programLocation.remove_filename();

    boost::filesystem::path dir(DATA_DIR_RELATIVE);
    boost::filesystem::path file(fileStr);

    auto fullPath = programLocation / dir / file;

    fullPath = fullPath.lexically_normal();

    return fullPath.string();
}
