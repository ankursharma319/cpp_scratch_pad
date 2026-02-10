#include "concurrency.hpp"

void Incrementer::increment() {
    ++count_;
}

int Incrementer::getCount() const {
    return count_;
}
