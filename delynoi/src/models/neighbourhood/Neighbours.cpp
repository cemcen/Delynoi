#include <delynoi/models/neighbourhood/Neighbours.h>

Neighbours::Neighbours() {}

Neighbours::Neighbours(int i1) {
    this->n1 = i1;
}

Neighbours::Neighbours(int i1, int i2) {
    this->n1 = i1;
    this->n2 = i2;
}

Neighbours::Neighbours(Pair<int> p) {
    this->n1 = p.first;
    this->n2 = p.second;
}

void Neighbours::setNeighbour(int i) {
    this->n2 = i;
}

int Neighbours::getFirst() const{
    return this->n1;
}

int Neighbours::getSecond() const{
    return this->n2;
}

std::string Neighbours::getString() const {
    return utilities::toString<double>(this->n1) + " " + utilities::toString<double>(this->n2);
}

bool Neighbours::operator==(const Neighbours &other) const{
    return this->getFirst()==other.getFirst() && this->getSecond()==other.getSecond() ||
           this->getFirst()==other.getSecond() && this->getSecond()==other.getFirst();
}

