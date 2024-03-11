#ifndef __CHASER_AGENT__H
#define __CHASER_AGENT__H 

#include "enviro.h"

using namespace enviro;

class ChaserController : public Process, public AgentInterface {

    public:
    ChaserController() : Process(), AgentInterface() {}
    double goal_x, goal_y;

    void init() {
        notice_collisions_with("Bullet", [&](Event &e) {
            life -= 2;
        });
        notice_collisions_with("Attacker", [&](Event &e) {
            remove_agent(id());
        });

        // Track the posistion of attacker
        watch("atk_move", [this](Event e) {
            goal_x = e.value()["x"];
            goal_y = e.value()["y"];
        });
    }
    void start() {}
    void update() {
        if(life <= 0){
            remove_agent(id());
        }

        // Chase the attacker
        move_toward(goal_x, goal_y);
    }
    void stop() {}

    double life = 6;
};

class Chaser : public Agent {
    public:
    Chaser(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    ChaserController c;
};

DECLARE_INTERFACE(Chaser)

#endif