//
// Created by Paweł on 10.12.2021.
//

#include "atoms.hpp"
#include <cmath>
#include <iostream>
std::vector<int> Point2D::round_to_integer() {
    std::vector<int> v ={0,0};
    v[0] = (int)x_;
    v[1] = (int)y_;
    return v;
}

void AtomNet::arrangeNet() {
    const double start = 50;
    for(int i = 0; i<(int)(desired_net_size/base_net_distance);i++){
        for(int j = 0; j<(int)(desired_net_size/base_net_distance);j++){
            auto new_atom = Atom(Point2D{200+start + i*base_net_distance,start+j*base_net_distance}, Point2D{0,0});
            atoms_.push_back(new_atom);
        }
    }

    int count = 0;
    for (int i = 0; i < atoms_.size();i++){
        for (int j = i; j < atoms_.size();j++){
            double distance = 100000000.0;
            if(i != j){
                distance = sqrt(pow((atoms_[i].get_pos().x_ - atoms_[j].get_pos().x_),2)+pow((atoms_[i].get_pos().y_ - atoms_[j].get_pos().y_),2));
                if(distance < base_net_distance+1) {
                    count++;
//                    std::cout<<"found"<<count<<std::endl;
                    std::pair<Atom *, Atom *> new_pair(&atoms_[i], &atoms_[j]);
                    Bound new_bound(new_pair);
                    new_bound.setBaseDistance(base_net_distance);
                    bounds_.push_back(new_bound);
                }
            }

        }
    }


}

void AtomNet::simNetwork() {
    const double dtime = 0.0001;
    for(auto bound:bounds_){
        bound.actByHooke(dtime);
    }
    for(auto atom = atoms_.begin();atom<atoms_.end();atom++){
        atom->move(dtime);
    }

}

void AtomNet::disturb( int index, Point2D dist) {
    auto cpos = atoms_[index].get_pos();
    atoms_[index].setPos(cpos.x_+dist.x_,cpos.y_+dist.y_);
}

void Bound::actByHooke(double dtime) {
    const double damping = 0.1;
    double distance = sqrt(pow((atomPair_.first->get_pos().x_-atomPair_.second->get_pos().x_),2) + pow((atomPair_.first->get_pos().y_-atomPair_.second->get_pos().y_),2));
    double base_force = (base_distance_-distance)*k_;
    double sin = (atomPair_.first->get_pos().y_-atomPair_.second->get_pos().y_)/distance;
    double cos = (atomPair_.first->get_pos().x_-atomPair_.second->get_pos().x_)/distance;
    double force_x_first = base_force * cos;
    double force_y_first = base_force * sin;

    double first_damping_x = - damping * atomPair_.first->get_vel().x_;
    double first_damping_y = - damping * atomPair_.first->get_vel().y_;
    double second_damping_x = - damping * atomPair_.second->get_vel().x_;
    double second_damping_y = - damping * atomPair_.second->get_vel().y_;
    Point2D acc_first(force_x_first + first_damping_x, force_y_first + first_damping_y);
    Point2D acc_second(-force_x_first + second_damping_x,-force_y_first + second_damping_y);
    atomPair_.first->accelerate(acc_first,dtime);
    atomPair_.second->accelerate(acc_second,dtime);
}

void Atom::accelerate(Point2D acc, double time) {
    vel_.y_ += acc.y_ *time;
    vel_.x_ += acc.x_ *time;
}

void Atom::move(double time) {
    loc_.x_ = loc_.x_ + vel_.x_*time;
    loc_.y_ =loc_.y_ + vel_.y_*time;
}

void AtomChain::arrangeChain() {
    double chain_beg = 300;
    for(int i = 0; i < desired_chain_size/base_chain_distance; i++){
        Atom new_atom(Point2D{chain_beg + i * base_chain_distance,chain_beg}, Point2D{0,0});
        atoms_.push_back(new_atom);
    }
    for(int i = 0; i < (atoms_.size()-1); i++){
        Bound new_bound(std::pair<Atom*,Atom*>{&atoms_[i], &atoms_[i+1]});
        new_bound.setBaseDistance(base_chain_distance);
        bounds_.push_back(new_bound);
    }
}

void AtomChain::simChain() {
    const double dtime = 0.0001;
    for(auto bound:bounds_){
        bound.actByHooke(dtime);
    }
    for(auto atom_it =atoms_.begin();atom_it<atoms_.end();atom_it++){
        atom_it->move(dtime);
    }


}
void AtomChain::disturb( int index, Point2D dist) {
    auto cpos = atoms_[index].get_pos();
    atoms_[index].setPos(cpos.x_+dist.x_,cpos.y_+dist.y_);
}