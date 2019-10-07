#include "monitor.h"
#include "data.h"

using namespace std;

/**
 * Class constructor
 */
Monitor::Monitor(int size) {
    this->data = new Data[size];
}

/**
 * Class destructor
 */
Monitor::~Monitor() {
    delete[] this->data;
}

/**
 * Adds an element to the monitor (in the correct position based on sort order)
 */
void Monitor::add(Data data) {
    #pragma omp critical
    {
        while (this->count == this->size) {
            // spin-wait while the data array is full
        }

        int index = this->getIndex(data);

        this->shiftElements(index);

        this->data[index] = data;

        this->count++;
    }
}

/**
 * Removes and returns the last element from the data array
 */
Data* Monitor::pop() {
    Data* data;

    #pragma omp critical
    {
        while (this->count == 0 && this->willHaveMoreData) {
            // spin-wait while there is no data
        }

        if (!this->willHaveMoreData) {
            data = nullptr;
        }

        data = &this->data[count - 1];

        count--;
    }

    return data;
}

/**
 * Gets the correct position of an element based on it's sort order
 */
int Monitor::getIndex(Data data) {
    int index = 0;

    for (int i = 0; i < count; i++) {
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
    for (int i = count - 1; i > index; i--) {
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
