#include <iostream>
#include <string>

#include <spdlog/spdlog.h>
#include <boost/program_options.hpp>

#include "utils.hpp"

namespace bpo = boost::program_options;

namespace
{
const auto g_busKey {"bus"};
const auto g_devKey {"device"};
}

int main(int argc, char** argv)
{
    spdlog::set_pattern("[%T](%l): %v");

    try
    {
        bpo::options_description desc("Allowed options");
        desc.add_options()
            ("help,h", "Print help")
            ("bus,b", bpo::value<std::string>()->required(), "I2C bus address in hex")
            ("device,d", bpo::value<std::string>()->required(), "I2C device address in hex")
            ("verbose,v", bpo::bool_switch(), "Enable verbose logs");

        bpo::variables_map vm;
        bpo::store(bpo::parse_command_line(argc, argv, desc), vm);
        bpo::notify(vm);

        if (vm.count("help") || argc < 2)
        {
            desc.print(std::cerr, 0);
            return 0;
        }

        const auto bus = vm[g_busKey].as<std::string>();
        const uint32_t busAddr = getDigitFromHex<uint32_t>(bus);

        const auto device = vm[g_busKey].as<std::string>();
        const uint8_t devAddr = getDigitFromHex<uint8_t>(device);

        const auto logLevel = vm["verbose"].as<bool>() ? spdlog::level::debug : spdlog::level::info;
        spdlog::set_level(logLevel);

        SPDLOG_INFO("Settings: bus = {}, device = {}", busAddr, devAddr);
    }
    catch (const std::exception& ex)
    {
        SPDLOG_ERROR("Error occured: {}", ex.what());
        return -1;
    }
}
