#ifndef __BOSS_AGENT__H
#define __BOSS_AGENT__H 

#include "enviro.h"

using namespace enviro;

class bossController : public Process, public AgentInterface {

    public:
    bossController() : Process(), AgentInterface() {}

    void init() {
        notice_collisions_with("Bullet", [&](Event &e) {
            life -= 2;
        });

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

        if(counter++ % 47 == 0){
            // Create a chaser to chase attacker timely
            Agent& chaser = add_agent("Chaser", 
                        x() + 40, 
                        y() + 50, 
                        0,
                        { 
                            {"fill", "pink"}, 
                            {"stroke", "#888"}, 
                            {"strokeWidth", "4px"},
                            {"strokeOpacity", "0.25"}
                        }); 
        }

        prevent_rotation();
        track_velocity(7 + level, 0);
    }
    void stop() {}

    double life = 40;
    int level = 1;
    long int counter;
};

class boss : public Agent {
    public:
    boss(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    bossController c;
};

DECLARE_INTERFACE(boss)

#endif