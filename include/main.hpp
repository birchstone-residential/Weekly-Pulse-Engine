#ifndef __main__hpp__
#define __main__hpp__

#include "helper_functions.hpp"
#include "input_routines.hpp"
#include "output_routines.hpp"
#include "dictionaries.hpp"
#include <functional>
#include <regex>

#pragma region InitializeInputFiles

void checkDictionaryDefinitions() noexcept(false)
{
    int numPropertiesDefined = static_cast<unsigned>(PropertyNameDictionary::Count);
    int numPropertiesInNameMap = propertyNameMap.size();
    int numberPropertiesInEntrataNameMap = entrataNameMap.size();

    std::cout << "~ Number of properties defined in dictionary: \t\t (" << numPropertiesDefined - 1 << ")" << std::endl;
    std::cout << "~ Number of properties in propertyNameMap: \t\t (" << numPropertiesInNameMap - 1 << ")" << std::endl;
    std::cout << "~ Number of properties in entrataNameMap: \t\t (" << numberPropertiesInEntrataNameMap - 1 << ")" << std::endl;
    
    if (allValuesSame({numPropertiesDefined,numPropertiesInNameMap,numberPropertiesInEntrataNameMap}))
    {
        std::cout << "~ 🟢 All properties appear defined, but this is a soft check" << std::endl;
    }
    else
    {
        std::cout << "~ 🟡 Some properties are not fully defined in dictionaries" << std::endl;
    }
}

bool ifDateProvidedInCommandLineArguements(int argc, const char **argv)
{
    if ( argc > 1 )
    {
        std::string input = argv[1];

        // Define a regular expression for the YYYY.MM.DD format
        std::regex datePattern(R"(^\d{4}\.\d{2}\.\d{2}$)");

        // Check if the input matches the pattern
        return (std::regex_match(input, datePattern));
    }

    return false;
}

bool ifRoutineTypeProvidedInCommandLineArguements(int argc, const char **argv)
{
    if ( argc > 2 )
    {
        std::string input = argv[2];

        if (input == "-init" || input == "-run" )
        {
            return true;   
        }
        else
        {
            std::cout << "~ Invalid routine type provided: \t (" << input << ")" << std::endl;
            std::cout << "~ Valid options are: \t\t\t ('-init', '-run')" << std::endl;
        }
    }
    else
    {
        std::cout << "~ No routine type provided" << std::endl;
        std::cout << "~ Valid options are: \t\t\t ('-init', '-run')" << std::endl;
    }

    return false;
}

void configureDate(int argc, const char **argv) noexcept(false)
{
    if ( ifDateProvidedInCommandLineArguements(argc, argv) )
    {
        std::string customDate = argv[1];
        std::cout << "~ Custom date provided: \t (" << customDate << ")" << std::endl;

        sExportDate = customDate;
        replaceDotsWithSlashes(customDate);
        sExportDate_Forward_Slash_Format = customDate;
    }
    else
    {
        sExportDate = getFormattedDate(".");
        std::string date = sExportDate;
        replaceDotsWithSlashes(date);
        sExportDate_Forward_Slash_Format = date;
    }
}

void configureRoutineType(int argc, const char **argv) noexcept(false)
{
    if ( ifRoutineTypeProvidedInCommandLineArguements(argc, argv) )
    {
        std::string input = argv[2];
        std::cout << "~ Routine type provided: \t (" << input << ")" << std::endl;

        sRoutineType = input;
    }
    else
    {
        throw std::runtime_error("Invalid routine type provided");
    }
}

void inflateAttachmentsDir() noexcept(false) 
{
    std::string attachmentsDir = "attachments";
    std::string destDir = "data/" + sExportDate + "/raw";

    // Find the ZIP file in the attachments directory
    std::string zipFilePath = findZipFile(attachmentsDir);
    if (zipFilePath.empty()) {
        throw std::runtime_error("No ZIP file found in the attachments directory.");
    }

    // Unzip the file
    if (unzipFile(zipFilePath, destDir)) {
        std::cout << "Unzipped successfully!" << std::endl;
    } else {
        throw std::runtime_error("Failed to unzip the file.");
    }
}

bool copyCsvFiles(const std::string& sourceDir, const std::string& destDir) 
{
    // Ensure the source directory exists
    if (!fs::exists(sourceDir) || !fs::is_directory(sourceDir)) {
        std::cerr << "Source directory does not exist or is not a directory: " << sourceDir << std::endl;
        return false;
    }

    // Create the destination directory if it doesn't exist
    if (!fs::exists(destDir)) {
        fs::create_directories(destDir);
    }

    // Iterate through the source directory
    for (const auto& entry : fs::directory_iterator(sourceDir)) {
        if (entry.is_regular_file() && entry.path().extension() == ".csv") {
            try {
                // Construct the destination file path
                fs::path destFilePath = fs::path(destDir) / entry.path().filename();
                std::string filename = entry.path().filename();
                std::string newFilePath = "";
                
                if ( filename.find("Gross Potential Rent") != SIZE_MAX  &&  filename.find("20th") == SIZE_MAX ) { // Group 1
                    newFilePath = destDir + "/" + "Gross Potential Rent.csv";
                }
                else if ( filename.find("Gross Potential Rent") != SIZE_MAX  &&  filename.find("20th") != SIZE_MAX ) { // Group 2
                    newFilePath = destDir + "/" + "Gross Potential Rent (20th).csv";
                }
                else if ( filename.find("Receipt By Charge Code RENT only - Receipts") != SIZE_MAX  &&  filename.find("20th") == SIZE_MAX ) { // Group 1
                    newFilePath = destDir + "/" + "Receipt By Charge Code - Receipts.csv";
                }
                else if ( filename.find("Receipt By Charge Code") != SIZE_MAX  &&  filename.find("20th - Receipts") != SIZE_MAX ) { // Group 2
                    newFilePath = destDir + "/" + "Receipt By Charge Code - Receipts (20th).csv";
                }
                else if ( filename.find("Resident Aged Receivables - Detail") != SIZE_MAX  &&  filename.find("20th") == SIZE_MAX ) { // Group 1
                    newFilePath = destDir + "/" + "Resident Aged Receivables - Detail.csv";
                }
                else if ( filename.find("ResidentAgedReceivables") != SIZE_MAX  &&  filename.find("20th") != SIZE_MAX  &&  filename.find("Detail") != SIZE_MAX ) { // Group 2
                    newFilePath = destDir + "/" + "Resident Aged Receivables - Detail (20th).csv";
                }
                else if ( filename.find("Resident Aged Receivables - Summary") != SIZE_MAX  &&  filename.find("20th") == SIZE_MAX ) { // Group 1
                    newFilePath = destDir + "/" + "Resident Aged Receivables - Summary.csv";
                }
                else if ( filename.find("ResidentAgedReceivables") != SIZE_MAX  &&  filename.find("20th") != SIZE_MAX  &&  filename.find("Summary") != SIZE_MAX) { // Group 2
                    newFilePath = destDir + "/" + "Resident Aged Receivables - Summary (20th).csv";
                }
                else if ( filename.find("Weekly Report_Availability") != SIZE_MAX ) {
                    newFilePath = destDir + "/" + "Availability.csv";
                }
                else if ( filename.find("Resident Retention") != SIZE_MAX ) {
                    newFilePath = destDir + "/" + "Resident Retention.csv";
                }
                else if ( filename.find("Move Out Reasons") != SIZE_MAX ) {
                    newFilePath = destDir + "/" + "Move Out Reasons.csv";
                }
                else if ( filename.find("Weekly Report_Box Score - Availability") != SIZE_MAX ) {
                    newFilePath = destDir + "/" + "Box Score - Availability.csv";
                }
                else if ( filename.find("Box Score - Lead Conversions") != SIZE_MAX ) {
                    newFilePath = destDir + "/" + "Box Score - Lead Conversions.csv";
                }
                else if ( filename.find("Weekly Report_Box Score - Make Ready Status") != SIZE_MAX ) {
                    newFilePath = destDir + "/" + "Box Score - Make Ready Status.csv";
                }
                else if ( filename.find("Box Score - Property Pulse") != SIZE_MAX ) {
                    newFilePath = destDir + "/" + "Box Score - Property Pulse.csv";
                }
                else if ( filename.find("Work Order Performance") != SIZE_MAX ) {
                    newFilePath = destDir + "/" + "Work Order Performance.csv";
                }
                else if ( filename.find("Income Statement as Cash") != SIZE_MAX  &&  filename.find("20th") == SIZE_MAX ) { // Group 1
                    newFilePath = destDir + "/" + "Income Statement as Cash.csv";
                }
                else if ( filename.find("Income Statement as Cash") != SIZE_MAX  &&  filename.find("20th") != SIZE_MAX ) { // Group 2
                    newFilePath = destDir + "/" + "Income Statement as Cash (20th).csv";
                }
                else if ( filename.find("Daily and Weekly Operations") != SIZE_MAX ) {
                    newFilePath = destDir + "/" + "Daily and Weekly Operations.csv";
                }
                else if ( filename.find("Birchstone Dashboard") != SIZE_MAX ) {
                    newFilePath = destDir + "/" + "Birchstone Dashboard.csv";
                }
                else if ( filename.find("Job Cost Details") != SIZE_MAX ) {
                    newFilePath = destDir + "/" + "Job Cost Details.csv";
                }
                else if ( filename.find("Lease Trade-out") != SIZE_MAX ) {
                    newFilePath = destDir + "/" + "Lease Trade-out.csv";
                }
                else if ( filename.find("Rolling Renovation") != SIZE_MAX ) {
                    newFilePath = destDir + "/" + "Rolling Renovation.csv";
                }

                if ( newFilePath.size() ) {
                    // Copy the file to the destination directory
                    fs::copy_file(entry.path(), newFilePath, fs::copy_options::overwrite_existing);
                    std::cout << "Copied " << entry.path() << " to " << newFilePath << std::endl;
                }
                
            } catch (const fs::filesystem_error& e) {
                std::cerr << "Error copying file " << entry.path() << ": " << e.what() << std::endl;
            }
        }
    }

    return true;
}

void cleanFiles() 
{
    std::string srcDir = "data/" + sExportDate + "/raw";
    std::string destDir = "data/" + sExportDate + "/clean";

    copyCsvFiles(srcDir, destDir);
}

void initializeInputFiles() 
{
    std::string path = "data/" + sExportDate + "/clean";
    std::cout << "~ Generating for:\t\t (" << sExportDate << ")" << std::endl;

    if ( fs::exists(path) ) {
        std::cout << "~ Bypassing inflation and clean: (Files exist)" << std::endl;
        return;
    }

    try {
        inflateAttachmentsDir();
        cleanFiles();
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void mergeDataGroupings()
{
    std::string dateStr = sExportDate;
    std::cout << "~ Merging data groupings for date: (" << dateStr << ")" << std::endl;

    // Define the pairs of files to merge
    std::vector<std::tuple<std::string, std::string, std::string>> fileTuples = {
        {"Gross Potential Rent.csv", "Gross Potential Rent (20th).csv", "Gross Potential Rent (Merged).csv"},
        {"Receipt By Charge Code - Receipts.csv", "Receipt By Charge Code - Receipts (20th).csv", "Receipt By Charge Code - Receipts (Merged).csv"},
        {"Resident Aged Receivables - Detail.csv", "Resident Aged Receivables - Detail (20th).csv", "Resident Aged Receivables - Detail (Merged).csv"},
        {"Resident Aged Receivables - Summary.csv", "Resident Aged Receivables - Summary (20th).csv", "Resident Aged Receivables - Summary (Merged).csv"},
        {"Income Statement as Cash.csv", "Income Statement as Cash (20th).csv", "Income Statement as Cash (Merged).csv"}
    };

    for (const auto& tuple : fileTuples) {
        merge_csv_files(dateStr, std::get<0>(tuple), std::get<1>(tuple), std::get<2>(tuple));
    }
}

#pragma endregion // InitializeInputFiles

#pragma region InitializePropertyList

void initializePropertyNames(PropertyList& propList) noexcept(false) 
{
    std::cout << "~ Initializing Property Names:   (" << static_cast<unsigned>(PropertyNameDictionary::Count) - 1 << ") properties defined" << std::endl;
    for (int i = 1; i < static_cast<unsigned>(PropertyNameDictionary::Count); ++i) 
    {
        Property property;
        property.__name_ = propertyNameMap[static_cast<PropertyNameDictionary>(i)];
        property.__entrata_name_ = entrataNameMap[static_cast<PropertyNameDictionary>(i)];
        propList().push_back(property);
    }

    std::cout << "~ Initialization Complete:\t (" << propList().size() << ") properties created" << std::endl;
}

void initializeDictionaryIDs(PropertyList& propList) noexcept(false)
{
    std::cout << "~ Initializing Dictionary IDs" << std::endl;
    for (auto &prop: propList()) 
    {
        for (int i = 0; i < static_cast<unsigned>(PropertyNameDictionary::Count); i++)
        {
            if (prop.__name_ == propertyNameMap[static_cast<PropertyNameDictionary>(i)])
            {
                prop.__id_ = i;
                //std::cout << "~ Assigned ID: (" << prop.__id_ << ") to " << prop.__name_ << std::endl;
            }
        }
    }
}

#pragma endregion // InitializePropertyList

#pragma region RunInputRoutines

void runInputRoutines(PropertyList& propList) noexcept(false)
{
    injectBirchstoneDashboard(propList);
    injectAvailability(propList);
    injectBoxScore_Availability(propList);
    injectBoxScore_LeadConversions(propList);
    injectBoxScore_MakeReadyStatus(propList);
    injectBoxScore_PropertyPulse(propList);
    injectDailyAndWeeklyOperations(propList);
    injectGrossPotentialRent(propList);
    injectIncomeStatementAsCash(propList);
    //injectJobCostDetails(propList);
    //injectLeaseTradeOut(propList);
    injectMoveOutReasons(propList);
    injectReceiptByChargeCode_Receipts(propList);
    injectResidentAgedReceivables_Detail(propList);
    injectResidentAgedReceivables_Summary(propList);
    injectResidentRetention(propList);
    //injectRollingRenovation(propList);
    injectWorkOrderPerformance(propList);

    // Print summary of files generated
    std::cout << formatWithCommas(sNumRowsProcessed) << " rows processed" << std::endl;
}

#pragma endregion // RunInputRoutines

#pragma region RunOutputRoutines

void runOutputRoutines(PropertyList& propList) noexcept(false)
{
    // Create output directory
    createOutputDirectory();

    // Write output files
    writeAvailabilityReport(propList);
    writeOverviewReport(propList);
    writeResidentRetentionReport(propList);
    writeIncomeReport(propList);
    writeOperationsReport(propList);
    writeFacilitiesMaintenanceReport(propList);
    //writeJobCostingReport(propList);

    // Print summary of files generated
    std::cout << sNumFilesGenerated << " files generated" << std::endl;
}

#pragma endregion // RunOutputRoutines

#endif // __main__hpp__