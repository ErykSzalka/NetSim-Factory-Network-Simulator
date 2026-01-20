//
// Created by frane on 12.01.2026.
//
#include "Factory/Factory.hpp"

bool has_reachable_storehouse(const PackageSender* sender, std::map<const PackageSender*, NodeColor>& node_colors) {

    if (node_colors[sender] == NodeColor::VERIFIED){
        return true;
    }

    node_colors[sender] = NodeColor::VISITED;
    const auto& prefs = sender->receiver_preferences_;

    if (prefs.begin() == prefs.end()) {
        throw std::logic_error("Sender has no receivers");
    }

    bool has_nonself_receiver = false;
    for (const auto& receiver : prefs) {
        IPackageReceiver* receiver_ptr = receiver.first;

        if (receiver_ptr->get_receiver_type() == ReceiverType::STOREHOUSE) {
            has_nonself_receiver = true;
            continue;
        }

        if (receiver_ptr->get_receiver_type() == ReceiverType::WORKER) {

            Worker* worker_ptr = dynamic_cast<Worker*>(receiver_ptr);
            PackageSender* sendercv_ptr = dynamic_cast<PackageSender*>(worker_ptr);

            if (sendercv_ptr == sender) {  //na wypadek wysylania do samego siebie, nie powinno sie zdarzyć
               continue;
            }
            has_nonself_receiver = true;

            if (node_colors[sendercv_ptr] == NodeColor::UNVISITED) {
              has_reachable_storehouse(sendercv_ptr, node_colors);
            }
        }
    }

    node_colors[sender] = NodeColor::VERIFIED;
    if (has_nonself_receiver) {
        return true;
    }
    throw std::logic_error("Sender has no reachable storehouse");
}


bool Factory::is_consistent() const {

  std::map<const PackageSender*, NodeColor> node_colors;

  for (auto it = ramps_.cbegin(); it != ramps_.cend(); ++it) {
      node_colors[dynamic_cast<const PackageSender*>(&(*it))] = NodeColor::UNVISITED;
  }

  for (auto it = workers_.cbegin(); it != workers_.cend(); ++it) {
      node_colors[dynamic_cast<const PackageSender*>(&(*it))] = NodeColor::UNVISITED;
  }

  try {
       for(auto it = ramps_.cbegin(); it != ramps_.cend(); ++it) {
         has_reachable_storehouse(dynamic_cast<const PackageSender*>(&(*it)), node_colors);
       }
  }
  catch(const std::logic_error&) {
    return false;
  }


  return true;
}