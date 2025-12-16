#ifndef OOP_TEXTUI_H
#define OOP_TEXTUI_H

#include <string>
#include <iostream>
#include <vector>

class TextUI {
public:
    static void drawHeader(const std::string& title);
    static void drawMenu(const std::vector<std::string>& options);
    static void drawProgressBar(double percent);
    static std::string centerText(const std::string& text, int width);
};

#endif