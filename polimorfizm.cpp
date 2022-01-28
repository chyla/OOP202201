#include <iostream>
#include <string>
#include <fstream>
#include <memory>

struct ITransmitter {
    // czy moge zrobic implementacje funkcji (cialo funkcji) send() w klasie ITransmitter?
    virtual void send(const std::string &text) = 0;
    virtual ~ITransmitter() = default;
};


struct Transmitter : ITransmitter {
    Transmitter() {
        std::cout << "[Transmitter] creating...\n";
    }

    void send(const std::string &text) override {
        std::cout << "[Transmitter] sending: " << text << '\n';
    }

    ~Transmitter() {
        std::cout << "[Transmitter] destroying...\n";
    }
};

struct Receiver {
    Receiver() {
        std::cout << "[Receiver] creating...\n";
    }

    std::string receive() {
        std::string text = "Received text.";
        return text;
    }

    ~Receiver() {
        std::cout << "[Receiver] destroying...\n";
    }
};


struct Radio : Transmitter, Receiver {
    Radio() {
    }

    void send(const std::string &text) override {
        std::cout << "[Radio] sending...\n";
        constexpr int num_of_chars_to_send = 10;
        for (std::string::size_type i = 0;
             i < text.length();
             i += num_of_chars_to_send) {
            if (i + num_of_chars_to_send > text.length()) {
                Transmitter::send(text.substr(i, text.length() - i));
            }
            else {
                Transmitter::send(text.substr(i, num_of_chars_to_send));
            }
        }
    }
};



int main() {
    std::unique_ptr<Radio> radio = std::make_unique<Radio>();
    radio->send("Hello, hello, hello, hello.");

    return 0;
}
