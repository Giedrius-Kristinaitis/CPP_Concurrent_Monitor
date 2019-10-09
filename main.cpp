#include <omp.h>
#include <monitor.h>
#include <data.h>
#include <iostream>
#include <string>
#include <fstream>
#include <json.hpp>
#include <vector>

using namespace std;
using namespace nlohmann;

/**
 * I REALLY SHOULD HAVE MADE THE FUNCTIONS LESS DEPENDANT ON THE VARIABLES DECLARED BELOW
 * BY ADDING FUNCTION PARAMETERS, BUT WHATEVER
 */
const char LETTERS[] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '/', '\0', ' ', 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'r', 'q', 's', 't', 'v', 'x', 'z', 'w'
};

const int DATA_FILE_COUNT = 3;

const string DATA_FILES[] = {
    "IFF-7-2_Giedrius_Kristinaitis_L1_dat_1.json",
    "IFF-7-2_Giedrius_Kristinaitis_L1_dat_2.json",
    "IFF-7-2_Giedrius_Kristinaitis_L1_dat_3.json"
};

const int DATA_ELEMENTS = 25;
int dataElementsProcessed;

Monitor* monitor;
Monitor* results;

/**
 * Reads the data from a file and populates the monitor
 */
void populateMonitor(string file);

/**
 * Prints results to the specified file
 */
void printResults(Monitor* results, string dataFile, string resultFile);

/**
 * Processes data
 */
void processData(Data* data);

/**
 * Processes a file
 */
void processFile(string file);

/**
 * An action that is executed by a worker thread
 */
void executeThreadAction();

/**
 * Filters a data element
 */
bool filterData(Data* data);

/**
 * ENTRY POINT OF THE PROGRAM
 */
int main()
{
    try {
        remove("IFF-7-2_Giedrius-Kristinaitis_L1_rez.txt");
    } catch (exception ex) {}

    for (int i = 0; i < DATA_FILE_COUNT; i++) {
        processFile(DATA_FILES[i]);
    }

    return 0;
}

/**
 * Processes a file
 */
void processFile(string file) {
    monitor = new Monitor(25);
    results = new Monitor(25);

    dataElementsProcessed = 0;

    #pragma omp parallel num_threads(5)
    {
        if (omp_get_thread_num() == 0) {
            // main thread
            populateMonitor(file);
        } else {
            // worker thread
            executeThreadAction();
        }
    }

    printResults(results, file, "IFF-7-2_Giedrius-Kristinaitis_L1_rez.txt");

    delete monitor;
    delete results;
}

/**
 * Reads the data from a file and populates the monitor
 */
void populateMonitor(string file) {
    ifstream input;
    input.open(file, ifstream::in);

    json data = json::parse(input);

    for (auto& element: data["products"]) {
        Data data(element.value("title", ""), element.value("price", 0), element.value("quantity", 0));

        monitor->add(data);
    }

    input.close();

    monitor->setWillHaveMoreData(false);
}

/**
 * Prints results to the specified file
 */
void printResults(Monitor* results, string dataFile, string resultFile) {
    ofstream out(resultFile, ofstream::app);

    out << "----------------------------------------------------------" << endl;
    out << dataFile << " Results" << endl;
    out << "----------------------------------------------------------" << endl;
    out << "Title|Price|Quantity|Result" << endl;
    out << "----------------------------------------------------------" << endl;

    bool printed = false;

    for (int i = 0; i < results->getSize(); i++) {
        Data* result = results->get(i);

        if (!result->getTitle().empty()) {
            out << result->getTitle() << "|" << result->getPrice() << "|" << result->getQuantity() << "|" << result->getResult() << endl;
            printed = true;
        }
    }

    if (!printed) {
        out << "No results - no elements match the filter" << endl;
    }

    out.close();
}

/**
 * An action that is executed by a worker thread
 */
void executeThreadAction() {
    while (dataElementsProcessed != DATA_ELEMENTS) {
        Data* data = monitor->pop();

        if (data != nullptr) {
            processData(data);

            if (filterData(data)) {
                results->add(*data);
            }
        }
    }
}

/**
 * Processes data
 */
void processData(Data* data) {
    char result;
    const int endValue = data->getPrice() * data->getQuantity() * data->getQuantity();

    for (int i = 0; i < endValue; i++) {
        result = data->getTitle().at(i % (data->getTitle().length()));
    }

    data->setResult(result);

    dataElementsProcessed++;
}

/**
 * Filters a data element
 */
bool filterData(Data* data) {
    for (char letter: LETTERS) {
        if (letter == data->getResult()) {
            return true;
        }
    }

    return false;
}
