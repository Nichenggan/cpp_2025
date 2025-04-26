//
// Created by aminoç　　 on 25-4-9.
//
#include "hero.h"
#include "gamedata.h"



Hero::Hero(int x, int y, int direction, bool inversed, int speed, int height, int attackRange, int attackDamage, Key moveLeft, Key moveRight, Key changeGravity, Key attackKey, Color color, std::string texture, std::string attackEffectTexture) :
        posX(x), posY(y), direction(direction), inversed(inversed), speed(speed), height(height), attackRange(attackRange), attackDamage(attackDamage) ,moveLeft(moveLeft), moveRight(moveRight), changeGravity(changeGravity), attackKey(attackKey), color(color), texture(texture), attackEffectTexture(attackEffectTexture) {}

void Hero::drawHero() const {
    if ((G2D::elapsedTimeFromStartSeconds() - this->T_attack < 0.2)) {
        if (this->direction == 1 && this->inversed == true) { // Facing right
            G2D::drawRectWithTexture(this->attackEffectTextureCode, V2(this->posX - 30, this->posY - this->height), V2(60, this->height), 180);
        } else if (this->direction == 0 && this->inversed == true) { // Facing left
            G2D::drawRectWithTexture(this->attackEffectTextureCode, V2(this->posX + 30, this->posY - this->height), V2(-60, this->height), 180);
        } else if (this->direction == 1 && this->inversed == false) {
            G2D::drawRectWithTexture(this->attackEffectTextureCode, V2(this->posX - 30, this->posY), V2(60, this->height), 0);
        } else {
            G2D::drawRectWithTexture(this->attackEffectTextureCode, V2(this->posX + 30, this->posY), V2(-60, this->height), 0);
        }
    } else {
        if (this->direction == 1 && this->inversed == true) { // Facing right
            G2D::drawRectWithTexture(this->TextureCode, V2(this->posX - 30, this->posY - this->height), V2(60, this->height), 180);
        } else if (this->direction == 0 && this->inversed == true) { // Facing left
            G2D::drawRectWithTexture(this->TextureCode, V2(this->posX + 30, this->posY - this->height), V2(-60, this->height), 180);
        } else if (this->direction == 1 && this->inversed == false) {
            G2D::drawRectWithTexture(this->TextureCode, V2(this->posX - 30, this->posY), V2(60, this->height), 0);
        } else {
            G2D::drawRectWithTexture(this->TextureCode, V2(this->posX + 30, this->posY), V2(-60, this->height), 0);
        }
    }


}

void Hero::turn_left() {
    this->direction = 0;
}

void Hero::turn_right() {
    this->direction = 1;
}

void Hero::move_left() {
    this->turn_left();
    this->posX -= this->speed;
}

void Hero::move_right() {
    this->turn_right();
    this->posX += this->speed;
}

void Hero::turn_over() {
    if (this->inversed) {
        this->posY -= this->height;
    } else {
        this->posY += this->height;
    }
    this->inversed = !this->inversed;
}

bool Hero::is_movable_left(GameData &G) const {
    bool border = this->posX >= 10;
    return border;
}

bool Hero::is_movable_right(GameData &G) const {
    bool border = this->posX <= G.WidthPix - 10;
    return border;
}

void Hero::change_gravity() {
    if (G2D::elapsedTimeFromStartSeconds() - this->T_inverse > 0.5) {
        this->T_inverse = G2D::elapsedTimeFromStartSeconds();
        if(this->inversed) {
            this->turn_over();
            this->inversed = false;
        }
        else {
            this->turn_over();
            this->inversed = true;
        }
    }
}

void Hero::fall(GameData & G) {
    if (G2D::elapsedTimeFromStartSeconds() - this->T_inverse < 0.5) {
        if (!this->inversed)
            this->posY = G.PosCeiling - this->height - (G.PosCeiling - this->height - G.PosFloor) * (G2D::elapsedTimeFromStartSeconds() - this->T_inverse) * 2;
        else
            this->posY = G.PosFloor + this->height + (G.PosCeiling - this->height - G.PosFloor) * (G2D::elapsedTimeFromStartSeconds() - this->T_inverse) * 2;
    } else {
        this->posY = this->inversed ? G.PosCeiling : G.PosFloor;
    }
}

void Hero::movement(GameData &G) {
    if (G2D::isKeyPressed(this->moveLeft) && this->is_movable_left(G)) {
        this->move_left();
    }
    if (G2D::isKeyPressed(this->moveRight) && this->is_movable_right(G)) {
        this->move_right();
    }
    if (G2D::isKeyPressed(this->changeGravity)) {
        this->change_gravity();
    }
    // movement
    fall(G);
}

void Hero::attack(Hero &h){
    if (G2D::isKeyPressed(this->attackKey) && (G2D::elapsedTimeFromStartSeconds() - this->T_attack > 1)) {
        this->T_attack = G2D::elapsedTimeFromStartSeconds();
        bool inRange;
        bool inHeight;


        if (this->direction == 1) {
            inRange = (h.posX >= this->posX - this->attackRange/2 && h.posX <= this->posX + this->attackRange);
        } else {
            inRange = (h.posX <= this->posX + this->attackRange/2 && h.posX >= this->posX - this->attackRange);
        }

        if (this->inversed) {
            inHeight = (h.posY <= this->posY + this->height/2) && (h.posY >= this->posY - this->height);
        } else {
            inHeight = (h.posY >= this->posY - this->height/2) && (h.posY <= this->posY + this->height);
        }

        if (inRange && inHeight) {
            h.health -= this->attackDamage;
            if (h.health < 0) {
                h.health = 0;
            }
        }
    }

}

void Hero::drawAttackEffect() const {
    if (G2D::elapsedTimeFromStartSeconds() - this->T_attack < 0.2) {
        G2D::drawCircle(V2(this->posX, this->posY), 10, Color::Red, true);
    }
}

void Hero::drawPic(V2 pos) {
    if (this->TextureCode == -1) { // Load the texture only if it hasn't been loaded yet
        this->TextureCode = G2D::ExtractTextureFromPNG(this->texture, Transparency::None);
        if (this->TextureCode < 0) {
            std::cerr << "Failed to load texture" << std::endl;
            return;
        }
    }
    G2D::drawRectWithTexture(this->TextureCode, pos, V2(60, this->height), 0);
}

void Hero::initAsPlayer1(GameData &G) {
    this->posX = 50;
    this->posY = G.PosCeiling;
    this->direction = 1;
    this->inversed = true;
    this->moveLeft = Key::A;
    this->moveRight = Key::D;
    this->changeGravity = Key::C;
    this->attackKey = Key::V;
    this->color = Color::Cyan;
    this->attackEffectTextureCode = G2D::ExtractTextureFromPNG(this->attackEffectTexture, Transparency::None);
}

void Hero::initAsPlayer2(GameData &G) {
    this->posX = G.WidthPix - 50;
    this->posY = G.PosFloor;
    this->direction = 0;
    this->inversed = false;
    this->moveLeft = Key::LEFT;
    this->moveRight = Key::RIGHT;
    this->changeGravity = Key::K;
    this->attackKey = Key::L;
    this->color = Color::Red;
    this->attackEffectTextureCode = G2D::ExtractTextureFromPNG(this->attackEffectTexture, Transparency::None);
}




