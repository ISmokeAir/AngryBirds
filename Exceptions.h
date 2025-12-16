#ifndef OOP_EXCEPTIONS_H
#define OOP_EXCEPTIONS_H

#include <exception>
#include <string>


class GameException : public std::exception {
protected:
    std::string mesaj;
public:
    explicit GameException(std::string msg) : mesaj(std::move(msg)) {}
    [[nodiscard]] const char* what() const noexcept override {
        return mesaj.c_str();
    }
};


class InputException : public GameException {
public:
    explicit InputException(const std::string& msg) : GameException("Eroare Input: " + msg) {}
};


class FileException : public GameException {
public:
    explicit FileException(const std::string& filename)
        : GameException("Eroare Fisier: Nu s-a putut deschide " + filename) {}
};


class LogicException : public GameException {
public:
    explicit LogicException(const std::string& msg) : GameException("Eroare Logica: " + msg) {}
};

#endif //OOP_EXCEPTIONS_H