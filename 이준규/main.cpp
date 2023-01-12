#include "game.h"
int main() {
    Game game;
    game.init();
    while (1) {
        game.titleDraw();
        int menuCode = game.menuDraw();
        if (menuCode == 0) {

        }
        else if (menuCode == 1) {
            game.infoDraw();
        }
        else if (menuCode == 2) {
            return 0;
        }
        system("cls");
    }
    return 0;
}