#include <omp.h>
#include <monitor.h>
#include <data.h>
#include <iostream>
#include <string>

using namespace std;

/**
 * I REALLY SHOULD HAVE MADE THE FUNCTIONS LESS DEPENDANT ON THE VARIABLES DECLARED BELOW
 * BY ADDING FUNCTION PARAMETERS, BUT WHATEVER
 */
const int DATA_FILE_COUNT = 3;

const string DATA_FILES[] = {
    "IFF-7-2_Giedrius-Kristinaitis_L1_dat_1.json",
    "IFF-7-2_Giedrius-Kristinaitis_L1_dat_2.json",
    "IFF-7-2_Giedrius-Kristinaitis_L1_dat_3.json"
};

const string RESULT_FILE = "IFF-7-2_Giedrius-Kristinaitis_L1_rez.txt";

const int DATA_ELEMENTS = 25;
int dataElementsProcessed;

Monitor monitor(10);
Monitor results(25);

/**
 * Reads the data from a file and populates the monitor
 */
void populateMonitor(string file);

/**
 * Prints results to the specified file
 */
void printResults(string file);

/**
 * Processes data
 */
void processData(Data data);

/**
 * ENTRY POINt OF THE PROGRAM
 */
int main()
{
    #pragma omp parallel num_threads(5)
    {
        if (omp_get_thread_num() == 0) {
            // main thread

        } else {
            // worker thread

        }
    }

    return 0;
}

/**
 * Reads the data from a file and populates the monitor
 */
void populateMonitor(Monitor monitor) {

}

/**
 * Prints results to the specified file
 */
void printResults(Monitor results, string file) {

}

/**
 * Processes data
 */
void processData(Data data) {

}
