#include <iostream>
#include "SFML/Graphics.hpp"
#include "atoms.hpp"
#include <random>
#include <iostream>
int main() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> random(1,1000);
    sf::RenderWindow wind;
    wind.create(sf::VideoMode(1600,900),"My window");
    wind.setFramerateLimit(60);
    AtomNet at;
    AtomChain ac;
    //ac.arrangeChain();
    at.arrangeNet();
    auto atoms = ac.getAtoms();
    at.disturb(0, Point2D{30,30});
    int counter = 0;
    while(wind.isOpen()) {
        sf::Event event{};
        while (wind.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                wind.close();
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                //ac.setPos(0,sf::Mouse::getPosition(wind).x, sf::Mouse::getPosition(wind).y);
                //ac.setVel(0,0,0);
            }
        }
        wind.clear(sf::Color::Black);
        atoms = at.getAtoms();
        for(auto atom:atoms){
            sf::CircleShape cr(3);
            cr.setFillColor(sf::Color::White);
            //std::cout<<"x: " << (float)atom.get_pos().x_<<" y: " <<(float)atom.get_pos().y_<<std::endl;
            cr.setPosition((float)atom.get_pos().x_,(float)atom.get_pos().y_ );
            wind.draw(cr);
        }
        if(counter == 100){
            //ac.disturb(0, Point2D{0,-20});
            //at.disturb(random(rng));
        }
        counter+=1;
        at.simNetwork();
        wind.display();
    }
}
































//    sf::RenderWindow wind;
//    Player player;
//    Physics phys;
//    Map map;
//    map.initMap();
//    wind.create(sf::VideoMode(1600,900),"My window");
//    wind.setFramerateLimit(60);
//    sf::Texture* wall_texture = new sf::Texture;
//    sf::Texture* background_text = new sf::Texture;
//    background_text->loadFromFile(getCurrentPath()+"\\textures\\grass_field.jpg");
//    sf::Sprite bckgSprt(*background_text);
//    sf::View view;
//    view.setSize(1600,900);
//    while(wind.isOpen()){
//        sf::Event event;
//        while(wind.pollEvent(event)){
//            if (event.type == sf::Event::Closed){
//                wind.close();
//            }
//            if(event.type == sf::Event::KeyPressed){
//                if(event.key.code == sf::Keyboard::Space){
//                    phys.jumpPlayer(player);
//                }
//            }
//
//        }
//        view.setCenter(player.getLocation());
//        phys.accelerateByPlayer(player);
//        phys.accByGravity(player);
//        phys.applyPhysics(player);
//        phys.collisionDetection(player,map);
//        bckgSprt.setPosition(view.getCenter().x - 800, view.getCenter().y - 450);
//        wind.setView(view);
//        wind.clear(sf::Color::Cyan);
//        wind.draw(bckgSprt);
//        map.drawMap(wind);
//        wind.draw(player.getSprite());
//        wind.display();
//    }
//    delete  wall_texture;
//    delete background_text;
//    return 0;//    sf::RenderWindow wind;
////    Player player;
////    Physics phys;
////    Map map;
////    map.initMap();
////    wind.create(sf::VideoMode(1600,900),"My window");
////    wind.setFramerateLimit(60);
////    sf::Texture* wall_texture = new sf::Texture;
////    sf::Texture* background_text = new sf::Texture;
////    background_text->loadFromFile(getCurrentPath()+"\\textures\\grass_field.jpg");
////    sf::Sprite bckgSprt(*background_text);
////    sf::View view;
////    view.setSize(1600,900);
////    while(wind.isOpen()){
////        sf::Event event;
////        while(wind.pollEvent(event)){
////            if (event.type == sf::Event::Closed){
////                wind.close();
////            }
////            if(event.type == sf::Event::KeyPressed){
////                if(event.key.code == sf::Keyboard::Space){
////                    phys.jumpPlayer(player);
////                }
////            }
////
////        }
////        view.setCenter(player.getLocation());
////        phys.accelerateByPlayer(player);
////        phys.accByGravity(player);
////        phys.applyPhysics(player);
////        phys.collisionDetection(player,map);
////        bckgSprt.setPosition(view.getCenter().x - 800, view.getCenter().y - 450);
////        wind.setView(view);
////        wind.clear(sf::Color::Cyan);
////        wind.draw(bckgSprt);
////        map.drawMap(wind);
////        wind.draw(player.getSprite());
////        wind.display();
////    }
////    delete  wall_texture;
////    delete background_text;
////    return 0;