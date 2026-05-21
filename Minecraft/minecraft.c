#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <termios.h>
#include <stdlib.h>

static struct termios old_termios, new_termios;

typedef struct Vector
{
    float x;
    float y;
    float z;
} vect;

typedef struct Vector2
{
    float psi;
    float phi;
} vect2;

typedef struct Vector_vector2{
    vect pos;
    vect2 view;
} player_pos_view;


void init_terminal() {
    tcgetattr(STDIN_FILENO, &old_termios);
    new_termios = old_termios;
    new_termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
    fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL, 0) | O_NONBLOCK);
    fflush(stdout);

}

void restart_terminal() {
   tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
   printf("Terminal Restored");

}

static char keystate[256] = {0};

void process_input() {
    char c;
    for (int i  = 0; i < 256; i++) {
        keystate[i] = 0;
    }
    while(read(STDIN_FILENO, &c, 1) > 0) {
        printf("\ninput: %c", c);
        unsigned char uc = (unsigned char)c;
        keystate[uc] = 1;
    }
}

int is_key_pressed(char key) {
    return keystate[(unsigned char) key];
}

char** init_picture() {
    return NULL;
}
char*** init_blocks() {
    return NULL;
}

player_pos_view init_posview(){
    player_pos_view posview;
    posview.pos.x = 5;
    posview.pos.y = 5;
    posview.pos.z = 5;
    posview.view.phi = 0;
    posview.view.psi = 0;
}

int main() {
    init_terminal();
    char** picture = init_picture();
    char*** blocks = init_blocks();
    player_po_view posview = init_posview();
    while(1) {
        process_input();
        usleep(20000);
        if(is_key_pressed('q')) {
            exit(0);
        }
    }
    restart_terminal();
    return 0;
}