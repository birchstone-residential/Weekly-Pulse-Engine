#include "main.hpp"

int main(int argc, const char **argv)
{
    // Configure date used during session
    configureDate(argc, argv);

    // Configure routine type used during session
    configureRoutineType(argc, argv);

    // Setup input files
    initializeInputFiles();

    mergeDataGroupings();

    // If "-init" routine type is provided, end the program here
    if (sRoutineType == "-init")
    {
        std::cout << "~ ✅ Initialization routine successful" << std::endl;
        return 0;
    }

    checkDictionaryDefinitions();

    // Declare vector of properties
    PropertyList propList;

    // Initialize property names and populate vector
    initializePropertyNames(propList);

    // Initialize dictionary IDs
    initializeDictionaryIDs(propList);

    // Inject input data into PropertyList vector
    runInputRoutines(propList);

    // Create output report files
    runOutputRoutines(propList);

    return 0;
}