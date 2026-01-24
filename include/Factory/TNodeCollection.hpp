//
// Created by frane on 13.01.2026.
//

#ifndef TNODECOLLECTION_HPP
#define TNODECOLLECTION_HPP
#include <list>


#include "types.hpp"
#include <vector>


template<class Node>
class NodeCollection {
public:
  NodeCollection() = default;
  NodeCollection(const NodeCollection&) = delete;
  NodeCollection& operator=(const NodeCollection&) = delete;
  NodeCollection(NodeCollection&&) = default;
  NodeCollection& operator=(NodeCollection&&) = default;
  ~NodeCollection() = default;
  using container_t = std::list<Node>;
  using iterator = typename container_t::iterator;
  using const_iterator = typename container_t::const_iterator;

  void add(Node&& node) { container.emplace_back(std::move(node)); }

  void remove_by_id(ElementID id) {
    container.remove_if([id](const Node& n) { return n.get_id() == id; });
  }

  iterator find_by_id(ElementID id) {
    return std::find_if(container.begin(), container.end(),
                        [id](const Node& n) { return n.get_id() == id; });
  }

  const_iterator find_by_id(ElementID id) const {
    return std::find_if(container.cbegin(), container.cend(),
                        [id](const Node& n) { return n.get_id() == id; });
  }

  iterator begin() { return container.begin(); }
  iterator end() { return container.end(); }
  const_iterator begin() const { return container.cbegin(); }
  const_iterator end() const { return container.cend(); }
  const_iterator cbegin() const { return container.cbegin(); }
  const_iterator cend() const { return container.cend(); }

private:
  container_t container;
};
#endif //TNODECOLLECTION_HPP
