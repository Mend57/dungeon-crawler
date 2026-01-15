#include "Level.h"
#include "GraphicalUI.h"
#include "Tiles/Door.h"
#include "Tiles/Pit.h"
#include "Tiles/Portal.h"
#include "Tiles/Ramp.h"
#include "Tiles/Switch.h"
#include "Tiles/Levelchanger.h"

Level::Level(const int height, const int width, AbstractController* ui, std::string levelDesign) : height(height), width(width), l(levelDesign) {
    tileMap.resize(height);
    for (int row = 0; row < height; ++row) {
        tileMap[row].resize(width, nullptr);
    }
    std::vector<Portal*> portal;
    std::vector<Passive*> passiveObjects;
    Switch* switchTile = nullptr;
    int counter = 0;
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            switch (l[counter]) {
                case '.':
                    tileMap[row][col] = new Floor(row, col);
                    break;
                case '<':
                    tileMap[row][col] = new Ramp(row, col);
                    break;
                case '_':
                    tileMap[row][col] = new Pit(row, col);
                    break;
                case '#':
                    tileMap[row][col] = new Wall(row, col);
                    break;
                case 'X':
                    tileMap[row][col] = new Door(row, col);
                    passiveObjects.push_back(dynamic_cast<Passive*>(tileMap[row][col]));
                    break;
                case '?':
                    tileMap[row][col] = new Switch(row, col);
                    switchTile = dynamic_cast<Switch*>(tileMap[row][col]);
                    break;
                case 'O':{
                    tileMap[row][col] = new Portal(row, col);
                    portal.push_back(dynamic_cast<Portal*>(tileMap[row][col]));
                    break;
                }
                case 'E':{
                    tileMap[row][col] = new Levelchanger(row, col, this);
                    break;
                }
                default:
                    break;
            }
            counter++;
        }
    }
    for (int i = 0; i < portal.size(); i+=2) {
        portal[i]->setDestination(portal[i+1]);
        portal[i+1]->setDestination(portal[i]);

        int textureIndex = (i / 2) % GraphicalUI::getPortalTextures().size();
        portal[i]->setLabel(textureIndex);
        portal[i+1]->setLabel(textureIndex);
    }
    if (switchTile != nullptr) for (Passive* passiveObj : passiveObjects) switchTile->attach(passiveObj);
}


Level::~Level() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            delete tileMap[i][j];
        }
    }
    tileMap.clear();

    for (Character* character : characters) {
        delete character;
    }
    characters.clear();
}

Tile* Level::getTile(int row, int col){
    if (row < 0 || row >= height || col < 0 || col >= width) return nullptr;
    return tileMap[row][col];
}

const Tile* Level::getTile(int row, int col) const {
    if (row < 0 || row >= height || col < 0 || col >= width) return nullptr;
    return tileMap[row][col];
}

void Level::placeCharacter(Character* c, int row, int col) {
    if (row < 0 || row >= height || col < 0 || col >= width || c == nullptr) return;
    Tile* tile = getTile(row, col);
    if (tile == nullptr || tile->getTexture() != ".") return;
    tile->setCharacter(c);

    c->setTile(tile);
    addCharacter(c);
}

void Level::setMainCharacter(Character* character){
    mainCharacter = character;
    character->isMainCharacter();
    addCharacter(mainCharacter);
}

void Level::addCharacter(Character* character) {
    for (Character* ch : characters) if (ch == character) return;
    characters.push_back(character);
}

void Level::removeCharacter(Character* character) {
    std::erase(characters, character);
    character->getTile()->setCharacter(nullptr);
    delete character;
}
