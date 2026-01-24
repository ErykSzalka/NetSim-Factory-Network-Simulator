//
// Created by eszal on 24.01.2026.
//
#include "IO/io_fun.hpp"

#include <sstream>

#include "Package/PackageQueue.hpp"
static PackageQueueType queue_type(const std::string& s) {
    return s == "FIFO" ? PackageQueueType::FIFO : PackageQueueType::LIFO;
}
static std::vector<std::string> split(const std::string& s, char d) {
    std::stringstream ss(s);
    std::string part;
    std::vector<std::string> out;
    while (std::getline(ss, part, d))
        out.push_back(part);
    return out;
}
ParsedLineData parse_line(std::string& line) {
    std::stringstream ss(line);
    std::string tok;
    std::vector<std::string> tokens;
    while (ss >> tok)
        tokens.push_back(tok);

    std::map<std::string, ElementType> types{
            {"LOADING_RAMP", ElementType::RAMP},
            {"WORKER", ElementType::WORKER},
            {"STOREHOUSE", ElementType::STOREHOUSE},
            {"LINK", ElementType::LINK}
    };

    ParsedLineData data;
    data.element_type = types.at(tokens[0]);

    for (size_t i = 1; i < tokens.size(); ++i) {
        auto kv = split(tokens[i], '=');
        data.parameters[kv[0]] = kv[1];
    }

    return data;
}
static void link_nodes(Factory& f, const std::map<std::string, std::string>& p) {
    auto src = split(p.at("src"), '-');
    auto dst = split(p.at("dest"), '-');

    IPackageReceiver* receiver =
        (dst[0] == "worker")
            ? static_cast<IPackageReceiver*>(&*f.find_worker_by_id(std::stoi(dst[1])))
            : static_cast<IPackageReceiver*>(&*f.find_storehouse_by_id(std::stoi(dst[1])));

    if (src[0] == "ramp")
        f.find_ramp_by_id(std::stoi(src[1]))->receiver_preferences_.add_receiver(receiver);
    else
        f.find_worker_by_id(std::stoi(src[1]))->receiver_preferences_.add_receiver(receiver);
}
Factory load_factory_structure(std::istream& is) {
    Factory f;
    std::string line;

    while (std::getline(is, line)) {
        if (line.empty() || line[0] == ';')
            continue;

        auto p = parse_line(line);

        if (p.element_type == ElementType::RAMP) {
            f.add_ramp(Ramp(std::stoi(p.parameters.at("id")),
                            std::stoi(p.parameters.at("delivery-interval"))));
        } else if (p.element_type == ElementType::WORKER) {
            f.add_worker(Worker(std::stoi(p.parameters.at("id")),
                                std::stoi(p.parameters.at("processing-time")),
                                std::make_unique<PackageQueue>(
                                    queue_type(p.parameters.at("queue-type")))));
        } else if (p.element_type == ElementType::STOREHOUSE) {
            f.add_storehouse(Storehouse(std::stoi(p.parameters.at("id"))));
        } else {
            link_nodes(f, p.parameters);
        }
    }

    return f;
}

static std::string qstr(PackageQueueType t) {
    return t == PackageQueueType::FIFO ? "FIFO" : "LIFO";
}

static void dump_links(std::stringstream& ss,
                       const PackageSender& sender,
                       const ElementID id,
                       const std::string& name) {
    for (const auto& p : sender.receiver_preferences_.get_preferences()) {
        ss << "LINK src=" << name << "-" << id
           << " dest="
           << (p.first->get_receiver_type() == ReceiverType::WORKER ? "worker-" : "store-")
           << p.first->get_id()
           << "\n";
    }
}

void save_factory_structure(Factory& f, std::ostream& os)
{
    std::stringstream ss;

    // LOADING RAMPS
    for (auto it = f.ramp_cbegin(); it != f.ramp_cend(); ++it) {
        ss << "LOADING_RAMP id=" << it->get_id()
           << " delivery-interval=" << it->get_delivery_interval()
           << "\n";
    }

    // WORKERS
    for (auto it = f.worker_cbegin(); it != f.worker_cend(); ++it) {
        ss << "WORKER id=" << it->get_id()
           << " processing-time=" << it->get_processing_duration()
           << " queue-type="
           << (it->get_queue()->get_queue_type() == PackageQueueType::FIFO
                   ? "FIFO"
                   : "LIFO")
           << "\n";
    }

    // STOREHOUSES
    for (auto it = f.storehouse_cbegin(); it != f.storehouse_cend(); ++it) {
        ss << "STOREHOUSE id=" << it->get_id() << "\n";
    }

    // LINKS FROM RAMPS
    for (auto it = f.ramp_cbegin(); it != f.ramp_cend(); ++it) {
        for (const auto& p : it->receiver_preferences_.get_preferences()) {
            ss << "LINK src=ramp-" << it->get_id()
               << " dest="
               << (p.first->get_receiver_type() == ReceiverType::WORKER
                       ? "worker-"
                       : "store-")
               << p.first->get_id()
               << "\n";
        }
    }

    // LINKS FROM WORKERS
    for (auto it = f.worker_cbegin(); it != f.worker_cend(); ++it) {
        for (const auto& p : it->receiver_preferences_.get_preferences()) {
            ss << "LINK src=worker-" << it->get_id()
               << " dest="
               << (p.first->get_receiver_type() == ReceiverType::WORKER
                       ? "worker-"
                       : "store-")
               << p.first->get_id()
               << "\n";
        }
    }

    os << ss.str();
}