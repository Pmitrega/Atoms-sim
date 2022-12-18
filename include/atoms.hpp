//
// Created by Paweł on 10.12.2021.
//

#ifndef SFML_GAME_1_ATOMS_HPP
#define SFML_GAME_1_ATOMS_HPP
#include <utility>
#include <vector>
class Point2D{ ;
    std::vector<int> round_to_integer();

public:
    Point2D(double x,double y):x_{x},y_{y}{}
    double x_;
    double y_;
};


class Atom{
public:
    Atom(Point2D loc, Point2D vel): loc_{loc}, vel_{vel}{}
    Point2D get_pos() const{return loc_;}
    Point2D get_vel() const{return vel_;}
    void accelerate(Point2D acc, double time);
    void move(double time);
    void setPos(double x,double y){loc_.x_ = x; loc_.y_ = y;}
    void setVel(double x,double y){vel_.x_ = x; vel_.y_ = y;}
private:
    Point2D loc_;
    Point2D vel_;
};

class Bound{
public:
    explicit Bound(std::pair<Atom*,Atom*> atom_pair, double k = 1000000):atomPair_{std::move(atom_pair)}, k_{k}{}
    double getBaseDistance() const{return base_distance_;}
    void setBaseDistance(double base_dist){base_distance_ = base_dist;}
    void actByHooke(double dtime);
private:
    const double k_;
    double base_distance_ = 20;
    std::pair<Atom*,Atom*> atomPair_;
};

class AtomNet{
public:
    AtomNet(std::vector<Atom> atoms = std::vector<Atom>{},std::vector<Bound> bounds = std::vector<Bound>{}):atoms_{std::move(atoms)}, bounds_{std::move(bounds)}{}
    std::vector<Atom> getAtoms() const {return atoms_;}
    void arrangeNet();
    void simNetwork();
    void disturb(int index, Point2D dist);
private:
    double desired_net_size = 800;
    double base_net_distance = 20;
    std::vector<Atom> atoms_;
    std::vector<Bound> bounds_;
};

class AtomChain{
public:
    AtomChain(std::vector<Atom> atoms = std::vector<Atom>{},std::vector<Bound> bounds = std::vector<Bound>{}):atoms_{std::move(atoms)}, bounds_{std::move(bounds)}{}
    void arrangeChain();
    std::vector<Atom> getAtoms() const {return atoms_;}
    void simChain();
    void disturb(int index, Point2D dist);
    void setPos(int index, double x, double y){atoms_[index].setPos(x,y);}
    void setVel(int index, double x, double y){atoms_[index].setVel(x,y);}
private:
    double desired_chain_size = 800;
    double base_chain_distance = 10;
    std::vector<Atom> atoms_;
    std::vector<Bound> bounds_;

};
#endif //SFML_GAME_1_ATOMS_HPP
