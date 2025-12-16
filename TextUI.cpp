#include "TextUI.h"
#include <iomanip>

void TextUI::drawHeader(const std::string& title) {
    std::string border(40, '=');
    std::cout << "\n" << border << "\n";
    std::cout << centerText(title, 40) << "\n";
    std::cout << border << "\n";
}

void TextUI::drawMenu(const std::vector<std::string>& options) {
    std::cout << "\n";
    for (size_t i = 0; i < options.size(); ++i) {
        std::cout << " [" << (i + 1) << "] " << options[i] << "\n";
    }
    std::cout << "\nSelectie: ";
}

void TextUI::drawProgressBar(double percent) {
    int width = 20;
    int filled = static_cast<int>(width * (percent / 100.0));
    if (filled > width) filled = width;
    if (filled < 0) filled = 0;

    std::cout << "[";
    for (int i = 0; i < width; ++i) {
        if (i < filled) std::cout << "#";
        else std::cout << "-";
    }
    std::cout << "] " << static_cast<int>(percent) << "%\n";
}

std::string TextUI::centerText(const std::string& text, int width) {
    int len = static_cast<int>(text.length());
    if (len >= width) return text;
    
    int padding = (width - len) / 2;
    std::string res;
    res.append(padding, ' ');
    res.append(text);
    res.append(padding, ' ');
    
    if (res.length() < static_cast<size_t>(width)) {
        res.push_back(' ');
    }
    return res;
}