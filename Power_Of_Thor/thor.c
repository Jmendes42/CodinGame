#include <stdio.h>

int main()
{
    int light_x;    // the X position of the light of power
    int light_y;    // the Y position of the light of power
    int initial_tx; // Thor's starting X position
    int initial_ty; // Thor's starting Y position
    scanf("%d%d%d%d", &light_x, &light_y, &initial_tx, &initial_ty);

    // game loop
    while (1) {
        if (initial_ty > light_y) {
            initial_ty--;
            printf("N");
        }
        if (initial_ty < light_y) {
            initial_ty++;
            printf("S");
        }
        if (initial_tx < light_x) {
            initial_tx++;
            printf("E");
        }
        if (initial_tx > light_x) {
            initial_tx--;
            printf("W");
        }
        printf("\n");
    }
    return 0;
}
