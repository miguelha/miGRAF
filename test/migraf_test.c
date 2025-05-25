#include "../src/migraf.h"
#include <stdio.h>

void update(float dt){
    printf("Update: dt = %f\n", dt);
}

void draw(void){
    printf("Draw\n");
}

int main(){
    if(migraf_init("miGRAF test", 1280, 720) != 0){
        fprintf(stderr, "Initialization error.");
        return 1;
    }

    migraf_run(update, draw);

    migraf_end();
    
    return 0;
}