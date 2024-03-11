# Final Project
This directory organizes the final project for **EEP 520- Software Engineering for Embedded Applications** built by [**Enviro**](https://github.com/klavinslab/enviro/).

## Project Introduction
This project has developed a video game akin to the classic "Shoot 'Em Up" genre. Within a web client created using Enviro, players are able to control a blue attack unit, navigating and launching attacks to eliminate opposing enemy units.

### Game Control and Monster Guide

> #### Movement & Attack
- **Movement**: Navigate with `WASD` keys for up, down, left, and right directions.
- **Attack**: Launch missiles by pressing the `Spacebar`.

> #### Monster Types
- Standard Enemy
  - **Speed**: High
  - **Health**: 8 HP

- Boss
  - **Speed**: Slow
  - **Health**: 40 HP
  - **Special**: Can summon Chasers.

- Chaser
  - **Speed**: Slow, but tracks the player.
  - **Health**: 6 HP

- Booster
  - **Special**: Improve player's move speed once attacker touch it

> #### Gameplay Mechanics
> - Attacks from the player inflict 2 points of damage.
> - Contact with any type of enemy unit results in an immediate game over.
> - To restart the game, click the restart button located in the top-right corner.

### Increasing Game Difficulty

To enhance the challenge as you play, you can increase the game's difficulty level by clicking the green button located in the top-right corner of the game interface. With each increment in difficulty level:

- The frequency of randomly spawned enemy units will increase, making the game more challenging as more enemies appear on the screen.
- The speed of enemy units will also increase, requiring quicker reactions and strategies to navigate through or eliminate the heightened threats.

### Project Implementation

This project comprises seven agents in total: `attacker`, `enemy`, `boss`, `chaser`, `bullet`, `booster`, and `gameManager`.

- **attacker**: Represents the singleton player object, which is central to the player's interaction with the game environment.
- **gameManager**: Controls the overall progression and level of the game. This agent, along with the attacker, plays a significant role in the game's implementation.

Communication and data exchange between these agents is facilitated through the detection of collisions and player input events, as well as real-time event emissions (emit) from the `attacker` and `gameManager` (gm) objects to manage game dynamics.

## Run and Install

- **Programming Language:** C++

- **Build Environment**
  - UNIX environment
  - bash shell
  - gnu C and C++ compiler
  - make build tool
  - elam
  - enviro

Get Started
---
- **Docker**

To start easily, we use pre-build images for this project:

First run the docker command
```bash
docker run -p80:80 -p8765:8765 -v (Your directory)/Final_Project/:/source -it klavins/enviro:v1.6 bash
```
to pull the enviro image and get a `bash` prompt that allows you to run commands within the "container environment".

You will initially be placed to the `/source` directory onto which the `-v` option to docker will have mounted the default directory in your host environment. This directory and its children are the only host directories available within the container environment.

- **Enviro**

Then make the project and start the enviro server as follows:
```bash
esm start
make
enviro
```
Through these commands, you have compiled the code already and started both enviro client and server.

- **Go to Client/Game**

The `-p80:80` option maps port 80 from the Docker container to ports on your host computer. This should allow you to go to

> http://localhost with your web browser and see the ENVIRO client.

The `-p8765:8765` option allows the ENVIRO client to communicate with the **enviro server** via a WebSocket.

The command `esm start` uses the enviro setup manager to start a web server from which your browser can access the ENVRIO client.

Now that the necessary preparations have been completed, you are ready to launch the project.
Navigate to `http://localhost` you should see a game screen like this: 

![image](https://github.com/OvertheBrain/520-Assignments/assets/9031837/6e814f37-1324-47cd-bb05-06a6c69f405f)


### Now enjoy the project!





