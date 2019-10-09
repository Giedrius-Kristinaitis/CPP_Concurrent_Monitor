#include "monitor.h"
#include "data.h"
#include <omp.h>
#include <iostream>

using namespace std;

/**
 * Class constructor
 */
Monitor::Monitor(int size) {
    this->size = size;
    this->count = 0;

    this->initializeData();

    omp_init_lock(&this->lock);
}

/**
 * Class destructor
 */
Monitor::~Monitor() {
    this->destroyData();

    omp_destroy_lock(&this->lock);
}

/**
 * Adds an element to the monitor (in the correct position based on sort order)
 */
void Monitor::add(Data data) {
    while (this->count == this->size) {
        // spin-wait while the data array is full
    }

    omp_set_lock(&this->lock);

    int index = this->getIndex(data);

    this->shiftElements(index);

    this->data[index] = data;

    this->count++;

    omp_unset_lock(&this->lock);
}

/**
 * Removes and returns the last element from the data array
 */
Data* Monitor::pop() {
    Data* data;

    while (this->count == 0 && this->willHaveMoreData) {
        // spin-wait while there is no data
    }

    if (this->count == 0 && !this->willHaveMoreData) {
        return nullptr;
    }

    omp_set_lock(&this->lock);

    data = &this->data[this->count - 1];

    this->count--;

    Data* copy = new Data;

    if (data != nullptr) {
        copy->setTitle(data->getTitle());
        copy->setPrice(data->getPrice());
        copy->setQuantity(data->getQuantity());
    }

    omp_unset_lock(&this->lock);

    if(data == nullptr){
        return data;
    } else {
        return copy;
    }
}

/**
 * Gets the correct position of an element based on it's sort order
 */
int Monitor::getIndex(Data data) {
    int index = 0;

    for (int i = 0; i < this->count; i++) {
        int compareResult = this->data[i].compareTo(data);

        if (compareResult <= 0) {
            index = i + 1;
        } else {
            break;
        }
    }

    return index;
}

/**
 * Shifts all elements to the right starting from the specified index
 */
void Monitor::shiftElements(int index) {
    for (int i = this->size - 1; i > index; i--) {
        this->data[i] = this->data[i - 1];
    }
}

/**
 * Returns the element at the specified index
 */
Data* Monitor::get(int index) {
    return &this->data[index];
}

/**
 * Gets the number of elements in the monitor
 */
int Monitor::getSize() {
    return this->count;
}

/**
 * Sets the will have more data flag
 */
void Monitor::setWillHaveMoreData(bool willHaveMoreData) {
    this->willHaveMoreData = willHaveMoreData;
}

/**
 * Clears the monitor
 */
void Monitor::clear() {
    this->count = 0;
    this->willHaveMoreData = true;
}

/**
 * Initializes the inner data array
 */
void Monitor::initializeData() {
    this->data = new Data[size];
}

/**
 * Destroys the inner data array
 */
void Monitor::destroyData() {
    delete[] this->data;
}
