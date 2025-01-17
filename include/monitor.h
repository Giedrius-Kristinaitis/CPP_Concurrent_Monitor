#ifndef MONITOR_H
#define MONITOR_H

#include "data.h"
#include <omp.h>

using namespace std;

class Monitor {

    private:
        Data* data;
        int size;
        int count;
        bool willHaveMoreData;
        omp_lock_t lock;

    public:
        /**
         * Class constructor
         */
        Monitor(int size);

        /**
         * Class destructor
         */
        ~Monitor();

        /**
         * Adds an element to the monitor (in the correct position based on sort order)
         */
        void add(Data data);

        /**
         * Removes and returns the last element from the data array
         */
        Data* pop();

        /**
         * Returns the element at the specified index
         */
        Data* get(int index);

        /**
         * Gets the number of elements in the monitor
         */
        int getSize();

        /**
         * Sets the will have more data flag
         */
        void setWillHaveMoreData(bool willHaveMoreData);

        /**
         * Clears the monitor
         */
        void clear();

    private:
        /**
         * Gets the correct position of an element based on it's sort order
         */
        int getIndex(Data data);

        /**
         * Shifts all elements to the right starting from the specified index
         */
        void shiftElements(int index);

        /**
         * Initializes the inner data array
         */
        void initializeData();

        /**
         * Destroys the inner data array
         */
        void destroyData();
};

#endif // MONITOR_H
