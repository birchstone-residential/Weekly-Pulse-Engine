#ifndef __input_routines__hpp__
#define __input_routines__hpp__

#include "PropertyList.hpp"
#include "helper_functions.hpp"
#include "rapidcsv.h"
#include "dictionaries.hpp"

// Read "Birchstone Dashboard.csv" and inject into PropertyList
void injectBirchstoneDashboard(PropertyList& propList) noexcept(false)
{
    PRINT_FUNCTION_START();

    static const std::string FILENAME = "data/" + sExportDate + "/clean/Birchstone Dashboard.csv";

    // Load the CSV file into a rapidcsv::Document
    rapidcsv::Document doc(FILENAME);

    std::vector<std::string> headers = doc.GetColumnNames();
    //for (const auto& header : headers)
    //    std::cout << "Header: " << header << std::endl;

    // Get the number of cols
    int numCols = doc.GetColumnCount();
    // Get the number of rows
    int numRows = doc.GetRowCount();

    int numProperties = propList().size();
    int numPropertyCols = numCols - 2;

    std::cout << "~\t (" << numProperties << ") properties defined" << std::endl;
    std::cout << "~\t (" << numPropertyCols << ") property columns in 'Birchstone Dashboard.csv'" << std::endl;
    if (numProperties == numPropertyCols)
    {
        std::cout << "~\t 🟢 All properties defined should populate" << std::endl;
    }
    else
    {
        std::cout << "~\t 🟡 Some properties may not be defined in the dictionary" << std::endl;
    }

    // Create a vector of Availability structs to store the results
    std::vector<BirchstoneDashboard> vect;

   for (int i = 1; i < static_cast<unsigned>(PropertyNameDictionary::Count); i++)
   {
        bool columnExists = 
            (std::find(headers.begin(), headers.end(), entrataNameMap[static_cast<PropertyNameDictionary>(i)]) != headers.end());

        //if (columnExists)
        //    std::cout << "Found column: " << entrataNameMap[static_cast<PropertyNameDictionary>(i)] << std::endl;
        if (!columnExists)
            std::cout << "~\t 🟡 Column not found: " << entrataNameMap[static_cast<PropertyNameDictionary>(i)] << std::endl;

        if (columnExists)
        {
            BirchstoneDashboard data;

            data.__property_ = entrataNameMap[static_cast<PropertyNameDictionary>(i)];

            for (int j = 0; j < numRows; j++)
            {
                std::string datum = doc.GetCell<std::string>(entrataNameMap[static_cast<PropertyNameDictionary>(i)], j);
                switch (j)
                {
                    case 0:   data.__occupied_percent_ = parseFloatWithCommaAndParentheses(datum);
                        break;
                    case 1:   data.__14_day_trend_ = parseFloatWithCommaAndParentheses(datum);
                        break;
                    case 2:   data.__28_day_trend_ = parseFloatWithCommaAndParentheses(datum);
                        break;
                    case 3:   data.__56_day_trend_ = parseFloatWithCommaAndParentheses(datum);
                        break;
                    case 4:   data.__14_day_trend_with_applications_ = parseFloatWithCommaAndParentheses(datum);
                        break;
                    case 5:   data.__28_day_trend_with_applications_ = parseFloatWithCommaAndParentheses(datum);
                        break;
                    case 6:   data.__56_day_trend_with_applications_ = parseFloatWithCommaAndParentheses(datum);
                        break;
                    case 7:  // Skip this row
                        break;
                    case 8:   data.__30_day_traffic_count_ = parseFloatWithCommaAndParentheses(datum);
                        break;
                    case 9:   data.__30_day_closing_ratio_ = parseFloatWithCommaAndParentheses(datum);
                        break;
                    case 10:  data.__occupied_rent_per_sf_ = parseFloatWithCommaAndParentheses(datum);
                        break;
                    case 11:  data.__previous_30_day_net_move_ins_ = parseFloatWithCommaAndParentheses(datum);
                        break;
                    case 12:  data.__total_pending_move_ins_ = parseFloatWithCommaAndParentheses(datum);
                        break;
                    case 13:  // Skip this row
                        break;
                    case 14:  data.__open_work_orders_ = parseFloatWithCommaAndParentheses(datum);
                        break;
                    case 15:  data.__percent_work_orders_completed_on_time_ = parseFloatWithCommaAndParentheses(datum);
                        break;
                    case 16:  // Skip this row
                        break;
                    case 17:  data.__total_billed_ = parseFloatWithCommaAndParentheses(datum);
                        break;
                    case 18:  data.__current_month_collections_total_ = parseFloatWithCommaAndParentheses(datum);
                        break;
                    case 19:  data.__percent_collected_rent_type_ = parseFloatWithCommaAndParentheses(datum);
                        break;
                    case 20:  data.__delinquency_1_ = parseFloatWithCommaAndParentheses(datum);
                        break;
                    case 21:  data.__delinquency_2_ = parseFloatWithCommaAndParentheses(datum);
                        break;
                    case 22:  data.__delinquency_3_ = parseFloatWithCommaAndParentheses(datum);
                        break;
                    case 23:  data.__evictions_current_ = std::stoi(datum);
                        break;
                    case 24:  data.__evictions_total_ = std::stoi(datum);
                        break;
                    case 25:  // Skip this row
                        break;
                    case 26:  data.__notice_unrented_ = std::stoi(datum);
                        break;
                    case 27:  data.__vacant_unrented_not_ready_ = std::stoi(datum);
                        break;
                    case 28:  data.__vacant_unrented_ready_ = std::stoi(datum);
                        break;
                    case 29:  // Skip this row
                        break;
                    case 30:  data.__ap_total_outstanding_ = parseFloatWithCommaAndParentheses(datum);
                        break;
                    case 31:  data.__notice_rented_ = std::stoi(datum);
                        break;
                    case 32:  data.__vacant_rented_ready_ = std::stoi(datum);
                        break;
                    case 33:  // Skip this row
                        break;
                    case 34:  data.__current_month_renewal_percent_ = parseFloatWithCommaAndParentheses(datum);
                        break;
                    case 35:  data.__prior_month_renewal_percent_ = parseFloatWithCommaAndParentheses(datum);
                        break;
                    case 36:  data.__expirations_next_month_ = std::stoi(datum);
                        break;
                    case 37:  data.__renewals_next_month_ = std::stoi(datum);
                        break;
                    case 38:  data.__expirations_month_after_next_ = std::stoi(datum);
                        break;
                    case 39:  data.__renewals_month_after_next_ = std::stoi(datum);
                        break;
                    case 40:  data.__current_notice_to_vacate_ = std::stoi(datum);
                        break;
                    case 41:  // Skip this row
                        break;
                    case 42:  data.__total_p_ = std::stoi(datum);
                        break;
                    case 43:  data.__total_u_ = std::stoi(datum);
                        break;
                    case 44:  data.__total_r_ = std::stoi(datum);
                        break;
                    case 45:  data.__excluded_units_ = std::stoi(datum);
                        break;
                    
                    default:
                        break;
                }
            }

            vect.push_back(data);
        }
        else 
            continue;
   }

    // Inject the vector into the PropertyList by matching the property name 
    for (auto &item: vect)
        for (auto &prop: propList())
            if (item.__property_ == prop.__entrata_name_)
                prop.__birchstone_dashboard_ = item;

    // Print the number of "items" (rows of data) processed
    PRINT_NUM_ITEMS_PROCESSED(vect.size());

    sNumRowsProcessed += vect.size();

    PRINT_FUNCTION_STOP();

}

// Read "Availability.csv" and inject into PropertyList
void injectAvailability(PropertyList& propList) noexcept(false)
{
    PRINT_FUNCTION_START();

    static const std::string FILENAME = "data/" + sExportDate + "/clean/Availability_clean.csv";

    // Load the CSV file into a rapidcsv::Document
    rapidcsv::Document doc(FILENAME);

    // Get the number of rows (excluding the header)
    int numRows = doc.GetRowCount();

    // Create a vector of Availability structs to store the results
    std::vector<Availability> vect;

    // Loop through each row and extract the data
    for (int i = 0; i < numRows; i++)
    {
        Availability data;
        data.__property_                 = doc.GetCell<std::string>("Property", i);
        data.__bldg_unit_                = doc.GetCell<std::string>("Bldg-Unit", i);
        data.__floor_plan_               = doc.GetCell<std::string>("Floor Plan", i);
        data.__unit_type_                = doc.GetCell<std::string>("Unit Type", i);
        data.__unit_status_              = doc.GetCell<std::string>("Unit Status", i);
        data.__exclusion_name_           = doc.GetCell<std::string>("Exclusion Name", i);
        data.__days_vacant_              = doc.GetCell<int>("Days Vacant", i);

        if (doc.GetCell<std::string>("Move-Out", i) != "")
            data.__move_out_ = stotm(doc.GetCell<std::string>("Move-Out", i), "%m/%d/%Y");
        else
            data.__move_out_str_ = "";

        data.__available_on_ = stotm(doc.GetCell<std::string>("Available On", i), "%m/%d/%Y");
        
        if (doc.GetCell<std::string>("Scheduled Move-In", i) != "")
            data.__scheduled_move_in_ = stotm(doc.GetCell<std::string>("Scheduled Move-In", i), "%m/%d/%Y");
        else
            data.__scheduled_move_in_str_ = "";

        if (doc.GetCell<std::string>("Days Until Move In", i) != "")
            data.__days_until_move_in_ = doc.GetCell<int>("Days Until Move In", i);
        else
            data.__days_until_move_in_str_ = "";

        if (doc.GetCell<std::string>("Turn Time [MO-Avail]", i) != "")
            data.__turn_time_mo_avail_ = doc.GetCell<int>("Turn Time [MO-Avail]", i);
        else
            data.__turn_time_mo_avail_str_ = "";
        
        data.__available_date_exclusion_ = doc.GetCell<int>("Available Date Exclusion", i);
        data.__unit_notes_               = replaceDoubleQuotes(doc.GetCell<std::string>("Unit Notes", i));
        //data.__unit_activity_notes_      = replaceDoubleQuotes(doc.GetCell<std::string>("'Unit Activity Notes", i));
        //data.__hazard_note_              = replaceDoubleQuotes(doc.GetCell<std::string>("'Hazard Note", i));
        data.__market_rent_              = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Market Rent", i));
        data.__prior_lease_rent_         = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Prior Lease Rent", i));
        data.__budgeted_rent_            = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Budgeted Rent", i));

        if (doc.GetCell<std::string>("Future Lease Rent", i) != "")
            data.__future_lease_rent_ = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Future Lease Rent", i));
        else
            data.__future_lease_rent_str_ = "";

        if (doc.GetCell<std::string>("Application Approved", i) != "")
            data.__application_approved_ = stotm(doc.GetCell<std::string>("Application Approved", i), "%m/%d/%Y");
        else
            data.__application_approved_str_ = "";

        vect.push_back(data);           
    }

    // Inject the vector into the PropertyList by matching the property name 
    for (auto &item: vect)
        for (auto &prop: propList())
            if (item.__property_ == prop.__entrata_name_)
                prop.__availability_.push_back(item);

    // Print the number of "items" (rows of data) processed
    PRINT_NUM_ITEMS_PROCESSED(vect.size());

    sNumRowsProcessed += vect.size();

    PRINT_FUNCTION_STOP();
}

// Read "Box Score - Availability.csv" and inject into PropertyList
void injectBoxScore_Availability(PropertyList& propList) noexcept(false)
{
    PRINT_FUNCTION_START();

    static const std::string FILENAME = "data/" + sExportDate + "/clean/Box Score - Availability.csv";

    // Load the CSV file into a rapidcsv::Document
    rapidcsv::Document doc(FILENAME);

    // Get the number of rows (excluding the header)
    int numRows = doc.GetRowCount();

    // Create a vector of Availability structs to store the results
    std::vector<BoxScore_Availability> vect;

    // Loop through each row and extract the data
    for (int i = 0; i < numRows; i++)
    {
        BoxScore_Availability data;

        data.__property_                 = doc.GetCell<std::string>("Property", i);
        data.__avg_sqft_                 = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Avg. SQFT", i));
        data.__avg_market_rent_          = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Avg. Market Rent", i));
        data.__avg_budgeted_rent_        = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Avg. Budgeted Rent", i));
        data.__avg_scheduled_rent_       = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Avg. Scheduled Rent", i));
        data.__units_                    = doc.GetCell<int>("Units", i);
        data.__avg_scheduled_charges_    = doc.GetCell<float>("Avg. Scheduled Charges", i);
        data.__avg_scheduled_other_      = doc.GetCell<float>("Avg. Scheduled Other", i);
        data.__avg_effective_rent_       = doc.GetCell<float>("Avg. Effective Rent", i);
        data.__avg_net_effective_rent_   = doc.GetCell<float>("Avg. Net Effective Rent", i);
        data.__excluded_                 = doc.GetCell<int>("Excluded", i);
        data.__rentable_units_           = doc.GetCell<int>("Rentable Units", i);
        data.__occupied_                 = doc.GetCell<int>("Occupied", i);
        data.__vacant_                   = doc.GetCell<int>("Vacant", i);
        data.__available_                = doc.GetCell<int>("Available", i);
        data.__occupied_no_notice_       = doc.GetCell<int>("Occupied No Notice", i);
        data.__notice_rented_            = doc.GetCell<int>("Notice Rented", i);
        data.__notice_unrented_          = doc.GetCell<int>("Notice Unrented", i);
        data.__vacant_rented_            = doc.GetCell<int>("Vacant Rented", i);
        data.__vacant_unrented_          = doc.GetCell<int>("Vacant Unrented", i);
        data.__occupied_percent_         = doc.GetCell<float>("Occupied %", i);
        data.__trend_                    = doc.GetCell<float>("Trend", i);
        data.__exposure_                 = doc.GetCell<float>("Exposure", i);

        vect.push_back(data);
    }

    // Inject the vector into the PropertyList by matching the property name
    for (auto &item: vect)
        for (auto &prop: propList())
            if (item.__property_ == prop.__entrata_name_)
                prop.__box_score_availability_ = item;

    // Print the number of "items" (rows of data) processed
    PRINT_NUM_ITEMS_PROCESSED(vect.size());

    sNumRowsProcessed += vect.size();

    PRINT_FUNCTION_STOP();
}

// Read "Box Score - Lead Conversions.csv" and inject into PropertyList
void injectBoxScore_LeadConversions(PropertyList& propList) noexcept(false)
{
    PRINT_FUNCTION_START();

    static const std::string FILENAME = "data/" + sExportDate + "/clean/Box Score - Lead Conversions.csv";

    // Load the CSV file into a rapidcsv::Document
    rapidcsv::Document doc(FILENAME);

    // Get the number of rows (excluding the header)
    int numRows = doc.GetRowCount();

    // Create a vector of Availability structs to store the results
    std::vector<BoxScore_LeadConversions> vect;

    // Loop through each row and extract the data
    for (int i = 0; i < numRows; i++)
    {
        BoxScore_LeadConversions data;

        data.__property_                        = doc.GetCell<std::string>("Property", i);
        data.__application_partially_completed_ = doc.GetCell<int>("Application - Partially Completed", i);
        data.__application_completed_           = doc.GetCell<int>("Application - Completed", i);
        data.__application_completed_cancelled_ = doc.GetCell<int>("Application - Completed (Cancelled)", i);
        data.__application_denied_              = doc.GetCell<int>("Application - Denied", i);
        data.__application_approved_            = doc.GetCell<int>("Application - Approved", i);
        data.__application_approved_cancelled_  = doc.GetCell<int>("Application - Approved (Cancelled)", i);
        data.__lease_completed_                 = doc.GetCell<int>("Lease - Completed", i);
        data.__lease_completed_cancelled_       = doc.GetCell<int>("Lease - Completed (Cancelled)", i);
        data.__lease_approved_                  = doc.GetCell<int>("Lease - Approved", i);

        vect.push_back(data);
    }

    // Inject the vector into the PropertyList by matching the property name
    for (auto &item: vect)
        for (auto &prop: propList())
            if (item.__property_ == prop.__entrata_name_)
                prop.__box_score_lead_conversions_ = item;

    // Print the number of "items" (rows of data) processed
    PRINT_NUM_ITEMS_PROCESSED(vect.size());

    sNumRowsProcessed += vect.size();

    PRINT_FUNCTION_STOP();
}

// Read "Box Score - Make Ready Status.csv" and inject into PropertyList
void injectBoxScore_MakeReadyStatus(PropertyList& propList) noexcept(false)
{
    PRINT_FUNCTION_START();

    static const std::string FILENAME = "data/" + sExportDate + "/clean/Box Score - Make Ready Status.csv";

    // Load the CSV file into a rapidcsv::Document
    rapidcsv::Document doc(FILENAME);

    // Get the number of rows (excluding the header)
    int numRows = doc.GetRowCount();

    // Create a vector of Availability structs to store the results
    std::vector<BoxScore_MakeReadyStatus> vect;

    // Loop through each row and extract the data
    for (int i = 0; i < numRows; i++)
    {
        BoxScore_MakeReadyStatus data;

        data.__property_        = doc.GetCell<std::string>("Property", i);
        data.__status_          = doc.GetCell<std::string>("Status", i);
        data.__vacant_rented_   = doc.GetCell<int>("Vacant Rented", i);
        data.__vacant_unrented_ = doc.GetCell<int>("Vacant Unrented", i);
        data.__total_vacant_    = doc.GetCell<int>("Total Vacant", i);
        data.__percent_         = doc.GetCell<float>("%", i);

        vect.push_back(data);
    }

    // Inject the vector into the PropertyList by matching the property name
    for (auto &item: vect)
        for (auto &prop: propList())
            if (item.__property_ == prop.__entrata_name_)
                prop.__box_score_make_ready_status_.push_back(item);

    // Print the number of "items" (rows of data) processed
    PRINT_NUM_ITEMS_PROCESSED(vect.size());

    sNumRowsProcessed += vect.size();

    PRINT_FUNCTION_STOP();
}

// Read "Box Score - Property Pulse.csv" and inject into PropertyList
void injectBoxScore_PropertyPulse(PropertyList& propList) noexcept(false)
{
    PRINT_FUNCTION_START();

    static const std::string FILENAME = "data/" + sExportDate + "/clean/Box Score - Property Pulse.csv";

    // Load the CSV file into a rapidcsv::Document
    rapidcsv::Document doc(FILENAME);

    // Get the number of rows (excluding the header)
    int numRows = doc.GetRowCount();

    // Create a vector of Availability structs to store the results
    std::vector<BoxScore_PropertyPulse> vect;

    // Loop through each row and extract the data
    for (int i = 0; i < numRows; i++)
    {
        BoxScore_PropertyPulse data;

        data.__property_                 = doc.GetCell<std::string>("Property", i);
        data.__units_                    = doc.GetCell<int>("Units", i);
        data.__move_ins_                 = doc.GetCell<int>("Move-Ins", i);
        data.__mtm_                      = doc.GetCell<int>("MTM", i);
        data.__mtm_conversions_          = doc.GetCell<int>("MTM Conversions", i);
        data.__renewal_offers_completed_ = doc.GetCell<int>("Renewal Offers Completed", i);
        data.__transfers_                = doc.GetCell<int>("Transfers", i);
        data.__notices_                  = doc.GetCell<int>("Notices", i);
        data.__move_outs_                = doc.GetCell<int>("Move-Outs", i);
        data.__renewal_transfers_        = doc.GetCell<int>("Renewal Transfers", i);
        data.__skips_                    = doc.GetCell<int>("Skips", i);
        data.__evictions_                = doc.GetCell<int>("Evictions", i);
        data.__leased_                   = doc.GetCell<int>("Leased", i);

        vect.push_back(data);
    }

    // Inject the vector into the PropertyList by matching the property name
    for (auto &item: vect)
        for (auto &prop: propList())
            if (item.__property_ == prop.__entrata_name_)
                prop.__box_score_property_pulse_ = item;

    // Print the number of "items" (rows of data) processed
    PRINT_NUM_ITEMS_PROCESSED(vect.size());

    sNumRowsProcessed += vect.size();

    PRINT_FUNCTION_STOP();
}

// Read "Daily and Weekly Operations.csv" and inject into PropertyList
void injectDailyAndWeeklyOperations(PropertyList& propList) noexcept(false)
{
    PRINT_FUNCTION_START();

    static const std::string FILENAME = "data/" + sExportDate + "/clean/Daily and Weekly Operations.csv";

    // Load the CSV file into a rapidcsv::Document
    rapidcsv::Document doc(FILENAME);

    // Get the number of rows (excluding the header)
    int numRows = doc.GetRowCount();

    // Create a vector of Availability structs to store the results
    std::vector<DailyAndWeeklyOperations> vect;

    // Loop through each row and extract the data
    for (int i = 0; i < numRows; i++)
    {
        DailyAndWeeklyOperations data;

        data.__property_                         = doc.GetCell<std::string>("Property", i);
        data.__lead_source_                      = doc.GetCell<std::string>("Lead Source", i);
        data.__new_leads_                        = doc.GetCell<int>("New Leads", i);
        data.__first_visit_tour_                 = doc.GetCell<int>("First Visit/Tour", i);
        data.__applications_partial_             = doc.GetCell<int>("Applications Partially Completed", i);
        data.__applications_completed_           = doc.GetCell<int>("Applications Completed", i);
        data.__applications_completed_cancelled_ = doc.GetCell<int>("Applications Completed (Cancelled)", i);
        data.__applications_denied_              = doc.GetCell<int>("Applications Denied", i);
        data.__applications_approved_            = doc.GetCell<int>("Applications Approved", i);
        data.__applications_approved_cancelled_  = doc.GetCell<int>("Applications Approved (Cancelled)", i);
        data.__leases_completed_                 = doc.GetCell<int>("Leases Completed", i);
        data.__leases_completed_cancelled_       = doc.GetCell<int>("Leases Completed (Cancelled)", i);
        data.__leases_approved_                  = doc.GetCell<int>("Leases Approved", i);

        vect.push_back(data);
    }

    // Inject the vector into the PropertyList by matching the property name
    for (auto &item: vect)
        for (auto &prop: propList())
            if (item.__property_ == prop.__entrata_name_)
                prop.__daily_and_weekly_operations_.push_back(item);

    // Print the number of "items" (rows of data) processed
    PRINT_NUM_ITEMS_PROCESSED(vect.size());

    sNumRowsProcessed += vect.size();

    PRINT_FUNCTION_STOP();
}

// Read "Gross Potential Rent.csv" and inject into PropertyList
void injectGrossPotentialRent(PropertyList& propList) noexcept(false)
{
    PRINT_FUNCTION_START();

    static const std::string FILENAME = "data/" + sExportDate + "/clean/Gross Potential Rent (Merged).csv";

    // Load the CSV file into a rapidcsv::Document
    rapidcsv::Document doc(FILENAME);

    // Get the number of rows (excluding the header)
    int numRows = doc.GetRowCount();

    // Create a vector of Availability structs to store the results
    std::vector<GrossPotentialRent> vect;

    // Loop through each row and extract the data
    for (int i = 0; i < numRows; i++)
    {
        GrossPotentialRent data;

        data.__property_             = doc.GetCell<std::string>("Property", i);
        
        if ( doc.GetCell<std::string>("Unit Space Count", i) != "" )
            data.__unit_space_count_ = doc.GetCell<int>("Unit Space Count", i);
        else
            data.__unit_space_count_str_ = "";

        data.__gpr_market_rent_      = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("GPR - Market Rent", i));
        data.__total_potential_rent_ = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Total Potential Rent", i));
        data.__gain_loss_to_lease_   = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Gain/Loss to Lease", i));
        data.__days_vacant_          = doc.GetCell<int>("Days Vacant", i);
        data.__vacancy_              = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Vacancy", i));
        data.__vacancy_adjustments_  = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Vacancy Adjustments", i));
        data.__out_of_period_rent_   = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Out of Period Rent", i));
        data.__scheduled_rent_       = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Scheduled Rent", i));
        data.__rent_adjustments_     = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Rent Adjustments", i));
        data.__rent_write_offs_      = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Rent Write-Offs", i));
        data.__rental_income_        = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Rental Income", i));

        vect.push_back(data);
    }

    // Inject the vector into the PropertyList by matching the property name
    for (auto &item: vect)
        for (auto &prop: propList())
            if (item.__property_ == prop.__entrata_name_)
                prop.__gross_potential_rent_.push_back(item);

    // Print the number of "items" (rows of data) processed
    PRINT_NUM_ITEMS_PROCESSED(vect.size());

    sNumRowsProcessed += vect.size();

    PRINT_FUNCTION_STOP();
}

// Read "Income Statement as Cash.csv" and inject into PropertyList
void injectIncomeStatementAsCash(PropertyList& propList) noexcept(false)
{
    PRINT_FUNCTION_START();

    static const std::string FILENAME = "data/" + sExportDate + "/clean/Income Statement as Cash (Merged).csv";

    rapidcsv::Document doc(FILENAME);

    // Get the number of rows (excluding the header)
    int numRows = doc.GetRowCount();

    // Get the column names
    std::vector<std::string> headers = doc.GetColumnNames();

    // Create a vector of Availability structs to store the results
    std::vector<IncomeStatementAsCash> vect;

    // Loop through each row and extract the data only from the "Rent - Resident" Account Name
    for (int i = 0; i < numRows; i++)
    {
        IncomeStatementAsCash data;

        data.__account_name_ = doc.GetCell<std::string>("Account Name", i);
        
        if (data.__account_name_ == "Rent - Resident")
        {
            data.__property_   = doc.GetCell<std::string>("Property", i);
            data.__unit_count_ = doc.GetCell<int>("Unit Count", i);
            
            for (int j = 3; j < headers.size(); j++)
            {
                switch (j)
                {
                    case 3:   data.__balance_11_months_ago = std::make_pair(headers[j], parseFloatWithCommaAndParentheses(doc.GetCell<std::string>(j, i)));
                        break;
                    case 4:   data.__balance_10_months_ago = std::make_pair(headers[j], parseFloatWithCommaAndParentheses(doc.GetCell<std::string>(j, i)));
                        break;
                    case 5:   data.__balance_9_months_ago = std::make_pair(headers[j], parseFloatWithCommaAndParentheses(doc.GetCell<std::string>(j, i)));
                        break;
                    case 6:   data.__balance_8_months_ago = std::make_pair(headers[j], parseFloatWithCommaAndParentheses(doc.GetCell<std::string>(j, i)));
                        break;
                    case 7:   data.__balance_7_months_ago = std::make_pair(headers[j], parseFloatWithCommaAndParentheses(doc.GetCell<std::string>(j, i)));
                        break;
                    case 8:   data.__balance_6_months_ago = std::make_pair(headers[j], parseFloatWithCommaAndParentheses(doc.GetCell<std::string>(j, i)));
                        break;
                    case 9:   data.__balance_5_months_ago = std::make_pair(headers[j], parseFloatWithCommaAndParentheses(doc.GetCell<std::string>(j, i)));
                        break;
                    case 10:  data.__balance_4_months_ago = std::make_pair(headers[j], parseFloatWithCommaAndParentheses(doc.GetCell<std::string>(j, i)));
                        break;
                    case 11:  data.__balance_3_months_ago = std::make_pair(headers[j], parseFloatWithCommaAndParentheses(doc.GetCell<std::string>(j, i)));
                        break;
                    case 12:  data.__balance_2_months_ago = std::make_pair(headers[j], parseFloatWithCommaAndParentheses(doc.GetCell<std::string>(j, i)));
                        break;
                    case 13:  data.__balance_1_months_ago = std::make_pair(headers[j], parseFloatWithCommaAndParentheses(doc.GetCell<std::string>(j, i)));
                        break;
                    case 14:  data.__balance_0_months_ago = std::make_pair(headers[j], parseFloatWithCommaAndParentheses(doc.GetCell<std::string>(j, i)));
                        break;
                    default:
                        break;
                }
            }

            data.__total = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Total", i));

            vect.push_back(data);
        }
    }

    // Inject the vector into the PropertyList by matching the property name
    for (auto &item: vect)
        for (auto &prop: propList())
            if (item.__property_ == prop.__entrata_name_)
                prop.__income_statement_as_cash_ = (item);

    // Print the number of "items" (rows of data) processed
    PRINT_NUM_ITEMS_PROCESSED(numRows);

    sNumRowsProcessed += numRows;

    PRINT_FUNCTION_STOP();
    
}

// Read "Job Cost Details.csv" and inject into PropertyList
void injectJobCostDetails(PropertyList& propList) noexcept(false)
{
    PRINT_FUNCTION_START();

    static const std::string FILENAME = "data/" + sExportDate + "/clean/Job Cost Details.csv";

    // Load the CSV file into a rapidcsv::Document
    rapidcsv::Document doc(FILENAME);

    // Get the number of rows (excluding the header)
    int numRows = doc.GetRowCount();

    // Create a vector of Availability structs to store the results
    std::vector<JobCostDetails> vect;

    // Loop through each row and extract the data
    for (int i = 0; i < numRows; i++)
    {
        JobCostDetails data;

        data.__property_ = doc.GetCell<std::string>("Property", i);
        data.__bldg_unit_ = doc.GetCell<std::string>("BLDG-Unit", i);
        data.__gl_account_ = doc.GetCell<std::string>("GL Account", i);
        data.__gl_account_name_ = doc.GetCell<std::string>("GL Account Name", i);

        if (doc.GetCell<std::string>("Transaction Date", i) != "")
            data.__transaction_date_ = stotm(doc.GetCell<std::string>("Transaction Date", i), "%m/%d/%Y");
        else
            data.__transaction_date_str_ = "";

        if (doc.GetCell<std::string>("Post Date", i) != "")
            data.__post_date_ = stotm(doc.GetCell<std::string>("Post Date", i), "%m/%d/%Y");
        else
            data.__post_date_str_ = "";

        data.__post_month_ = doc.GetCell<std::string>("Post Month", i);
        data.__job_ = doc.GetCell<std::string>("Job", i);
        data.__phase_ = doc.GetCell<std::string>("Phase", i);
        data.__reference_ = doc.GetCell<std::string>("Reference", i);
        data.__transaction_type_ = doc.GetCell<std::string>("Transaction Type", i);
        data.__description_ = doc.GetCell<std::string>("Description", i);
        data.__cost_code_category_ = doc.GetCell<std::string>("Cost Code Category", i);
        data.__transaction_amount_ = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Transaction Amount", i));
        data.__total_ = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Total", i));
        data.__remaining_budget_ = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Remaining Budget", i));
        data.__percent_remaining_budget_ = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("% of Remaining Budget", i));

        vect.push_back(data);
    }

    // Inject the vector into the PropertyList by matching the property name
    for (auto &item: vect)
        for (auto &prop: propList())
            if (item.__property_ == prop.__entrata_name_)
                prop.__job_cost_details_.push_back(item);

    // Print the number of "items" (rows of data) processed
    PRINT_NUM_ITEMS_PROCESSED(vect.size());

    sNumRowsProcessed += vect.size();

    PRINT_FUNCTION_STOP();
}

// Read "Lease Trade-out.csv" and inject into PropertyList
void injectLeaseTradeOut(PropertyList& propList) noexcept(false)
{
    PRINT_FUNCTION_START();

    static const std::string FILENAME = "data/" + sExportDate + "/clean/Lease Trade-out.csv";

    // Load the CSV file into a rapidcsv::Document
    rapidcsv::Document doc(FILENAME);

    // Get the number of rows (excluding the header)
    int numRows = doc.GetRowCount();

    // Create a vector of Availability structs to store the results
    std::vector<LeaseTradeOut> vect;

    // Loop through each row and extract the data
    for (int i = 0; i < numRows; i++)
    {
        LeaseTradeOut data;

        data.__property_ = doc.GetCell<std::string>("Property", i);
        data.__bldg_unit_ = doc.GetCell<std::string>("Bldg-Unit", i);
        data.__unit_ = doc.GetCell<std::string>("Unit", i);
        data.__skip_mtm_ = doc.GetCell<std::string>("Skip MTM?", i);
        data.__unit_type_ = doc.GetCell<std::string>("Unit Type", i);
        data.__sqft_ = doc.GetCell<std::string>("SQFT", i);
        
        if (doc.GetCell<std::string>("Days Vacant", i) != "")
            data.__days_vacant_ = doc.GetCell<int>("Days Vacant", i);
        else
            data.__days_vacant_str_ = "";

        data.__prior_resident_ = doc.GetCell<std::string>("Prior Resident", i);
        
        if (doc.GetCell<std::string>("Move-In", i) != "")
            data.__move_in_ = stotm(doc.GetCell<std::string>("Move-In", i), "%m/%d/%Y");
        else
            data.__move_in_str_ = "";

        data.__current_resident_ = doc.GetCell<std::string>("Current Resident", i);
        data.__current_lease_type_ = doc.GetCell<std::string>("Current Lease Type", i);
        data.__prior_lease_start_ = stotm(doc.GetCell<std::string>("Prior Lease Start", i), "%m/%d/%Y");
        data.__prior_lease_end_ = stotm(doc.GetCell<std::string>("Prior Lease End", i), "%m/%d/%Y");
        data.__current_lease_start_ = stotm(doc.GetCell<std::string>("Current Lease Start", i), "%m/%d/%Y");
        data.__current_lease_end_ = stotm(doc.GetCell<std::string>("Current Lease End", i), "%m/%d/%Y");

        if (doc.GetCell<std::string>("Prior Base Rent", i) != "")
            data.__prior_base_rent_ = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Prior Base Rent", i));
        else
            data.__prior_base_rent_str_ = "";

        if (doc.GetCell<std::string>("Prior Amenity Rent", i) != "")
            data.__prior_amenity_rent_ = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Prior Amenity Rent", i));
        else
            data.__prior_amenity_rent_str_ = "";

        if (doc.GetCell<std::string>("Prior Lease Rent", i) != "")
            data.__prior_lease_rent_ = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Prior Lease Rent", i));
        else
            data.__prior_lease_rent_str_ = "";

        if (doc.GetCell<std::string>("Current Base Rent", i) != "")
            data.__current_base_rent_ = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Current Base Rent", i));
        else
            data.__current_base_rent_str_ = "";

        if (doc.GetCell<std::string>("Current Amenity Rent", i) != "")
            data.__current_amenity_rent_ = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Current Amenity Rent", i));
        else
            data.__current_amenity_rent_str_ = "";

        if (doc.GetCell<std::string>("Current Lease Rent", i) != "")
            data.__current_lease_rent_ = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Current Lease Rent", i));
        else
            data.__current_lease_rent_str_ = "";

        if (doc.GetCell<std::string>("Market Rent", i) != "")
            data.__market_rent_ = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Market Rent", i));
        else
            data.__market_rent_str_ = "";

        if (doc.GetCell<std::string>("Budgeted Rent", i) != "")
            data.__budgeted_rent_ = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Budgeted Rent", i));
        else
            data.__budgeted_rent_str_ = "";

        if (doc.GetCell<std::string>("Lease Rent Change ($)", i) != "")
            data.__lease_rent_change_ = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Lease Rent Change ($)", i));
        else
            data.__lease_rent_change_str_ = "";
        
        vect.push_back(data);
    }

    // Inject the vector into the PropertyList by matching the property name
    for (auto &item: vect)
        for (auto &prop: propList())
            if (item.__property_ == prop.__entrata_name_)
                prop.__lease_trade_out_.push_back(item);

    // Print the number of "items" (rows of data) processed
    PRINT_NUM_ITEMS_PROCESSED(vect.size());

    sNumRowsProcessed += vect.size();

    PRINT_FUNCTION_STOP();
}

// Read "Move Out Reasons.csv" and inject into PropertyList
void injectMoveOutReasons(PropertyList& propList) noexcept(false)
{
    PRINT_FUNCTION_START();

    static const std::string FILENAME = "data/" + sExportDate + "/clean/Move Out Reasons.csv";

    // Load the CSV file into a rapidcsv::Document
    rapidcsv::Document doc(FILENAME);

    // Get the number of rows (excluding the header)
    int numRows = doc.GetRowCount();

    // Create a vector of Availability structs to store the results
    std::vector<MoveOutReasons> vect;

    // Loop through each row and extract the data
    for (int i = 0; i < numRows; i++)
    {
        MoveOutReasons data;

        data.__property_          = doc.GetCell<std::string>("Property", i);
        data.__bldg_unit_         = doc.GetCell<std::string>("Bldg-Unit", i);
        data.__unit_type_         = doc.GetCell<std::string>("Unit Type", i);
        data.__resident_          = doc.GetCell<std::string>("Resident", i);
        data.__notice_given_      = stotm(doc.GetCell<std::string>("Notice Given", i), "%m/%d/%Y");
        data.__lease_end_date_    = stotm(doc.GetCell<std::string>("Lease End Date", i), "%m/%d/%Y");
        data.__move_out_date_     = stotm(doc.GetCell<std::string>("Move Out Date", i), "%m/%d/%Y");
        data.__reason_            = doc.GetCell<std::string>("Reason", i);
        data.__early_termination_ = doc.GetCell<std::string>("Early Termination", i);
        data.__market_rent_       = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Market Rent", i));
        data.__scheduled_rent_    = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Scheduled Rent", i));
        data.__deposit_held_      = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Deposit Held", i));
        data.__balance_           = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Balance", i));

        vect.push_back(data);
    }

    // Inject the vector into the PropertyList by matching the property name
    for (auto &item: vect)
        for (auto &prop: propList())
            if (item.__property_ == prop.__entrata_name_)
                prop.__move_out_reasons_.push_back(item);

    // Print the number of "items" (rows of data) processed
    PRINT_NUM_ITEMS_PROCESSED(vect.size());

    sNumRowsProcessed += vect.size();

    PRINT_FUNCTION_STOP();
}

// Read "Receipt By Charge Code - Receipts.csv" and inject into PropertyList
void injectReceiptByChargeCode_Receipts(PropertyList& propList) noexcept(false)
{
    PRINT_FUNCTION_START();

    static const std::string FILENAME = "data/" + sExportDate + "/clean/Receipt By Charge Code - Receipts (Merged).csv";

    // Load the CSV file into a rapidcsv::Document
    rapidcsv::Document doc(FILENAME);

    // Get the number of rows (excluding the header)
    int numRows = doc.GetRowCount();

    // Create a vector of Availability structs to store the results
    std::vector<ReceiptByChargeCode_Receipts> vect;

    // Loop through each row and extract the data
    for (int i = 0; i < numRows; i++)
    {
        ReceiptByChargeCode_Receipts data;

        data.__property_               = doc.GetCell<std::string>("Property", i);
        data.__charge_code_            = doc.GetCell<std::string>("Charge Code", i);
        data.__gl_account_             = doc.GetCell<std::string>("GL Account", i);
        data.__total_charges_          = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Total Charges", i));
        data.__total_cash_collections_ = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Total Cash Collections", i));
        data.__credits_concessions_    = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Credits / Concessions", i));
        data.__total_collections_      = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Total Collections", i));

        if (doc.GetCell<std::string>("% Collected", i) != "")
            data.__percent_collected_ = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("% Collected", i));
        else
            data.__percent_collected_str_ = "";

        vect.push_back(data);
    }

    // Inject the vector into the PropertyList by matching the property name
    for (auto &item: vect)
        for (auto &prop: propList())
            if (item.__property_ == prop.__entrata_name_)
                prop.__receipt_by_charge_code_receipts_.push_back(item);

    // Print the number of "items" (rows of data) processed
    PRINT_NUM_ITEMS_PROCESSED(vect.size());

    sNumRowsProcessed += vect.size();

    PRINT_FUNCTION_STOP();
}

// Read "Resident Aged Receivables - Detail.csv" and inject into PropertyList
void injectResidentAgedReceivables_Detail(PropertyList& propList) noexcept(false)
{
    PRINT_FUNCTION_START();

    static const std::string FILENAME = "data/" + sExportDate + "/clean/Resident Aged Receivables - Detail (Merged).csv";

    // Load the CSV file into a rapidcsv::Document
    rapidcsv::Document doc(FILENAME);

    // Get the number of rows (excluding the header)
    int numRows = doc.GetRowCount();

    // Create a vector of Availability structs to store the results
    std::vector<ResidentAgedReceivables_Detail> vect;

    // Loop through each row and extract the data
    for (int i = 0; i < numRows; i++)
    {
        ResidentAgedReceivables_Detail data;

        data.__property_              = doc.GetCell<std::string>("Property", i);
        data.__resident_              = doc.GetCell<std::string>("Resident", i);
        data.__bldg_unit_             = doc.GetCell<std::string>("Bldg-Unit", i);
        data.__resident_              = doc.GetCell<std::string>("Resident", i);
        data.__lease_status_          = doc.GetCell<std::string>("Lease Status", i);
        data.__eviction_start_date_   = stotm(doc.GetCell<std::string>("Eviction Start Date", i), "%m/%d/%Y");
        data.__delinquent_total_      = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Delinquent Total", i));
        data.__0_to_30_days_          = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("0-30 Days", i));
        data.__31_to_60_days_         = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("31-60 Days", i));
        data.__61_to_90_days_         = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("61-90 Days", i));
        data.__90_plus_days_          = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("90+ Days", i));
        data.__pre_payments_          = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Pre-Payments", i));
        data.__balance_               = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Balance", i));

        vect.push_back(data);
    }

    // Inject the vector into the PropertyList by matching the property name
    for (auto &item: vect)
        for (auto &prop: propList())
            if (item.__property_ == prop.__entrata_name_)
                prop.__resident_aged_receivables_detail_.push_back(item);

    // Print the number of "items" (rows of data) processed
    PRINT_NUM_ITEMS_PROCESSED(vect.size());

    sNumRowsProcessed += vect.size();

    PRINT_FUNCTION_STOP();
}

// Read "Resident Aged Receivables - Summary.csv" and inject into PropertyList
void injectResidentAgedReceivables_Summary(PropertyList& propList) noexcept(false)
{
    PRINT_FUNCTION_START();

    static const std::string FILENAME = "data/" + sExportDate + "/clean/Resident Aged Receivables - Summary (Merged).csv";

    // Load the CSV file into a rapidcsv::Document
    rapidcsv::Document doc(FILENAME);

    // Get the number of rows (excluding the header)
    int numRows = doc.GetRowCount();

    // Create a vector of Availability structs to store the results
    std::vector<ResidentAgedReceivables_Summary> vect;

    // Loop through each row and extract the data
    for (int i = 0; i < numRows; i++)
    {
        ResidentAgedReceivables_Summary data;

        data.__property_                    = doc.GetCell<std::string>("Property", i);
        data.__lease_status_                = doc.GetCell<std::string>("Lease Status", i);
        data.__unallocated_charges_credits_ = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Unallocated Charges / Credits", i));
        data.__0_to_30_days_                = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("0-30 Days", i));
        data.__31_to_60_days_               = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("31-60 Days", i));
        data.__61_to_90_days_               = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("61-90 Days", i));
        data.__90_plus_days_                = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("90+ Days", i));
        data.__pre_payments_                = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Pre-Payments", i));
        data.__balance_                     = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Balance", i));

        vect.push_back(data);
    }

    // Inject the vector into the PropertyList by matching the property name
    for (auto &item: vect)
        for (auto &prop: propList())
            if (item.__property_ == prop.__entrata_name_)
                prop.__resident_aged_receivables_summary_.push_back(item);

    // Print the number of "items" (rows of data) processed
    PRINT_NUM_ITEMS_PROCESSED(vect.size());

    sNumRowsProcessed += vect.size();

    PRINT_FUNCTION_STOP();
}

// Read "Resident Retention.csv" and inject into PropertyList
void injectResidentRetention(PropertyList& propList) noexcept(false)
{
    PRINT_FUNCTION_START();

    static const std::string FILENAME = "data/" + sExportDate + "/clean/Resident Retention.csv";

    // Load the CSV file into a rapidcsv::Document
    rapidcsv::Document doc(FILENAME);

    // Get the number of rows (excluding the header)
    int numRows = doc.GetRowCount();

    // Create a vector of Availability structs to store the results
    std::vector<ResidentRetention> vect;

    // Loop through each row and extract the data
    for (int i = 0; i < numRows; i++)
    {
        ResidentRetention data;

        data.__property_                  = doc.GetCell<std::string>("Property", i);
        data.__month_                     = doc.GetCell<std::string>("Month", i);
        data.__units_                     = doc.GetCell<int>("Units", i);
        data.__rentable_units_            = doc.GetCell<int>("Rentable Units", i);
        data.__expiring_leases_           = doc.GetCell<int>("Expiring Leases", i);
        data.__early_move_out_            = doc.GetCell<int>("Early Move-out", i);
        data.__early_move_out_percent_    = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Early Move-out %", i));
        data.__ntv_                       = doc.GetCell<int>("NTV", i);
        data.__ntv_percent_               = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("NTV %", i));
        data.__renewals_                  = doc.GetCell<int>("Renewals", i);
        data.__renewals_percent_          = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Renewals %", i));
        data.__renewal_transfers_         = doc.GetCell<int>("Renewal Transfers", i);
        data.__renewal_transfers_percent_ = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Renewal Transfers %", i));
        data.__transfers_                 = doc.GetCell<int>("Transfers", i);
        data.__transfers_percent_         = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Transfers %", i));
        data.__pending_                   = doc.GetCell<int>("Pending", i);
        data.__pending_percent_           = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Pending %", i));
        data.__mtm_                       = doc.GetCell<int>("MTM", i);
        data.__mtm_percent_               = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("MTM %", i));

        vect.push_back(data);
    }

    // Inject the vector into the PropertyList by matching the property name
    for (auto &item: vect)
        for (auto &prop: propList())
            if (item.__property_ == prop.__entrata_name_)
                prop.__resident_retention_.push_back(item);

    // Print the number of "items" (rows of data) processed
    PRINT_NUM_ITEMS_PROCESSED(vect.size());

    sNumRowsProcessed += vect.size();

    PRINT_FUNCTION_STOP();
}

// Read "Rolling Renovation.csv" and inject into PropertyList
void injectRollingRenovation(PropertyList& propList) noexcept(false)
{
    PRINT_FUNCTION_START();

    static const std::string FILENAME = "data/" + sExportDate + "/clean/Rolling Renovation.csv";

    // Load the CSV file into a rapidcsv::Document
    rapidcsv::Document doc(FILENAME);

    // Get the number of rows (excluding the header)
    int numRows = doc.GetRowCount();

    // Create a vector of Availability structs to store the results
    std::vector<RollingRenovation> vect;

    // Loop through each row and extract the data
    for (int i = 0; i < numRows; i++)
    {
        RollingRenovation data;

        data.__property_                   = doc.GetCell<std::string>("Property", i);
        data.__bldg_unit_                  = doc.GetCell<std::string>("Bldg-Unit", i);
        data.__unit_type_                  = doc.GetCell<std::string>("Unit Type", i);
        data.__sqft_                       = doc.GetCell<std::string>("SQFT", i);
        data.__unit_status_                = doc.GetCell<std::string>("Unit Status", i);
        data.__renovation_status_          = doc.GetCell<std::string>("Renovation Status", i);
        data.__phase_                      = doc.GetCell<std::string>("Phase", i);
        data.__move_out_date_              = stotm(doc.GetCell<std::string>("Move-Out Date", i), "%m/%d/%Y");

        if (doc.GetCell<std::string>("Renovation Start Date", i) != "")
            data.__renovation_start_date_ = stotm(doc.GetCell<std::string>("Renovation Start Date", i), "%m/%d/%Y");
        else
            data.__renovation_start_date_str_ = "";
        
        if (doc.GetCell<std::string>("Renovation Completion Date", i) != "")
            data.__renovation_completion_date_ = stotm(doc.GetCell<std::string>("Renovation Completion Date", i), "%m/%d/%Y");
        else
            data.__renovation_completion_date_str_ = "";

        if (doc.GetCell<std::string>("Actual Renovation Days", i) != "")
            data.__actual_renovation_days_ = doc.GetCell<int>("Actual Renovation Days", i);
        else
            data.__actual_renovation_days_str_ = "";

        if (doc.GetCell<std::string>("Move-In Date", i) != "")
            data.__move_in_date_ = stotm(doc.GetCell<std::string>("Move-In Date", i), "%m/%d/%Y");
        else
            data.__move_in_date_str_ = "";

        data.__actual_renovation_cost_     = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Actual Renovation Cost", i));
        data.__budgeted_renovation_cost_   = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Budgeted Renovation Cost", i));
        data.__actual_vs_budget_variance_  = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Actual vs Budget Variance", i));
        data.__prior_market_rent_          = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Prior Market Rent", i));
        data.__new_market_rent_            = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("New Market Rent", i));
        data.__monthly_unit_premium_       = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Monthly Unit Premium", i));
        data.__monthly_roi_                = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Monthly ROI", i));

        data.__prior_budgeted_rent_ = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Prior Budgeted Rent", i));
        data.__new_budgeted_rent_   = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("New Budgeted Rent", i));
        
        vect.push_back(data);
    }

    // Inject the vector into the PropertyList by matching the property name
    for (auto &item: vect)
        for (auto &prop: propList())
            if (item.__property_ == prop.__entrata_name_)
                prop.__rolling_renovation_.push_back(item);

    // Print the number of "items" (rows of data) processed
    PRINT_NUM_ITEMS_PROCESSED(vect.size());

    sNumRowsProcessed += vect.size();

    PRINT_FUNCTION_STOP();
}

// Read "Work Order Performance.csv" and inject into PropertyList
void injectWorkOrderPerformance(PropertyList& propList) noexcept(false)
{
    PRINT_FUNCTION_START();

    static const std::string FILENAME = "data/" + sExportDate + "/clean/Work Order Performance.csv";

    // Load the CSV file into a rapidcsv::Document
    rapidcsv::Document doc(FILENAME);

    // Get the number of rows (excluding the header)
    int numRows = doc.GetRowCount();

    // Create a vector of Availability structs to store the results
    std::vector<WorkOrderPerformance> vect;

    // Loop through each row and extract the data
    for (int i = 0; i < numRows; i++)
    {
        WorkOrderPerformance data;

        data.__property_                        = doc.GetCell<std::string>("Property", i);
        data.__priority_                        = doc.GetCell<std::string>("Priority", i);
        data.__response_previous_work_orders_   = doc.GetCell<int>("Response - Previous Work Orders", i);
        data.__response_new_work_orders_        = doc.GetCell<int>("Response - New Work Orders", i);
        data.__response_on_time_                = doc.GetCell<int>("Response - On Time", i);
        data.__response_percent_on_time_        = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Response - % On Time", i));
        data.__response_late_                   = doc.GetCell<int>("Response - Late", i);
        data.__response_total_                  = doc.GetCell<int>("Response - Total", i);
        data.__response_not_started_            = doc.GetCell<int>("Response - Not Started", i);
        data.__completion_previous_work_orders_ = doc.GetCell<int>("Completion - Previous Work Orders", i);
        data.__completion_new_work_orders_      = doc.GetCell<int>("Completion - New Work Orders", i);
        data.__completion_on_time_              = doc.GetCell<int>("Completion - On Time", i);
        data.__completion_percent_on_time_      = parseFloatWithCommaAndParentheses(doc.GetCell<std::string>("Completion - % On Time", i));
        data.__completion_late_                 = doc.GetCell<int>("Completion - Late", i);
        data.__completion_total_                = doc.GetCell<int>("Completion - Total", i);
        data.__completion_not_complete_         = doc.GetCell<int>("Completion - Not Complete", i);
        data.__completion_exceptions_           = doc.GetCell<int>("Completion - Exceptions", i);

        vect.push_back(data);
    }

    // Inject the vector into the PropertyList by matching the property name
    for (auto &item: vect)
        for (auto &prop: propList())
            if (item.__property_ == prop.__entrata_name_)
                prop.__work_order_performance_.push_back(item);

    // Print the number of "items" (rows of data) processed
    PRINT_NUM_ITEMS_PROCESSED(vect.size());

    sNumRowsProcessed += vect.size();

    PRINT_FUNCTION_STOP();
}

#endif // __input_routines__hpp__