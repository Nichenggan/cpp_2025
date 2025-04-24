//
// Created by aminoç　　 on 25-4-9.
//
#include "hero.h"
#include "gamedata.h"



Hero::Hero(int x, int y, int direction, bool inversed, int speed, int height, int attackRange, int attackDamage, Key moveLeft, Key moveRight, Key changeGravity, Key attackKey, Color color, std::string texture) :
        posX(x), posY(y), direction(direction), inversed(inversed), speed(speed), height(height), attackRange(attackRange), attackDamage(attackDamage) ,moveLeft(moveLeft), moveRight(moveRight), changeGravity(changeGravity), attackKey(attackKey), color(color), texture(texture) {}

void Hero::drawHero() const {
    G2D::drawCircle(V2(this->posX, this->posY), 5, Color::Green, true);
    // Calculate the vertices of the equilateral triangle
    std::vector<V2> PointList;
    int halfBase = this->height / 2; // Half the base length of the trian
    if (this->direction == 1 && this->inversed == true) { // Facing right
        PointList.push_back(V2(this->posX, this->posY)); // Top vertex
        PointList.push_back(V2(this->posX, this->posY - this->height)); // Bottom-left vertex
        PointList.push_back(V2(this->posX + halfBase, this->posY - this->height/2)); // Bottom-right vertex
    } else if (this->direction == 0 && this->inversed == true) { // Facing left
        PointList.push_back(V2(this->posX, this->posY)); // Top vertex
        PointList.push_back(V2(this->posX, this->posY - this->height)); // Bottom-right vertex
        PointList.push_back(V2(this->posX - halfBase, this->posY - this->height/2)); // Bottom-left vertex
    } else if (this->direction == 1 && this->inversed == false) {
        PointList.push_back(V2(this->posX, this->posY)); // buttom vertex
        PointList.push_back(V2(this->posX, this->posY + this->height)); // Bottom-right vertex
        PointList.push_back(V2(this->posX + halfBase, this->posY + this->height/2));
    } else {
        PointList.push_back(V2(this->posX, this->posY)); // buttom vertex
        PointList.push_back(V2(this->posX, this->posY + this->height)); // Bottom-right vertex
        PointList.push_back(V2(this->posX - halfBase, this->posY + this->height/2));
    }
        // Draw the triangle
        G2D::drawPolygon(PointList, this->color, true);

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
    if (G2D::isKeyPressed(this->attackKey) && (G2D::elapsedTimeFromStartSeconds() - this->T_attack > 0.5)) {
        this->T_attack = G2D::elapsedTimeFromStartSeconds();
        bool inRange;
        bool inHeight;


        if (this->direction == 1) {
            inRange = (h.posX >= this->posX && h.posX <= this->posX + this->attackRange);
        } else {
            inRange = (h.posX <= this->posX && h.posX >= this->posX - this->attackRange);
        }

        if (this->inversed) {
            inHeight = (h.posY <= this->posY + 10) && (h.posY >= this->posY - this->height);
        } else {
            inHeight = (h.posY >= this->posY - 10) && (h.posY <= this->posY + this->height);
        }

        if (inRange && inHeight) {
            h.health -= 10;
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

void Hero::drawPic(V2 pos) const {
    static int Texture = -1; // Static variable to store the texture ID
    if (Texture == -1) { // Load the texture only if it hasn't been loaded yet
        Texture = G2D::ExtractTextureFromPNG("../texture/img.png", Transparency::None);
        if (Texture < 0) {
            std::cerr << "Failed to load texture: ../texture/img.png" << std::endl;
            return;
        }
    }
    G2D::drawRectWithTexture(Texture, pos, V2(100, 200), 0);
}






