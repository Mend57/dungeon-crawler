#include "Character.h"
#include "GraphicalUI.h"

void Character::setLabel(){
    if (isPlayer) {
        if (moveDirection.getDx() == 1) label->setPixmap(GraphicalUI::getCharacterTexture("char_right_2"));
        else if (moveDirection.getDx() == -1) label->setPixmap(GraphicalUI::getCharacterTexture("char_left_2"));
        else if (moveDirection.getDy() == -1) label->setPixmap(GraphicalUI::getCharacterTexture("char_back_2"));
        else label->setPixmap(GraphicalUI::getCharacterTexture("char_front_2"));
    }
    else {
        if (moveDirection.getDx() == -1) label->setPixmap(GraphicalUI::getTexture("zombie_left"));
        else label->setPixmap(GraphicalUI::getTexture("zombie_right"));
    }
}