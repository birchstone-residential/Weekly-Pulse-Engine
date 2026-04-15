#ifndef __output_routines__hpp__
#define __output_routines__hpp__

#include "PropertyList.hpp"
#include "dictionaries.hpp"

// Utility to create output directory
void createOutputDirectory()
{
    std::string path = "data/" + sExportDate + "/bin/";
    std::cout << "~ Creating directory: \t\t (" << path << ")" << std::endl;
    fs::create_directories(path);

    path = "data/" + sExportDate + "/bin_2/";
    std::cout << "~ Creating directory: \t\t (" << path << ")" << std::endl;
    fs::create_directories(path);
}

// Utility to assign alerts to Availability entries
void assignAlert(Availability& entry) noexcept(false)
{
    // If the turn time is greater than 30 days and the unit is not excluded, assign alert
    if ( entry.__turn_time_mo_avail_str_.size() > 0  &&  entry.__exclusion_name_.size() == 0 ) // Excludes units with Exclusion Name
    {
        if ( entry.__turn_time_mo_avail_ > 30 ) 
        {
            entry.__alert_ = "Unit Turn Exceeded 30 Days";
        }
    }

    // If the unit is not ready and the available date is in the past, assign alert
    if ( daysBetween(stotm(sExportDate_Forward_Slash_Format), entry.__available_on_) < 0  &&  entry.__exclusion_name_.size() == 0 ) // Excludes units with Exclusion Name
    {
        if ( entry.__unit_status_.find("Not Ready") != std::string::npos )
        {
            entry.__alert_ = "Not Ready Past Available Date";
        }
    }

    // If the unit is vacant and the move-in date is in the past, assign alert
    if ( entry.__scheduled_move_in_str_.size() > 0  &&  entry.__exclusion_name_.size() == 0 ) // Excludes units with Exclusion Name
    {
        if ( daysBetween(stotm(sExportDate_Forward_Slash_Format), entry.__scheduled_move_in_) < 0 )
        {
            if ( entry.__unit_status_.find("Vacant Rented Ready (Unavailable)")     != std::string::npos  || 
                 entry.__unit_status_.find("Vacant Rented Not Ready (Unavailable)") != std::string::npos )
            
            {
                entry.__alert_ = "Past Move-In Date";
            }
        }     
    }

    // If the unit is vacant and the move-out date is in the past, assign alert
    if ( entry.__move_out_str_.size() > 0  &&  entry.__exclusion_name_.size() == 0 ) // Excludes units with Exclusion Name
    {
        if ( daysBetween(stotm(sExportDate_Forward_Slash_Format), entry.__move_out_) < 0 )
        {
            if ( entry.__unit_status_.find("Notice Rented (Unavailable)") != std::string::npos  || 
                 entry.__unit_status_.find("Notice Unrented (Available)") != std::string::npos )
            
            {
                entry.__alert_ = "Past Move-Out Date";
            }
        }     
    }

    // If the unit has an available date more than 210 days from current date, assign alert
    if ( entry.__move_out_str_.size() > 0  &&  entry.__exclusion_name_.size() == 0 ) // Excludes units with Exclusion Name
    {
        if ( daysBetween(stotm(sExportDate_Forward_Slash_Format), entry.__available_on_) > 210  &&  entry.__turn_time_mo_avail_ > 210 )
        {
            entry.__alert_ = "Excluded By Available Date";
        }
    }
    
}

// Write "Availability Report.csv" to bin directory
void writeAvailabilityReport(PropertyList& propList) noexcept(false)
{   
    static const std::string FILENAME = "data/" + sExportDate + "/bin_2/Tracker Sheet.csv";

    std::ofstream outFS;

    outFS.open(FILENAME, std::ios::out);

    // Write header
    outFS << "Date,Alerts,Property,Bldg-Unit,Floor Plan,Unit Type,Unit Status,Exclusion Name,Days Vacant,Move-Out,Available On,Scheduled Move-In,Days Until Move In,Turn Time [MO-Avail],Available Date Exclusion,Unit Notes,Market Rent,Prior Lease Rent,Budgeted Rent,Future Lease Rent,Application Approved" << std::endl;

    for (auto &prop: propList())
    {
        for (auto &entry: prop.__availability_)
        {
            outFS << sExportDate_Forward_Slash_Format << ",";
            
            /// TODO: Alerts stuff
            assignAlert(entry);
            outFS << entry.__alert_ << ",";

            outFS << prop.__name_ << ","
                  << entry.__bldg_unit_ << ","
                  << entry.__floor_plan_ << ","
                  << entry.__unit_type_ << ","
                  << entry.__unit_status_ << ",";
            
            ( entry.__exclusion_name_.size() > 0 ) 
                ? outFS << entry.__exclusion_name_ << ","
                : outFS << "Not Excluded" << ",";

            outFS << entry.__days_vacant_ << ",";

            ( entry.__move_out_str_.size() > 0 ) 
                ? outFS << tmtostr(entry.__move_out_) << "," 
                : outFS << ",";

            outFS << tmtostr(entry.__available_on_) << ",";

            ( entry.__scheduled_move_in_str_.size() > 0 ) 
                ? outFS << tmtostr(entry.__scheduled_move_in_) << "," 
                : outFS << ",";
            
            if ( entry.__scheduled_move_in_str_.size() > 0 ) 
            {
                outFS << daysBetween(
                            stotm(sExportDate_Forward_Slash_Format),
                            entry.__scheduled_move_in_) << ",";
            }
            else
            {
                outFS << ",";
            }
            
            ( entry.__turn_time_mo_avail_str_.size() > 0 )
                ? outFS << entry.__turn_time_mo_avail_ << ","
                : outFS << ",";

            outFS << daysBetween(
                        stotm(sExportDate_Forward_Slash_Format),
                        entry.__available_on_) << ",";
                
            outFS << "\"" << entry.__unit_notes_ << "\"" << ","
                  << entry.__market_rent_ << ","
                  << entry.__prior_lease_rent_ << ","
                  << entry.__budgeted_rent_ << ",";

            ( entry.__future_lease_rent_str_.size() > 0 ) 
                ? outFS << entry.__future_lease_rent_ << ","
                : outFS << ",";

            ( entry.__application_approved_str_.size() > 0 )
                ? outFS << tmtostr(entry.__application_approved_) << std::endl
                : outFS << std::endl;
        }
    }

    if ( fs::exists(FILENAME) )
    {
        sNumFilesGenerated += 1;
        PRINT_WRITE_FILE_SUCCESS_MSG(FILENAME);
    }
    else
    {   
        PRINT_WRITE_FILE_FAILURE_MSG(FILENAME);
        throw std::runtime_error("❌ Failed to generate file: " + FILENAME);
    }

    outFS.close();
}

// Write "Overview Report.csv" to bin directory
void writeOverviewReport(PropertyList& propList) noexcept(false)
{
    static const std::string FILENAME = "data/" + sExportDate + "/bin/Overview Report.csv";

    std::ofstream outFS;

    outFS.open(FILENAME, std::ios::out);

    // Write header
    outFS << "Property,Date,Metric,Value,Origin,Decoder,Section" << std::endl;

    for (auto &prop: propList())
    {
        outFS << prop.__name_ << "," << sExportDate_Forward_Slash_Format << "," << "Occupied %," << prop.__birchstone_dashboard_.__occupied_percent_ << "," << "Birchstone Dashboard Report," << "Occupancy," << "Operational KPI" << std::endl;
        outFS << prop.__name_ << "," << sExportDate_Forward_Slash_Format << "," << "28 Day Trend," << prop.__birchstone_dashboard_.__28_day_trend_ << "," << "Birchstone Dashboard Report," << "Trended Occ - 30 Days," << "Operational KPI" << std::endl;
        outFS << prop.__name_ << "," << sExportDate_Forward_Slash_Format << "," << "28 Day Trend w/ Apps," << prop.__birchstone_dashboard_.__28_day_trend_with_applications_ << "," << "Birchstone Dashboard Report," << "Trended Occ w/ Apps - 30 Days," << "Operational KPI" << std::endl;
        outFS << prop.__name_ << "," << sExportDate_Forward_Slash_Format << "," << "56 Day Trend," << prop.__birchstone_dashboard_.__56_day_trend_ << "," << "Birchstone Dashboard Report," << "Trended Occ - 60 Days," << "Operational KPI" << std::endl;
        outFS << prop.__name_ << "," << sExportDate_Forward_Slash_Format << "," << "56 Day Trend w/ Apps," << prop.__birchstone_dashboard_.__56_day_trend_with_applications_ << "," << "Birchstone Dashboard Report," << "Trended Occ w/ Apps - 60 Days," << "Operational KPI" << std::endl;
        
        float totalPotentialRent = 0.0f;
        float totalVacancyLoss = 0.0f;

        for (auto &entry: prop.__gross_potential_rent_)
        {
            totalPotentialRent += entry.__total_potential_rent_;
            totalVacancyLoss += entry.__vacancy_;
        }

        outFS << prop.__name_ << "," << sExportDate_Forward_Slash_Format << "," << "Sum of Total Potential Rent," << totalPotentialRent << "," << "GPR Report," << "01. Total Potential Rent," << "Collections" << std::endl;
        outFS << prop.__name_ << "," << sExportDate_Forward_Slash_Format << "," << "Sum of Vacancy Loss," << totalVacancyLoss << "," << "GPR Report," << "02. Vacancy Loss," << "Collections" << std::endl;

        float totalRentCharges = 0;
        float totalRentCollected = 0;

        for (auto &entry: prop.__receipt_by_charge_code_receipts_)
        {
            totalRentCharges += entry.__total_charges_;
            totalRentCollected += entry.__total_collections_;
        }

        outFS << prop.__name_ << "," << sExportDate_Forward_Slash_Format << "," << "Sum of Total Charges," << totalRentCharges << "," << "Receipts by Charge Code (Rent)," << "03. Total Rent Charges," << "Collections" << std::endl;
        outFS << prop.__name_ << "," << sExportDate_Forward_Slash_Format << "," << "Sum of Total Collections," << totalRentCollected << "," << "Receipts by Charge Code (Rent)," << "04. Total Rent Collected," << "Collections" << std::endl;

        float totalPercentCollected = totalRentCollected / totalRentCharges;
        // Guard rails for dividing by 0
        if (totalRentCharges == 0.f)
        {
            totalPercentCollected = 0.f;
        }

        outFS << prop.__name_ << "," << sExportDate_Forward_Slash_Format << "," << "% Collected," << totalPercentCollected << "," << "Receipts by Charge Code (Rent)," << "05. % Collected," << "Collections" << std::endl;

        float totalDelinquent = 0;
        float totalDelinquentCurrent = 0;
        float totalDelinquentEviction = 0;
        float netCurrentBalance = 0;
        float net31to60Balance = 0;
        float net61to90Balance = 0;
        float net90PlusBalance = 0;

        for (auto &entry: prop.__resident_aged_receivables_detail_)
        {
            totalDelinquent += entry.__delinquent_total_;
            netCurrentBalance += entry.__0_to_30_days_;
            net31to60Balance += entry.__31_to_60_days_;
            net61to90Balance += entry.__61_to_90_days_;
            net90PlusBalance += entry.__90_plus_days_;

            if ( entry.__lease_status_.find("Eviction") != SIZE_MAX )
                totalDelinquentEviction += entry.__delinquent_total_;
            else
                totalDelinquentCurrent += entry.__delinquent_total_;
        }

        outFS << prop.__name_ << "," << sExportDate_Forward_Slash_Format << "," << "Sum of Delinquent Total," << totalDelinquent << "," << "Resident Aged Receivables (Detail)," << "06. Delinquent Total," << "Collections" << std::endl;
        outFS << prop.__name_ << "," << sExportDate_Forward_Slash_Format << "," << "Total Delinquent - Eviction," << totalDelinquentEviction << "," << "Resident Aged Receivables (Detail)," << "07. Total Delinquent - Eviction," << "Collections" << std::endl;
        outFS << prop.__name_ << "," << sExportDate_Forward_Slash_Format << "," << "Total Delinquent - Current," << totalDelinquentCurrent << "," << "Resident Aged Receivables (Detail)," << "08. Total Delinquent - Current," << "Collections" << std::endl;
        outFS << prop.__name_ << "," << sExportDate_Forward_Slash_Format << "," << "Sum of Net Current Balance," << netCurrentBalance << "," << "Resident Aged Receivables (Detail)," << "09. Net Current Balance," << "Collections" << std::endl;
        outFS << prop.__name_ << "," << sExportDate_Forward_Slash_Format << "," << "Sum of Net 31-60 Day Balance," << net31to60Balance << "," << "Resident Aged Receivables (Detail)," << "10. Net 31-60 Day Balance," << "Collections" << std::endl;
        outFS << prop.__name_ << "," << sExportDate_Forward_Slash_Format << "," << "Sum of Net 61-90 Day Balance," << net61to90Balance << "," << "Resident Aged Receivables (Detail)," << "11. Net 61-90 Day Balance," << "Collections" << std::endl;
        outFS << prop.__name_ << "," << sExportDate_Forward_Slash_Format << "," << "Sum of Net 90+ Balance," << net90PlusBalance << "," << "Resident Aged Receivables (Detail)," << "12. Net 90+ Day Balance," << "Collections" << std::endl;

        int totalCancelledApps = prop.__box_score_lead_conversions_.__application_approved_cancelled_ + prop.__box_score_lead_conversions_.__application_completed_cancelled_;

        outFS << prop.__name_ << "," << sExportDate_Forward_Slash_Format << "," << "Open Work Orders," << prop.__birchstone_dashboard_.__open_work_orders_ << "," << "Birchstone Dashboard Report," << "Outstanding Work Orders," << "Weekly Activity" << std::endl;
        outFS << prop.__name_ << "," << sExportDate_Forward_Slash_Format << "," << "Application - Completed," << prop.__box_score_lead_conversions_.__application_completed_ << "," << "Box Score - Lead Conversions," << "Completed Applications," << "Weekly Activity" << std::endl;
        outFS << prop.__name_ << "," << sExportDate_Forward_Slash_Format << "," << "Application - Denied," << prop.__box_score_lead_conversions_.__application_denied_ << "," << "Box Score - Lead Conversions," << "Denied Applications," << "Weekly Activity" << std::endl;
        outFS << prop.__name_ << "," << sExportDate_Forward_Slash_Format << "," << "Application - Approved (Cancelled)," << totalCancelledApps << "," << "Box Score - Lead Conversions," << "Cancelled Applications," << "Weekly Activity" << std::endl;
        outFS << prop.__name_ << "," << sExportDate_Forward_Slash_Format << "," << "Application - Approved," << prop.__box_score_lead_conversions_.__application_approved_ << "," << "Box Score - Lead Conversions," << "Approved Applications," << "Weekly Activity" << std::endl;
        outFS << prop.__name_ << "," << sExportDate_Forward_Slash_Format << "," << "Lease - Completed," << prop.__box_score_lead_conversions_.__lease_completed_ << "," << "Box Score - Lead Conversions," << "Signed Leases," << "Weekly Activity" << std::endl;
        outFS << prop.__name_ << "," << sExportDate_Forward_Slash_Format << "," << "Move Ins," << prop.__box_score_property_pulse_.__move_ins_ << "," << "Box Score - Property Pulse," << "Move Ins," << "Weekly Activity" << std::endl;
        outFS << prop.__name_ << "," << sExportDate_Forward_Slash_Format << "," << "Move Outs," << prop.__box_score_property_pulse_.__move_outs_ << "," << "Box Score - Property Pulse," << "Move Outs," << "Weekly Activity" << std::endl;
        outFS << prop.__name_ << "," << sExportDate_Forward_Slash_Format << "," << "Skips," << prop.__box_score_property_pulse_.__skips_ << "," << "Box Score - Property Pulse," << "Skips," << "Weekly Activity" << std::endl;

        std::vector<std::string> reasons;
        for (auto &moveOut: prop.__move_out_reasons_)
            reasons.push_back(moveOut.__reason_);

        std::sort(reasons.begin(), reasons.end());

        // Map to store each string and its count
        std::map<std::string, int> reasonCount;

        // Count occurrences of each string
        for (const auto& reason : reasons) 
            reasonCount[reason]++;

        // Create a vector of pairs from the map
        std::vector<std::pair<std::string, int>> result;
        for (const auto& entry : reasonCount) 
            result.push_back(entry);

        // Output the results
        for (const auto& entry : result) 
        {
            outFS << prop.__name_ << "," << sExportDate_Forward_Slash_Format << "," << entry.first << "," << entry.second << "," << "Move Out Reasons Report," << "Reason For Move Out" << "," << "Reason For Move Out" << std::endl;
        }
    }

    if ( fs::exists(FILENAME) )
    {
        sNumFilesGenerated += 1;
        PRINT_WRITE_FILE_SUCCESS_MSG(FILENAME);
    }
    else
    {   
        PRINT_WRITE_FILE_FAILURE_MSG(FILENAME);
        throw std::runtime_error("❌ Failed to generate file: " + FILENAME);
    }

    outFS.close();
}

// Write "Resident Retention Report.csv" to bin directory
void writeResidentRetentionReport(PropertyList& propList) noexcept(false)
{
    static const std::string FILENAME = "data/" + sExportDate + "/bin/Resident Retention Report.csv";
    std::ofstream outFS;

    outFS.open(FILENAME, std::ios::out);

    // Write header
    outFS << "Property,Date,Period,Gross Expiring Leases,Early Move Out,Early Move Out %,NTV,NTV %,Renewal,Renewal %,Transfers,Transfers %,Remaining Expiration,Remaining Expiration %,MTM,MTM %" << std::endl;
    for (auto &prop : propList())
    {
        for (auto &entry : prop.__resident_retention_)
        {
            outFS << prop.__name_ << "," 
                  << sExportDate_Forward_Slash_Format << "," 
                  << transformDatePeriodStr(entry.__month_) << "," 
                  << entry.__expiring_leases_ << "," 
                  << entry.__early_move_out_ << "," 
                  << entry.__early_move_out_percent_ << "," 
                  << entry.__ntv_ << "," 
                  << entry.__ntv_percent_ << "," 
                  << entry.__renewals_ << "," 
                  << entry.__renewals_percent_ << ","
                  << entry.__transfers_ << ","
                  << entry.__transfers_percent_ << ","
                  << entry.__pending_ << ","
                  << entry.__pending_percent_ << ","
                  << entry.__mtm_ << ","
                  << entry.__mtm_percent_ << std::endl;
        }
    }

    if ( fs::exists(FILENAME) )
    {
        sNumFilesGenerated += 1;
        PRINT_WRITE_FILE_SUCCESS_MSG(FILENAME);
    }
    else
    {   
        PRINT_WRITE_FILE_FAILURE_MSG(FILENAME);
        throw std::runtime_error("❌ Failed to generate file: " + FILENAME);
    }

    outFS.close();
}

// Write "Income Report.csv" to bin directory
void writeIncomeReport(PropertyList& propList) noexcept(false)
{
    static const std::string FILENAME = "data/" + sExportDate + "/bin/Income Report.csv";
    std::ofstream outFS;

    outFS.open(FILENAME, std::ios::out);

    // Write header
    outFS << "Property,Date,Period,Value" << std::endl;
    for (auto &prop : propList())
    {
        outFS << prop.__name_ << "," << sExportDate_Forward_Slash_Format << "," << (transformDatePeriodStr(prop.__income_statement_as_cash_.__balance_11_months_ago.first)) << "," << prop.__income_statement_as_cash_.__balance_11_months_ago.second << std::endl;
        outFS << prop.__name_ << "," << sExportDate_Forward_Slash_Format << "," << (transformDatePeriodStr(prop.__income_statement_as_cash_.__balance_10_months_ago.first)) << "," << prop.__income_statement_as_cash_.__balance_10_months_ago.second << std::endl;
        outFS << prop.__name_ << "," << sExportDate_Forward_Slash_Format << "," << (transformDatePeriodStr(prop.__income_statement_as_cash_.__balance_9_months_ago.first)) << "," << prop.__income_statement_as_cash_.__balance_9_months_ago.second << std::endl;
        outFS << prop.__name_ << "," << sExportDate_Forward_Slash_Format << "," << (transformDatePeriodStr(prop.__income_statement_as_cash_.__balance_8_months_ago.first)) << "," << prop.__income_statement_as_cash_.__balance_8_months_ago.second << std::endl;
        outFS << prop.__name_ << "," << sExportDate_Forward_Slash_Format << "," << (transformDatePeriodStr(prop.__income_statement_as_cash_.__balance_7_months_ago.first)) << "," << prop.__income_statement_as_cash_.__balance_7_months_ago.second << std::endl;
        outFS << prop.__name_ << "," << sExportDate_Forward_Slash_Format << "," << (transformDatePeriodStr(prop.__income_statement_as_cash_.__balance_6_months_ago.first)) << "," << prop.__income_statement_as_cash_.__balance_6_months_ago.second << std::endl;
        outFS << prop.__name_ << "," << sExportDate_Forward_Slash_Format << "," << (transformDatePeriodStr(prop.__income_statement_as_cash_.__balance_5_months_ago.first)) << "," << prop.__income_statement_as_cash_.__balance_5_months_ago.second << std::endl;
        outFS << prop.__name_ << "," << sExportDate_Forward_Slash_Format << "," << (transformDatePeriodStr(prop.__income_statement_as_cash_.__balance_4_months_ago.first)) << "," << prop.__income_statement_as_cash_.__balance_4_months_ago.second << std::endl;
        outFS << prop.__name_ << "," << sExportDate_Forward_Slash_Format << "," << (transformDatePeriodStr(prop.__income_statement_as_cash_.__balance_3_months_ago.first)) << "," << prop.__income_statement_as_cash_.__balance_3_months_ago.second << std::endl;
        outFS << prop.__name_ << "," << sExportDate_Forward_Slash_Format << "," << (transformDatePeriodStr(prop.__income_statement_as_cash_.__balance_2_months_ago.first)) << "," << prop.__income_statement_as_cash_.__balance_2_months_ago.second << std::endl;
        outFS << prop.__name_ << "," << sExportDate_Forward_Slash_Format << "," << (transformDatePeriodStr(prop.__income_statement_as_cash_.__balance_1_months_ago.first)) << "," << prop.__income_statement_as_cash_.__balance_1_months_ago.second << std::endl;   
        outFS << prop.__name_ << "," << sExportDate_Forward_Slash_Format << "," << (transformDatePeriodStr(prop.__income_statement_as_cash_.__balance_0_months_ago.first)) << "," << prop.__income_statement_as_cash_.__balance_0_months_ago.second << std::endl;
    }

    if ( fs::exists(FILENAME) )
    {
        sNumFilesGenerated += 1;
        PRINT_WRITE_FILE_SUCCESS_MSG(FILENAME);
    }
    else
    {   
        PRINT_WRITE_FILE_FAILURE_MSG(FILENAME);
        throw std::runtime_error("❌ Failed to generate file: " + FILENAME);
    }

    outFS.close();
}

// Write "Operations Report.csv" to bin directory
void writeOperationsReport(PropertyList& propList) noexcept(false)
{
    static const std::string FILENAME = "data/" + sExportDate + "/bin/Operations Report.csv";
    std::ofstream outFS;

    outFS.open(FILENAME, std::ios::out);

    // Write header
    outFS << "Property,"
          << "Date,"
          << "Lead Source,"
          << "New Leads,"
          << "First Visit/Tour,"
          << "Applications Partially Completed,"
          << "Applications Completed,"
          << "Applications Completed (Cancelled),"
          << "Applications Denied,"
          << "Applications Approved,"
          << "Applications Approved (Cancelled),"
          << "Leases Completed,"
          << "Leases Completed (Cancelled),"
          << "Leases Approved"; // add comma if extended
    outFS << std::endl;
    for (auto &prop : propList())
    {
        for (auto &entry : prop.__daily_and_weekly_operations_)
        {
            outFS << prop.__name_                              << "," 
                  << sExportDate_Forward_Slash_Format          << "," 
                  << entry.__lead_source_                      << "," 
                  << entry.__new_leads_                        << "," 
                  << entry.__first_visit_tour_                 << ","
                  << entry.__applications_partial_             << ","
                  << entry.__applications_completed_           << ","
                  << entry.__applications_completed_cancelled_ << ","
                  << entry.__applications_denied_              << ","
                  << entry.__applications_approved_            << ","
                  << entry.__applications_approved_cancelled_  << ","
                  << entry.__leases_completed_                 << ","
                  << entry.__leases_completed_cancelled_       << ","
                  << entry.__leases_approved_                  << ","

                  << std::endl;
        }
    }

    if ( fs::exists(FILENAME) )
    {
        sNumFilesGenerated += 1;
        PRINT_WRITE_FILE_SUCCESS_MSG(FILENAME);
    }
    else
    {   
        PRINT_WRITE_FILE_FAILURE_MSG(FILENAME);
        throw std::runtime_error("❌ Failed to generate file: " + FILENAME);
    }

    outFS.close();
}

// Write "Facilities Maintenance Report.csv" to bin directory
void writeFacilitiesMaintenanceReport(PropertyList& propList) noexcept(false)
{
    static const std::string FILENAME = "data/" + sExportDate + "/bin/Facilities Maintenance Report.csv";
    std::ofstream outFS;

    outFS.open(FILENAME, std::ios::out);

    // Write header
    outFS << "Property,Date,Type,Status,%,Alert" << std::endl;

    // Write 'Make Ready Status' Data
    for (auto &prop : propList())
    {
        for (auto &entry : prop.__box_score_make_ready_status_)
        {
            if (entry.__status_ == "Ready")
            {
                outFS << prop.__name_ << ","
                    << sExportDate_Forward_Slash_Format << ","
                    << "Make Ready,"
                    << entry.__status_ << ","
                    << entry.__percent_ << ",";
                    
                if (entry.__percent_ < .5)
                    outFS << "Watchlist,";

                outFS << std::endl;
            }
        }
    }

    // Write 'Box Score - Availability' data
    for (auto &prop : propList())
    {        
        outFS << prop.__name_ 
              << "," << sExportDate_Forward_Slash_Format << ","
              << "Exposure," << "," 
              << prop.__box_score_availability_.__exposure_ << ",";

        if (prop.__box_score_availability_.__exposure_ > .1)
            outFS << "Watchlist,";   
        
        outFS << std::endl;
    }

    if ( fs::exists(FILENAME) )
    {
        sNumFilesGenerated += 1;
        PRINT_WRITE_FILE_SUCCESS_MSG(FILENAME);
    }
    else
    {   
        PRINT_WRITE_FILE_FAILURE_MSG(FILENAME);
        throw std::runtime_error("❌ Failed to generate file: " + FILENAME);
    }

    outFS.close();
}

// Write "Job Costing Report.csv" to bin directory
void writeJobCostingReport(PropertyList& propList) noexcept(false)
{
    static const std::string FILENAME = "data/" + sExportDate + "/bin/Job Costing Report.csv";
    std::ofstream outFS;

    outFS.open(FILENAME, std::ios::out);

    // Write header
    outFS << "Property,"
          << "Date," 
          << "Bldg-Unit,"
          << "Unit Type,"
          << "Unit Status,"
          << "Reno Status,"
          << "Phase,"
          << "Move-Out Date,"
          << "Reno Begin,"
          << "Reno End,"
          << "Days In Reno,"
          << "Move-In Date,"
          << "Actual Reno Cost,"
          << "Budgeted Reno Cost,"
          << "Actual vs Budget Variance,"
          << "Prior Lease Rent,"
          << "Current Lease Rent,"
          << "Prior Premium,"
          << "Current Premium,"
          << "Premium Variance," 
          << "Annual Premium,"
          << "ROI,"
          << "Prior Market Rent (Classic),"
          << "Current Market Rent (Classic),"
          << "Current Market Rent (Premium),"
          << "Prior Budgeted Rent,"
          << "New Budgeted Rent,"
          << std::endl;
    
    for (auto &prop: propList())
    {
        for (auto &reno: prop.__rolling_renovation_)
        {
            std::string reno_bldg_unit = reno.__bldg_unit_;
            bool found_first = false;
            bool found_last = false;
            std::vector<LeaseTradeOut> matching_ltos;
            
            // Find matching Lease Trade Out entries
            for (auto &lto: prop.__lease_trade_out_)
            {
                // Only consider completed renovations
                if (reno.__renovation_status_ != "Completed ")
                    break;

                std::string lto_bldg_unit = lto.__bldg_unit_;
                bool matchFound = (lto_bldg_unit == reno_bldg_unit) ? true : false;
                
                if (matchFound)
                {
                    if (!found_first)
                    {
                        found_first = true;
                    }

                    matching_ltos.push_back(lto);
                }
                else if (!matchFound  &&  found_first)
                {
                    found_last = true;
                }

                if (found_last)
                {
                    break;
                }
            }

            std::cout << prop.__name_ << " - " << "Found " << matching_ltos.size() << " matches for bldg-unit: " << reno_bldg_unit << std::endl;
            std::cout << "Renovation Completed Date: " << tmtostr(reno.__renovation_completion_date_) << std::endl;

            // Sort the matching Lease Trade Out entries by move-in date
            std::sort(matching_ltos.begin(), matching_ltos.end());
            
            LeaseTradeOut* prior_reno_lease = nullptr;
            LeaseTradeOut* post_reno_lease = nullptr;

            int count = 0;
            for (auto &match: matching_ltos)
            {
                std::cout << "LTO " << count + 1 << "/" << matching_ltos.size() << std::endl;
                std::cout << "Lease Start: " << tmtostr(match.__current_lease_start_) << std::endl;

                if ( !prior_reno_lease  &&  isBefore(match.__current_lease_start_, reno.__renovation_completion_date_) )
                {
                    std::cout << "Found match for prior_reno_lease" << std::endl;
                    prior_reno_lease = &match;
                }
                else if ( !post_reno_lease  &&  isAfterOrEqual(match.__current_lease_start_, reno.__renovation_completion_date_) )
                {
                    std::cout << "Found match for post_reno_lease" << std::endl;
                    post_reno_lease = &match;
                }

                count++;
            }

            if (reno.__actual_renovation_cost_ == 0)
            {
                std::cout << "Aborting: Actual Renovation Cost is 0" << std::endl;
            }

            if (prior_reno_lease  &&  post_reno_lease)
            {
                std::cout << "Found both prior and post renovation leases" << std::endl;
                std::cout << "Renovation Completed Date: " << tmtostr(reno.__renovation_completion_date_) << std::endl;
                std::cout << "Prior: " << tmtostr(prior_reno_lease->__current_lease_start_) << std::endl;
                std::cout << "Post: " << tmtostr(post_reno_lease->__current_lease_start_) << std::endl;

                // Write Property Name
                outFS << prop.__name_ << ",";
                // Write Export Date
                outFS << sExportDate_Forward_Slash_Format << ",";
                // Write Bldg-Unit
                outFS << reno.__bldg_unit_ << ",";
                // Write Unit Type
                outFS << reno.__unit_type_ << ",";
                // Write Unit Status
                outFS << reno.__unit_status_ << ",";
                // Write Reno Status
                outFS << removeSpaces(reno.__renovation_status_) << ",";
                // Write Phase
                outFS << reno.__phase_ << ",";
                // Write Move-Out Date
                outFS << tmtostr(reno.__move_out_date_) << ",";
                // Write Reno Begin
                outFS << tmtostr(reno.__renovation_start_date_) << ",";
                // Write Reno End
                outFS << tmtostr(reno.__renovation_completion_date_) << ",";
                // Write Days In Reno
                outFS << reno.__actual_renovation_days_ << ",";
                // Write Move-In Date
                outFS << tmtostr(post_reno_lease->__current_lease_start_) << ",";
                // Write Actual Renovation Cost
                outFS << reno.__actual_renovation_cost_ << ",";
                // Write Budgeted Renovation Cost
                outFS << reno.__budgeted_renovation_cost_ << ",";
                // Write Actual vs Budget Variance
                outFS << reno.__actual_vs_budget_variance_ << ",";
                // Write Prior Lease - Current Lease Rent
                outFS << prior_reno_lease->__current_lease_rent_ << ",";
                // Write Current Lease - Current Lease Rent
                outFS << post_reno_lease->__current_lease_rent_ << ",";
                // Write Prior Premium
                outFS << prior_reno_lease->__current_amenity_rent_ << ",";
                // Write Current Premium
                outFS << post_reno_lease->__current_amenity_rent_ << ",";
                // Write Premium Variance
                outFS << post_reno_lease->__current_amenity_rent_ - prior_reno_lease->__current_amenity_rent_ << ",";
                // Write Annual Premium
                outFS << post_reno_lease->__current_amenity_rent_ * 12 << ",";
                // Write ROI
                outFS << (post_reno_lease->__current_amenity_rent_ * 12) / reno.__actual_renovation_cost_ << ",";
                // Write Prior Market Rent (Classic)
                outFS << prior_reno_lease->__market_rent_ << ",";
                // Write Current Market Rent (Classic)
                outFS << post_reno_lease->__market_rent_ << ",";
                // Write Current Market Rent (Premium)
                outFS << post_reno_lease->__current_amenity_rent_ << ",";
                // Write Prior Budgeted Rent
                outFS << reno.__prior_budgeted_rent_ << ",";
                // Write New Budgeted Rent
                outFS << reno.__new_budgeted_rent_ << ",";
                // Write end of line
                outFS << std::endl;
            }
            else if ( !prior_reno_lease  &&  post_reno_lease )
            {
                std::cout << "Incomplete: Found ONLY post renovation lease" << std::endl;
            }
            else if ( prior_reno_lease  &&  !post_reno_lease )
            {
                std::cout << "Incomplete: Found ONLY prior renovation lease" << std::endl;
            }
            else if ( !prior_reno_lease  &&  !post_reno_lease )
            {
                std::cout << "Incomplete: Found NEITHER prior nor post renovation lease" << std::endl;
            }
        }
    }
    
    if ( fs::exists(FILENAME) )
    {
        sNumFilesGenerated += 1;
        PRINT_WRITE_FILE_SUCCESS_MSG(FILENAME);
    }
    else
    {
        PRINT_WRITE_FILE_FAILURE_MSG(FILENAME);
        throw std::runtime_error("❌ Failed to generate file: " + FILENAME);
    }

    outFS.close();
}

#endif // __output_routines__hpp__