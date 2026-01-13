//
// Created by frane on 12.01.2026.
//

#ifndef FACTORY_H
#define FACTORY_H

#endif //FACTORY_H
#include "Factory/TNodeCollection.hpp"
#include "package/types.hpp"

class Factory {

  public:
    Factory();

    //Ramps
    void add_ramp(Ramp&& ramp);
    void remove_ramp(Ramp&& ramp);
    NodeCollection<Ramp>::iterator find_ramp_by_id(ElementID id);
    NodeCollection<Ramp>::const_iterator find_ramp_by_id(ElementID id) const;
    NodeCollection<Ramp>::const_iterator ramp_cbegin() const;
    NodeCollection<Ramp>::const_iterator ramp_cend() const;

    //Workers
    void add_worker(Worker&& worker);
    void remove_worker(Worker&& worker);
    NodeCollection<Worker>::iterator find_worker_by_id(ElementID id);
    NodeCollection<Worker>::const_iterator find_worker_by_id(ElementID id) const;
    NodeCollection<Worker>::const_iterator worker_cbegin() const;
    NodeCollection<Worker>::const_iterator worker_cend() const;

    //Storehouses
    void add_storehouse(Storehouse&& storehouse);
    void remove_storehouse(Storehouse&& storehouse);
    NodeCollection<Storehouse>::iterator find_storehouse_by_id(ElementID id);
    NodeCollection<Storehouse>::const_iterator find_storehouse_by_id(ElementID id) const;
    NodeCollection<Storehouse>::const_iterator storehouse_cbegin() const;
    NodeCollection<Storehouse>::const_iterator storehouse_cend() const;


    bool is_consistent() const;
    void do_dekiveries();
    void do_package_passing();
    void do_work();

    ~Factory();

    private:
      NodeCollection<Ramp> ramps_;            //klasy z zadania 'Węzły sieci'
      NodeCollection<Worker> workers_;
      NodeCollection<Storehouses> storehouses_;

      void remove_receiver(NodeCollection<Node>& collection, ElementID id);
};