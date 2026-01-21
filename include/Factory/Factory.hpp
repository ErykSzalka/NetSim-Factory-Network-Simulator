//
// Created by frane on 12.01.2026.
//

#ifndef FACTORY_H
#define FACTORY_H

#endif //FACTORY_H
#include "Factory/TNodeCollection.hpp"
#include "types.hpp"
#include "Nodes/Ramp.hpp"
#include "Nodes/Worker.hpp"
#include "Nodes/Storehouse.hpp"
#include "package/Package.hpp"

class Factory {

  public:
    Factory() = default;
	~Factory() = default;

    //Ramps
    void add_ramp(Ramp&& ramp){
      ramps_.add(std::move(ramp));
      }
    void remove_ramp(Ramp&& ramp){
      ramps_.remove_by_id(ramp.get_id());
      }
    NodeCollection<Ramp>::iterator find_ramp_by_id(ElementID id){
      return ramps_.find_by_id(id);
      }
    NodeCollection<Ramp>::const_iterator find_ramp_by_id(ElementID id) const{
      return ramps_.find_by_id(id);
      }
    NodeCollection<Ramp>::const_iterator ramp_cbegin() const{
      return ramps_.cbegin();
      }
    NodeCollection<Ramp>::const_iterator ramp_cend() const{
      return ramps_.cend();
      }


    //Workers
    void add_worker(Worker&& worker){
      workers_.add(std::move(worker));
      }
    void remove_worker(Worker&& worker){
      workers_.remove_by_id(worker.get_id());
      }
    NodeCollection<Worker>::iterator find_worker_by_id(ElementID id){
      return workers_.find_by_id(id);
      }
    NodeCollection<Worker>::const_iterator find_worker_by_id(ElementID id) const{
      return workers_.find_by_id(id);
      }
    NodeCollection<Worker>::const_iterator worker_cbegin() const{
      return workers_.cbegin();
      }
    NodeCollection<Worker>::const_iterator worker_cend() const{
      return workers_.cend();
      }


    //Storehouses
    void add_storehouse(Storehouse&& storehouse){
      storehouses_.add(std::move(storehouse));
      }
    void remove_storehouse(Storehouse&& storehouse){
      workers_.remove_by_id(storehouse.get_id());
      }
    NodeCollection<Storehouse>::iterator find_storehouse_by_id(ElementID id){
      return storehouses_.find_by_id(id);
      }
    NodeCollection<Storehouse>::const_iterator find_storehouse_by_id(ElementID id) const{
      return storehouses_.find_by_id(id);
      }
    NodeCollection<Storehouse>::const_iterator storehouse_cbegin() const{
      return storehouses_.cbegin();
	  }
    NodeCollection<Storehouse>::const_iterator storehouse_cend() const{
      return storehouses_.cend();
      }

	//Special methods
    void do_deliveries(){
      for (Ramp& ramp : ramps_){ramp.deliver_goods(time_);}
      }
    void do_package_passing();
    void do_work(){
      for (Worker& worker : workers_){worker.do_work(time_);}
      }
    bool is_consistent() const;


    private:
      NodeCollection<Ramp> ramps_;
      NodeCollection<Worker> workers_;
      NodeCollection<Storehouse> storehouses_;
      Time time_;      //Nie wiem czy powinienem robić to pole,
                       // jesli tak to pewnie potrzebne metody do ustawiania time_

      template<typename Node>
      void remove_receiver(NodeCollection<Node>& collection, ElementID id);
};