#ifndef CONCURRENCY_HPP
#define CONCURRENCY_HPP

class Incrementer {
public:
    Incrementer() = default;
    void increment();
    int getCount() const;

private:
    int count_ {0};
};

#endif
