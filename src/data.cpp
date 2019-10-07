#include "data.h"
#include <string>

using namespace std;

Data::Data(string title, double price, int quantity) {
    this->title = title;
    this->price = price;
    this->quantity = quantity;
}

void Data::setTitle(string title) {
    this->title = title;
}

void Data::setPrice(double price) {
    this->price = price;
}

void Data::setQuantity(int quantity) {
    this->quantity = quantity;
}

void Data::setResult(char result) {
    this->result = result;
}

string Data::getTitle() {
    return this->title;
}

double Data::getPrice() {
    return this->price;
}

int Data::getQuantity() {
    return this->quantity;
}

char Data::getResult() {
    return this->result;
}

int Data::compareTo(Data data) {
    if (data->getResult() > this->result) {
        return -1;
    } else if (data->getResult() < this->result) {
        return 1;
    }

    return 0;
}
