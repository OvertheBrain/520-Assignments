#ifndef __ATTACKER_AGENT__H
#define __ATTACKER_AGENT__H 

#include "enviro.h"

using namespace enviro;

class AttackerController : public Process, public AgentInterface {

    public:
    AttackerController() : Process(), AgentInterface() {}

    void init() {
        // Disabled once contacting with enemies. Need to respawn.
        notice_collisions_with("enemy", [&](Event &e) {
            disabled = true;
            set_style({{"fill", "black"}});
        });
        notice_collisions_with("boss", [&](Event &e) {
            disabled = true;
            set_style({{"fill", "black"}});
            remove_agent(id());
        });
        notice_collisions_with("Chaser", [&](Event &e) {
            disabled = true;
            set_style({{"fill", "black"}});
        });

        // Speed up once getting the booster
        notice_collisions_with("booster", [&](Event &e) {
            force += 200;
        });

        // Move and Fire operations
        watch("keydown", [&](Event &e) {
            auto k = e.value()["key"].get<std::string>();
            if(!disabled){
                if ( k == " " && !firing ) {
                    // Fire operation: shoot out a bullet
                    Agent& bullet = add_agent("Bullet", 
                        x(), 
                        y() - 60, 
                        -1.6,
                        { 
                            {"fill", "yellow"}, 
                            {"stroke", "#888"}, 
                            {"strokeWidth", "2px"},
                            {"strokeOpacity", "0.25"}
                        });    
                    bullet.apply_force(300,0);

                    firing = true;
                } else if ( k == "w" ) {
                    fx = 0;
                    fy = -force;
                } else if ( k == "s" ) {
                    fx = 0;
                    fy = force;
                } else if ( k == "a" ) {
                    fx = -force;
                    fy = 0;
                } else if ( k == "d" ) {
                    fx = force;
                    fy = 0;
                } else {
                    fx = 0;
                    fy = 0;
                }
                omni_apply_force(fx,fy);
            }
        });
        watch("keyup", [&](Event &e) {
            auto k = e.value()["key"].get<std::string>();
            if ( k == " " && !disabled) {
                firing = false;
            }
        });
    }

    void start() {
        fx = 0;
        fy = 0;
    }

    void update() {
        // Update position in real time
        emit(Event("atk_move", {{"id", id()}, {"x", x()}, {"y", y()}}));

        prevent_rotation();
        omni_damp_movement();
    }

    void stop() {}

    // Respawn
    void enable() {
        disabled = false;
        set_style({{"fill", "blue"}});
    }

    double fx, fy;

    double force = 700;
    bool firing;
    bool disabled = false;
};

class Attacker : public Agent {
    public:
    Attacker(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    AttackerController c;
};

DECLARE_INTERFACE(Attacker)

#endif