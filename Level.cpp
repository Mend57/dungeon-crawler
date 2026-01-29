#include "Level.h"
#include <fstream>
#include "GraphicalUI.h"
#include "Tiles/Door.h"
#include "Tiles/Pit.h"
#include "Tiles/Portal.h"
#include "Tiles/Ramp.h"
#include "Tiles/Switch.h"
#include "Tiles/Levelchanger.h"
#include "Tiles/Lootchest.h"

Level::Level(const int height, const int width, AbstractController* ui, std::string map, std::string filename) : height(height), width(width), ui(ui), map(map), filename(filename) {
    tileMap.resize(height);
    for (int row = 0; row < height; ++row) tileMap[row].resize(width, nullptr);
    int counter = 0;
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            switch (map[counter]) {
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
                break;
            case '?':
                tileMap[row][col] = new Switch(row, col);
                break;
            case 'O':
                tileMap[row][col] = new Portal(row, col);
                break;
            case 'E':
                tileMap[row][col] = new Levelchanger(row, col, this);
                break;
            case 'V':
                tileMap[row][col] = new Lootchest(row, col);
                break;
            default:
                break;
            }
            counter++;
        }
    }
    std::ifstream in(filename);
    std::string line;
    while (std::getline(in, line)) {
        if (line == "#PORTALS") bindPortals(in, line);
        else if (line == "#CHARACTERS") buildCharacters(in, line);
        else if (line == "#SWITCHES") bindSwitches(in, line);
        else if (line == "#DOORS") openDoors(in, line);
    }
}

void Level::openDoors(std::ifstream& in, std::string& line) {
    while (std::getline(in, line) && !line.empty()) {
        std::vector<std::string> tokens = splitLine(line);
        int row = std::stoi(tokens.at(0)), col = std::stoi(tokens.at(1));
        Door* door = dynamic_cast<Door*>(getTile(row, col));
        if (tokens.at(2) == "open") door->notify();
    }
}

void Level::bindSwitches(std::ifstream& in, std::string& line) {
    while (std::getline(in, line) && !line.empty()){
        std::vector<std::string> tokens = splitLine(line);
        int row = std::stoi(tokens.at(0)), col = std::stoi(tokens.at(1));
        for (int i = 3; i < tokens.size(); i+=3) {
            int passiveRow = std::stoi(tokens.at(i)), passiveCol = std::stoi(tokens.at(i+1));
            dynamic_cast<Active*> (getTile(row, col))->attach(dynamic_cast<Passive*>(getTile(passiveRow, passiveCol)));
        }
    }
}

void Level::buildCharacters(std::ifstream& in, std::string& line) {
    while (std::getline(in, line) && !line.empty()) {
        std::vector<std::string> tokens = splitLine(line);
        std::string type = tokens.at(0);
        int row = std::stoi(tokens.at(1)), col = std::stoi(tokens.at(2));
        std::string controller = tokens.at(3);
        int currentHP = std::stoi(tokens.at(4));
        AbstractController* charController = nullptr;
        int strength = 0, stamina = 0;
        if (controller == "player") {
            charController = ui;
            strength = 10, stamina = 20;
        } else if (controller == "stationary") {
            charController = new StationaryController();
            strength = 10, stamina = 10;
        } else if (controller == "guard") {
            charController = new GuardController();
            strength = 5, stamina = 5;
            dynamic_cast<GuardController*>(charController)->setIndex(std::stoi(tokens.at(5)));
        }
        if (charController == nullptr) continue;
        Character* character = new Character(getTile(row, col), charController, strength, stamina);
        character->setHitpoints(currentHP);
        placeCharacter(character, row, col);
        if (type == "main") setMainCharacter(character);
    }
}

void Level::bindPortals(std::ifstream& in, std::string& line) {
    int portalTextureCounter = 0;
    while (std::getline(in, line) && !line.empty()){
        std::vector<std::string> tokens = splitLine(line);
        int row = std::stoi(tokens.at(0)), col = std::stoi(tokens.at(1));
        int destRow = std::stoi(tokens.at(2)), destCol = std::stoi(tokens.at(3));
        Portal* currentPortal = dynamic_cast<Portal*>(getTile(row, col));
        Portal* destPortal = dynamic_cast<Portal*>(getTile(destRow, destCol));
        currentPortal->setDestination(destPortal), destPortal->setDestination(currentPortal);
        int textureIndex = (portalTextureCounter) % GraphicalUI::getPortalTextures().size();
        currentPortal->setLabel(textureIndex), destPortal->setLabel(textureIndex);
        portalTextureCounter++;
    }
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
    mainCharacters.push_back(character);
    character->isMainCharacter();
    addCharacter(character);
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

std::vector<std::string> Level::splitLine(const std::string& line, char delimiter) {
    std::vector<std::string> tokens;
    size_t start = 0, end;
    while ((end = line.find(delimiter, start)) != std::string::npos) {
        tokens.push_back(line.substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(line.substr(start));
    return tokens;
}

Level* Level::CSVLoader(AbstractController* ui, const std::string& filename) {
    int height = 0, width = 0;
    std::ifstream in(filename);
    std::string line;
    std::string map;

    while (std::getline(in, line)) {
        if (line == "#SIZE") {
            std::getline(in, line);
            std::vector<std::string> tokens = splitLine(line);
            height = std::stoi(tokens.at(1)), width = std::stoi(tokens.at(3));
        }
        else if (line == "#MAP") {
            for (int i = 0; i < height; i++) {
                std::getline(in, line);
                map += line;
            }
        }
    }
    return new Level(height, width, ui, map, filename);
}
