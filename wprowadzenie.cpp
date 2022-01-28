#include <iostream>

class NumbersContainer {
public:
    using size_type = int;
    using value_type = int;

    NumbersContainer(size_type max_size)
     : max_size(max_size),
       count(0),
       numbers(new value_type[max_size]) {
    }

    NumbersContainer(NumbersContainer &&other)
     : max_size(other.max_size),
       count(other.count),
       numbers(other.numbers) {
           other.numbers = nullptr;
    }

    /* remember of rule of three/five */
    // ...

    void add(value_type value) {
        if (count >= max_size) {
            // thorw
        }
        else {
            numbers[count] = value;
            count++;
        }
    }

    void print_content() {
        for (size_type i = 0; i < count; ++i) {
            std::cout << "Content pos: " << i << " value: " << numbers[i] << '\n';
        }
    }

    ~NumbersContainer() {
        delete [] numbers;
    }

private:
    size_type max_size;
    size_type count;
    value_type *numbers;
};

NumbersContainer&&
my_move(NumbersContainer &other) {
    return static_cast<NumbersContainer&&>(other);
}

int main() {
    NumbersContainer containerA(10);

    containerA.add(1);
    containerA.add(3);
    containerA.add(2);

    containerA.print_content();

    NumbersContainer &container_ref = static_cast<NumbersContainer&>(containerA);
    container_ref.add(4);

    containerA.print_content();


    NumbersContainer containerB(my_move(containerA));

    containerB.print_content();

    return 0;
}
