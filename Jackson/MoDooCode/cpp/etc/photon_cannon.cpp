#include <iostream>
#include <string.h>

class Photon_Cannon {
    int hp, shield;
    int coord_x, coord_y;
    int damage;

    char *name;

  public:
    Photon_Cannon(int x, int y);
    Photon_Cannon(int x, int y, const char *cannon_name);
    Photon_Cannon(const Photon_Cannon& pc);
    ~Photon_Cannon();

    void show_status();
};

Photon_Cannon::Photon_Cannon(int x, int y) {
    hp = shield = 100;
    coord_x = x;
    coord_y = y;
    damage = 20;

    name = NULL;
    std::cout << "일반 생성자 호출 ! " << std::endl;
}

Photon_Cannon::Photon_Cannon(int x, int y, const char *cannon_name) {
  hp = shield = 100;
  coord_x = x;
  coord_y = y;
  damage = 20;
  name = new char[strlen(cannon_name) + 1];
  strcpy(name, cannon_name);
  std::cout << "일반 생성자 호출 ! " << std::endl;

}

Photon_Cannon::Photon_Cannon(const Photon_Cannon& pc) {
    hp = pc.hp;
    shield = pc.shield;
    coord_x = pc.coord_x;
    coord_y = pc.coord_y;
    damage = pc.damage;
    if (pc.name) {
      name = new char[strlen(pc.name) + 1];
      strcpy(name, pc.name);
    }
    std::cout << "복사 생성자 호출 ! " << std::endl;
}

Photon_Cannon::~Photon_Cannon() {
  if (name) delete[] name;
}

void Photon_Cannon::show_status() {
    std::cout << "Photon Cannon " << std::endl;
    std::cout << " Location : ( " << coord_x << "  , " << coord_y << " ) " << std::endl;
    std::cout << " HP : " << hp << std::endl;
}

int main() {
    Photon_Cannon pc1(3, 3, "Cannon");
    Photon_Cannon pc2(pc1);
    Photon_Cannon pc3 = pc2;

    pc1.show_status();
    pc2.show_status();

    return 0;
}