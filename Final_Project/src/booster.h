#ifndef __BOOSTER_AGENT__H
#define __BOOSTER_AGENT__H 

#include "enviro.h"

using namespace enviro;

class boosterController : public Process, public AgentInterface {

    public:
    boosterController() : Process(), AgentInterface() {}

    void init() {
        notice_collisions_with("Attacker", [&](Event &e) {
            remove_agent(id());
        });
        notice_collisions_with("Bullet", [&](Event &e) {
            remove_agent(id());
        });
    }
    void start() {}
    void update() {
        prevent_rotation();
        damp_movement();
    }
    void stop() {}

};

class booster : public Agent {
    public:
    booster(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    boosterController c;
};

DECLARE_INTERFACE(booster)

#endif