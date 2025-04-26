#ifndef HERO_H
#define HERO_H

#include <vector>
#include "G2D.h"
#include <string>

struct GameData;

struct Hero {
    int posX;
    int posY;
    int direction = 1; // 1 = vers la droite, 0 = vers la gauche
    bool inversed = true;
    int speed = 5;
    int height = 50;
    int health = 100;
    double T_inverse = -1;
    double T_attack = -1;
    int attackRange = 80;
    int attackDamage = 10;
    Key moveLeft = Key::LEFT;
    Key moveRight = Key::RIGHT;
    Key changeGravity = Key::N;
    Key attackKey = Key::M;
    Color color = Color::Cyan;
    std::string texture;
    std::string attackEffectTexture;
    int TextureCode = -1;
    int attackEffectTextureCode = -1;




    Hero(int x, int y, int direction, bool inversed, int speed, int height, int attackRange, int attackDamage, Key moveLeft, Key moveRight, Key changeGravity, Key attackKey, Color color, std::string texture, std::string attackEffectTexture);

    void drawHero() const;

    void turn_left();

    void turn_right();

    void move_left();

    void move_right();

    void turn_over();

    bool is_movable_left (GameData &G) const;

    bool is_movable_right (GameData &G) const;

    void change_gravity();

    void fall(GameData & G);

    void movement(GameData &G);

    void attack(Hero &h);

    void drawAttackEffect() const;

    void drawPic(V2 pos) ;

    void initAsPlayer1(GameData &G);

    void initAsPlayer2(GameData &G);

};

#endif // HERO_H