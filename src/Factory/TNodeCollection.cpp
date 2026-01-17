//
// Created by frane on 17.01.2026.
//
#include "Factory\TNodeCollection.hpp"
template<typename Node>
typename NodeCollection<Node>::const_iterator

NodeCollection<Node>::find_by_id(ElementID id) const{
  return std::find_if(cbegin(), cend(),
         [id](const Node& node){return node.get_id() == id;});
}

template<typename Node>
typename NodeCollection<Node>::iterator

NodeCollection<Node>::find_by_id(ElementID id) {
    return std::find_if(begin(), end(),
           [id](const Node& node){return node.get_id() == id;});
}


template<typename Node>

void NodeCollection<Node>::remove_by_id(ElementID id){
  auto it = find_by_id(id);

  if(it != nodes_.end()){
    nodes_.erase(it);
    }
}