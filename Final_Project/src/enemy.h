#ifndef __ENEMY_AGENT__H
#define __ENEMY_AGENT__H 

#include "enviro.h"

using namespace enviro;

class enemyController : public Process, public AgentInterface {

    public:
    enemyController() : Process(), AgentInterface() {}

    void init() {
        notice_collisions_with("Bullet", [&](Event &e) {
            life -= 2;
        });
        notice_collisions_with("Attacker", [&](Event &e) {
            remove_agent(id());
        });
        
        // Modify the level according to GM
        watch("levelup", [this](Event e) {
            level = e.value()["level"];
        });
    }
    void start() {}
    void update() {
        // Killed by bullet
        if(life <= 0){
            remove_agent(id());
        }

        track_velocity(9 + level, 0);
    }
    void stop() {}

    int life = 8;
    int level = 1;
};

class enemy : public Agent {
    public:
    enemy(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    enemyController c;
};

DECLARE_INTERFACE(enemy)

#endif