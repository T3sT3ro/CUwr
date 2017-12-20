//
// Created by i300791 on 20.12.17.
//

#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

#define RUNTIME_LENGTH 300.0 // 300 seconds = 5 minutes
#define REFRESH_INTERVAL 0.04 // 40 miliseconds refresh interval = 60 FPS
#define SIMULATION_INTERVAL 0.04


#define BOARD_WIDTH  120.0
#define BOARD_HEIGHT  40.0

#define G 9.81 // G constant

#define STARTING_VX 40.0 // horizontal starting velocity
#define STARTING_X 0.0 // horizontal starting position
#define STARTING_Y BOARD_HEIGHT/2.0 // vertical starting position

#define toMilis(t) ((t)/CLOCKS_PER_SEC)

struct ball_ {
    double x, y;
    double Vx, Vy;
} ball;


void moveBall(double dt) {

    // update positions based on velocities
    ball.x += ball.Vx * dt;
    ball.y += ball.Vy * dt;

    // calculate new vertical velocity from `dv=a*dt`
    ball.Vy += G * dt;


    // update position if out of bounds
    if (ball.x < 0) { // left border
        ball.x = -ball.x;
        ball.Vx *= -1; // reverse velocity vector
    }
    if (ball.y < 0) { // up border
        ball.y = -ball.y;
        ball.Vy *= -1; // reverse velocity vector
    }
    if (ball.y > BOARD_HEIGHT) { // down border
        ball.y = BOARD_HEIGHT - (ball.y - BOARD_HEIGHT);
        ball.Vy *= -1; // reverse velocity vector
    }
    if (ball.x > BOARD_WIDTH) { // right border
        ball.x = BOARD_WIDTH - (ball.x - BOARD_WIDTH);
        ball.Vx *= -1; // reverse velocity vector
    }
    if (ball.y < STARTING_Y){ // top
        ball.y = STARTING_Y;
        ball.Vy = 0.0;
    }
}


void render() {
    int ball_x = (int) ball.x;
    int ball_y = (int) ball.y;

    char buffer[(int) BOARD_WIDTH];

    for (int i = 0; i < BOARD_HEIGHT; ++i) {
        for (int j = 0; j < BOARD_WIDTH; ++j) {
            if (i == ball_y && j == ball_x)
                buffer[j] = '0';
            else if (i + 1 == BOARD_HEIGHT)
                buffer[j] = '_';
            else buffer[j] = ' ';
        }
        printf("%s\n", buffer);
        //mvprintw(i, 0, "%s\n", buffer);
    }
}

int main() {


    // init ball
    ball.Vx = STARTING_VX;
    ball.Vy = 0.0;
    ball.x = STARTING_X;
    ball.y = STARTING_Y;

    // init timer
    clock_t runtime = clock();
    clock_t t_render_0 = clock();
    clock_t t_simulation_0 = clock();
    clock_t t_elapsed = clock();

    //initscr();

    while (toMilis(runtime) < RUNTIME_LENGTH) {
        double d_simulation_t = t_elapsed - t_simulation_0;
        if (toMilis(d_simulation_t)> SIMULATION_INTERVAL) {
            moveBall(toMilis(d_simulation_t));
            t_simulation_0 = clock(); // reset zegara
        }

        double d_render_t = t_elapsed - t_render_0;
        if (toMilis(d_render_t)> REFRESH_INTERVAL) {
            render();
            t_render_0 = clock(); // reset zegara
        }
        t_elapsed = clock();
    }

    return EXIT_SUCCESS;
}

