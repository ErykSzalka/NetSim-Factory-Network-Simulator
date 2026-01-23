//
// Created by eszal on 24.01.2026.
//

#ifndef NETSIM_IO_FUN_HPP
#define NETSIM_IO_FUN_HPP
#include <map>
#include <string>

#include "Factory/Factory.hpp"

enum class ElementType { RAMP, WORKER, STOREHOUSE, LINK };

struct ParsedLineData {
    ElementType element_type;
    std::map<std::string, std::string> parameters;
};
ParsedLineData parse_line(std::string& line);
Factory load_factory_structure(std::istream& is);
void save_factory_structure(Factory& factory, std::ostream& os);

#endif //NETSIM_IO_FUN_HPP