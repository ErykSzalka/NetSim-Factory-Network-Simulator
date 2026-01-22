//
// Created by frane on 13.01.2026.
//

#ifndef TNODECOLLECTION_HPP
#define TNODECOLLECTION_HPP

#endif //TNODECOLLECTION_HPP

#include "types.hpp"
#include <vector>


template<typename Node>

class NodeCollection{

  public:
    using container_t = std::vector<Node>;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;


    void add(Node&& node){
		nodes_.push_back(std::move(node));
    }

    const_iterator find_by_id(ElementID id) const;
    iterator find_by_id(ElementID id);

    void remove_by_id(ElementID id);

    [[nodiscard]] iterator begin(){
      return nodes_.begin();
      }
    [[nodiscard]] iterator end(){
      return nodes_.end();
      }
    [[nodiscard]] iterator begin() const{
      return nodes_.begin();
      }
    [[nodiscard]] const_iterator end() const{
      return nodes_.end();
      }
    [[nodiscard]] const_iterator cbegin() const{
      return nodes_.cbegin();
      }
    [[nodiscard]] const_iterator cend() const{
      return nodes_.cend();
      }

    private:
      container_t nodes_;
};