#ifndef MENU_H
#define MENU_H

#include <Adafruit_SSD1306.h>
#include <RotaryEncoder.h>

#include "MenuItem.h"

struct Node
{
public:
    MenuItem item;
    Node *next = nullptr;
    Node *prev = nullptr;

    Node(MenuItem &item) : item(item)
    {};
};

class Menu
{
private:
    Adafuit_SSD1306 *display;
    Node *head = nullptr;
    Node *tail = nullptr;
    Node *curr = nullptr;

    inline bool is_empty() const
    { return head == nullptr; };

public:
    Menu(Adafruit_SSD1306 *display);

    void insert(MenuItem item);

    void update(const RotaryEncoder::Direction &dir);

    void update_display();

    MenuItem &get()
    { return curr->item; }; // TODO error handling

};

#endif // MENU_H
