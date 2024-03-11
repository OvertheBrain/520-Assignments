#ifndef __GAME_MANAGER_AGENT__H
#define __GAME_MANAGER_AGENT__H 

#include "enviro.h"
#include <cstdlib>
#include <ctime>

using namespace enviro;

class GameManagerController : public Process, public AgentInterface {

    public:
    GameManagerController() : Process(), AgentInterface() {}

    void init() {
        srand(static_cast<unsigned int>(time(0)));

        watch("atk_move", [&](Event &e) {
            atk_id = e.value()["id"];
        });

        // Click the game buttons
        watch("button_click", [&](Event &e) {
            auto k = e.value()["name"].get<std::string>();
            if (k == "restart") {
                // Respawn the player
                remove_agent(atk_id);
                Agent& ag = add_agent("Attacker", 
                        0,
                        200, 
                        0,
                        { 
                            {"fill", "blue"}, 
                            {"stroke", "#888"}, 
                            {"strokeWidth", "5px"},
                            {"strokeOpacity", "0.25"}
                        });
                level = 1;
            } else if ( k == "level") {
                level++;
                // Increased difficulty in notifying enemy units
                emit(Event("levelup", {{"level", level}}));
            }
        });
    }
    void start() {}
    void update() {
        // Randomly generate agents
        int randomNumber = 1 + rand() % (200 / level);
        if (randomNumber == 1){
            Agent& ag = add_agent("boss", 
                        -600 + rand() % 1200, 
                        -260, 
                        1.55,
                        { 
                            {"fill", "purple"}, 
                            {"stroke", "white"}, 
                            {"strokeWidth", "5px"},
                            {"strokeOpacity", "0.25"}
                        }); 
        }
        else if (randomNumber == 2 || randomNumber == 3){
            Agent& ag = add_agent("enemy", 
                        -600 + rand() % 1200, 
                        -260, 
                        1.55,
                        { 
                            {"fill", "red"}, 
                            {"stroke", "white"}, 
                            {"strokeWidth", "5px"},
                            {"strokeOpacity", "0.25"}
                        });
        }
        else if ((randomNumber == 4)){
            Agent& ag = add_agent("booster", 
                        -500 + rand() % 1000, 
                        -200 + rand() % 400, 
                        0,
                        { 
                            {"fill", "green"}, 
                            {"stroke", "#888"}, 
                            {"strokeWidth", "5px"},
                            {"strokeOpacity", "0.25"}
                        });
        }
    }
    void stop() {}

    int level = 1;
    int atk_id;
};

class GameManager : public Agent {
    public:
    GameManager(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    GameManagerController c;
};

DECLARE_INTERFACE(GameManager)

#endif