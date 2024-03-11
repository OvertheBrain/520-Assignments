#ifndef __BULLET_AGENT__H
#define __BULLET_AGENT__H 

#include "enviro.h"

using namespace enviro;

class BulletController : public Process, public AgentInterface {

    public:
    BulletController() : Process(), AgentInterface() {}

    void init() {
        notice_collisions_with("enemy", [&](Event &e) {
            remove_agent(id());
        });
        notice_collisions_with("Chaser", [&](Event &e) {
            remove_agent(id());
        });
    }
    void start() {}
    void update() {
        // Auto-dead after a certain distance
        if ( counter++ > 20 ) {
            remove_agent(id());
        }
    }
    void stop() {}

    double counter;
};

class Bullet : public Agent {
    public:
    Bullet(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    BulletController c;
};

DECLARE_INTERFACE(Bullet)

#endif