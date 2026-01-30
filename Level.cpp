#include "Level.h"
#include <fstream>
#include <queue>

#include "GraphicalUI.h"
#include "tiles/Door.h"
#include "tiles/Pit.h"
#include "tiles/Portal.h"
#include "tiles/Ramp.h"
#include "tiles/Switch.h"
#include "tiles/Levelchanger.h"
#include "tiles/Lootchest.h"
#include "controllers/AttackController.h"

Level::Level(const int height, const int width, AbstractController* ui, std::string map, const std::string& filename) : height(height), width(width), ui(ui), map(map), filename(filename) {
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
                tileMap[row][col] = new Door(row, col, this);
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
            if (tileMap[row][col]->isWalkable()) nodes.push_back(new Node{row, col});
            counter++;
        }
    }

    for (Node* node1 : nodes) {
        for (Node* node2 : nodes) {
            if (node1 == node2) continue;
            if ((abs(node1->row - node2->row) <= 1) && (abs(node1->col - node2->col) <= 1)) graph[node1].push_back(node2);
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

Level::~Level() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) delete tileMap[i][j];
    }
    tileMap.clear();
    for (const Character* character : characters) delete character;
    characters.clear();
}

void Level::addEdge(const Tile* tile1, const Tile* tile2) {
    bool exists = false;
    Node* node1 = getNode(tile1->getRow(), tile1->getColumn());
    Node* node2 = getNode(tile2->getRow(), tile2->getColumn());
    if (!node1 || !node2 || node1 == node2) return;

    for (const Node* node : graph[node1]) {
        if (node == node2) {
            exists = true;
            break;
        }
    }
    if (!exists) graph[node1].push_back(node2);

    exists = false;
    for (const Node* node : graph[node2]) {
        if (node == node1) {
            exists = true;
            break;
        }
    }
    if (!exists) graph[node2].push_back(node1);
}

void Level::removeEdge(const Tile* tile1, const Tile* tile2) {
    Node* node1 = getNode(tile1->getRow(), tile1->getColumn());
    Node* node2 = getNode(tile2->getRow(), tile2->getColumn());
    if (!node1 || !node2 || node1 == node2) return;

    auto& neighbors1 = graph[node1];
    std::erase(neighbors1, node2);

    auto& neighbors2 = graph[node2];
    std::erase(neighbors2, node1);
}

void Level::openDoors(std::ifstream& in, std::string& line) {
    while (std::getline(in, line) && !line.empty()) {
        std::vector<std::string> tokens = splitLine(line);
        const int row = std::stoi(tokens.at(0)), col = std::stoi(tokens.at(1));
        Door* door = dynamic_cast<Door*>(getTile(row, col));
        if (tokens.at(2) == "open") door->notify();
        for (int deltaRow = -1; deltaRow <= 1; ++deltaRow) {
            for (int deltaCol = -1; deltaCol <= 1; ++deltaCol) {
                if (deltaRow == 0 && deltaCol == 0) continue;
                Tile* neighborTile = getTile(row + deltaRow, col + deltaCol);
                if (neighborTile && neighborTile->isWalkable()) door->addAdjacent(neighborTile);
            }
        }
    }
}

void Level::bindSwitches(std::ifstream& in, std::string& line) {
    while (std::getline(in, line) && !line.empty()){
        std::vector<std::string> tokens = splitLine(line);
        const int row = std::stoi(tokens.at(0)), col = std::stoi(tokens.at(1));
        for (int i = 3; i < tokens.size(); i+=3) {
            const int passiveRow = std::stoi(tokens.at(i)), passiveCol = std::stoi(tokens.at(i+1));
            dynamic_cast<Active*> (getTile(row, col))->attach(dynamic_cast<Passive*>(getTile(passiveRow, passiveCol)));
        }
    }
}

void Level::buildCharacters(std::ifstream& in, std::string& line) {
    while (std::getline(in, line) && !line.empty()) {
        std::vector<std::string> tokens = splitLine(line);
        const std::string& type = tokens.at(0);
        const int row = std::stoi(tokens.at(1)), col = std::stoi(tokens.at(2));
        const std::string& controller = tokens.at(3);
        const int currentHP = std::stoi(tokens.at(4));
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
        else if (controller == "attack") {
            charController = new AttackController(this, getTile(row, col));
            strength = 5, stamina = 5;
        }
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
        const int row = std::stoi(tokens.at(0)), col = std::stoi(tokens.at(1));
        const int destRow = std::stoi(tokens.at(2)), destCol = std::stoi(tokens.at(3));
        Portal* currentPortal = dynamic_cast<Portal*>(getTile(row, col));
        Portal* destPortal = dynamic_cast<Portal*>(getTile(destRow, destCol));
        currentPortal->setDestination(destPortal), destPortal->setDestination(currentPortal);
        const int textureIndex = (portalTextureCounter) % GraphicalUI::getPortalTextures().size();
        currentPortal->setLabel(textureIndex), destPortal->setLabel(textureIndex);
        portalTextureCounter++;
    }
}

Tile* Level::getTile(const int row, const int col){
    if (row < 0 || row >= height || col < 0 || col >= width) return nullptr;
    return tileMap[row][col];
}

const Tile* Level::getTile(const int row, const int col) const {
    if (row < 0 || row >= height || col < 0 || col >= width) return nullptr;
    return tileMap[row][col];
}

void Level::placeCharacter(Character* c, const int row, const int col) {
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
    for (const Character* ch : characters) if (ch == character) return;
    if (character->isCharacterPlayer()) {
        characters.insert(characters.begin(), character);
        return;
    }
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

std::vector<Tile*> Level::getPath(const Tile* from, const Tile* to) {
    std::vector<Tile*> path;
    if (!from || !to) return path;
    Node* start = getNode(from->getRow(), from->getColumn());
    Node* goal = getNode(to->getRow(), to->getColumn());
    if (!start || !goal) return path;
    for (Node* node : nodes) {
        node->dist = INT_MAX;
        node->prev = nullptr;
        node->visited = false;
    }
    start->dist = 0;
    auto cmp = [](const Node* a, const Node* b) { return a->dist > b->dist; };
    std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> pq(cmp);
    pq.push(start);
    while (!pq.empty()) {
        Node* current = pq.top();
        pq.pop();
        if (current->visited) continue;
        current->visited = true;
        if (current == goal) break;
        for (Node* neighbor : graph[current]) {
            if (neighbor->visited) continue;
            const int newDist = current->dist + 1;
            if (newDist < neighbor->dist) {
                neighbor->dist = newDist;
                neighbor->prev = current;
                pq.push(neighbor);
            }
        }
    }

    const Node* current = goal;
    while (current != nullptr) {
        Tile* t = getTile(current->row, current->col);
        if (!t) break;
        path.push_back(t);
        current = current->prev;
    }

    std::ranges::reverse(path);
    return path;
}
