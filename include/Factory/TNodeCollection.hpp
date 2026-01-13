//
// Created by frane on 13.01.2026.
//

#ifndef TNODECOLLECTION_HPP
#define TNODECOLLECTION_HPP

#endif //TNODECOLLECTION_HPP

#include "types.hpp"
#include <vector>

//Definicje metod klasy szablonowej muszą znajdować się w pliku nagłówkowym.
template<typename Node>

class NodeCollection{

  public:
    using container_t = std::vector<Node>;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;

    void add(Node&& node);
    const_iterator find_by_id(ElementID id) const;
    iterator find_by_id(ElementID id);
    void remove_by_id(ElementID id);

    [[nodiscard]] iterator begin() const;
    [[nodiscard]] iterator end() const;
    [[nodiscard]] const_iterator cbegin() const;
    [[nodiscard]] const_iterator cend() const;

    private:
      container_t nodes_;
};