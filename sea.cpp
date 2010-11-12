#include "sea.h"
#include "animal.h"
#include "fish.h"
#include "shark.h"

Sea::Sea() {
    this->Configure(100, 100, 1000, 10, 10);
    this->garbage = QVector<Animal *>();
}

Sea::Sea(unsigned int width, unsigned int height, unsigned int simulation_turns, unsigned int starting_fishes, unsigned int starting_sharks) {
    this->Configure(width, height, simulation_turns, starting_fishes, starting_sharks);
    this->garbage = QVector<Animal *>();
}

void Sea::Init() {
    Animal::setSea(this);
}

void Sea::Configure(unsigned int width, unsigned int height, unsigned int simulation_turns, unsigned int starting_fishes, unsigned int starting_sharks) {
    this->width = width;
    this->height = height;
    this->simulation_turns = simulation_turns;
    this->turns_left = simulation_turns;
    this->starting_fishes = starting_fishes;
    this->starting_sharks = starting_sharks;
}

void Sea::Populate() {
    unsigned int i;
    for(i = 0; i < this->starting_fishes; i++)
        new Fish();
    for(i = 0; i < this->starting_sharks; i++)
        new Shark();
}

Animal * Sea::Get(int x, int y) {
    // if x < 0, we get the position from the other side of the grid.
    // same for y
    return this->grid[(x < 0 ? this->width - x : x)][(y < 0 ? this->height - y : y)];
}

void Sea::Delete(Animal *animal) {
    this->Set(animal->getX(), animal->getY(), NULL);
    this->garbage.push_back(animal);
}

void Sea::Clean() {
    Animal * current = this->garbage.first();
    while(current != NULL) {
        this->garbage.pop_front();
        delete current;
        current = this->garbage.first();
    }
}

void Sea::Move(Animal *animal, int x, int y) {
    this->Set(animal->getX(), animal->getY(), NULL);
    int posX = (x < 0 ? this->width - x : x);
    int posY = (y < 0 ? this->height - y : y);
    this->Set(posX, posY, animal);
    animal->setX(posX);
    animal->setY(posY);
}