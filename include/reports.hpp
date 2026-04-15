#ifndef __reports__hpp__
#define __reports__hpp__

#include <vector>

struct BirchstoneDashboard
{
    std::string __property_;
    float __occupied_percent_ = -1;
    float __14_day_trend_ = -1;
    float __28_day_trend_ = -1;
    float __56_day_trend_ = -1;
    float __14_day_trend_with_applications_;
    float __28_day_trend_with_applications_;
    float __56_day_trend_with_applications_;
    int   __30_day_traffic_count_;
    float __30_day_closing_ratio_;
    float __occupied_rent_per_sf_;
    int   __previous_30_day_net_move_ins_;
    int   __total_pending_move_ins_;
    int   __open_work_orders_;
    float __percent_work_orders_completed_on_time_;
    float __total_billed_;
    float __current_month_collections_total_;
    float __percent_collected_rent_type_;
    float __delinquency_1_;
    float __delinquency_2_;
    float __delinquency_3_;
    int   __evictions_current_;
    int   __evictions_total_;
    int   __notice_unrented_;
    int   __vacant_unrented_not_ready_;
    int   __vacant_unrented_ready_;
    float __ap_total_outstanding_;
    int   __notice_rented_;
    int   __vacant_rented_ready_;
    float __current_month_renewal_percent_;
    float __prior_month_renewal_percent_;
    int   __expirations_next_month_;
    int   __renewals_next_month_;
    int   __expirations_month_after_next_;
    int   __renewals_month_after_next_;
    int   __current_notice_to_vacate_;
    int   __total_p_;
    int   __total_u_;
    int   __total_r_;
    int   __excluded_units_;
};

struct Availability 
{
    Availability() = default;
    ~Availability() = default;

    std::string __alert_ = "";
    std::string __property_;
    std::string __bldg_unit_;
    std::string __floor_plan_;
    std::string __unit_type_;
    std::string __unit_status_;
    std::string __exclusion_name_;
    int         __days_vacant_;
    std::tm     __move_out_;
    std::string __move_out_str_ = "~";
    std::tm     __available_on_;
    std::tm     __scheduled_move_in_;
    std::string __scheduled_move_in_str_ = "~";
    int         __days_until_move_in_;
    std::string __days_until_move_in_str_ = "~";
    int         __turn_time_mo_avail_;
    std::string __turn_time_mo_avail_str_ = "~";
    int         __available_date_exclusion_;
    std::string __unit_notes_;
    std::string __unit_activity_notes_;
    std::string __hazard_note_;
    float       __market_rent_;
    float       __prior_lease_rent_;
    float       __budgeted_rent_;
    float       __future_lease_rent_   ;
    std::string __future_lease_rent_str_ = "~";
    std::tm     __application_approved_;
    std::string __application_approved_str_ = "~";
};

struct BoxScore_Availability
{
    std::string __property_;
    float       __avg_sqft_;
    float       __avg_market_rent_;
    float       __avg_budgeted_rent_;
    float       __avg_scheduled_rent_;
    int         __units_;
    float       __avg_scheduled_charges_;
    float       __avg_scheduled_other_;
    float       __avg_effective_rent_;
    float       __avg_net_effective_rent_;
    int         __excluded_;
    int         __rentable_units_;
    int         __occupied_;
    int         __vacant_;
    int         __available_;
    int         __occupied_no_notice_;
    int         __notice_rented_;
    int         __notice_unrented_;
    int         __vacant_rented_;
    int         __vacant_unrented_;
    float       __occupied_percent_;
    float       __trend_;
    float       __exposure_;
};

struct BoxScore_LeadConversions
{
    std::string __property_;
    int         __application_partially_completed_;
    int         __application_completed_;
    int         __application_completed_cancelled_;
    int         __application_denied_;
    int         __application_approved_;
    int         __application_approved_cancelled_;
    int         __lease_completed_;
    int         __lease_completed_cancelled_;
    int         __lease_approved_;
};

struct BoxScore_MakeReadyStatus
{
    std::string __property_;
    std::string __status_;
    int         __vacant_rented_;
    int         __vacant_unrented_;
    int         __total_vacant_;
    float       __percent_;
};

struct BoxScore_PropertyPulse
{
    std::string __property_;
    int         __units_;
    int         __move_ins_;
    int         __mtm_;
    int         __mtm_conversions_;
    int         __renewal_offers_completed_;
    int         __transfers_;
    int         __notices_;
    int         __move_outs_;
    int         __renewal_transfers_;
    int         __skips_;
    int         __evictions_;
    int         __leased_;
};

struct DailyAndWeeklyOperations
{
    std::string __property_;
    std::string __lead_source_;
    int         __new_leads_;
    int         __first_visit_tour_;
    int         __applications_partial_;
    int         __applications_completed_;
    int         __applications_completed_cancelled_;
    int         __applications_denied_;
    int         __applications_approved_;
    int         __applications_approved_cancelled_;
    int         __leases_completed_;
    int         __leases_completed_cancelled_;
    int         __leases_approved_;
    
};

struct GrossPotentialRent
{
    std::string __property_;
    int         __unit_space_count_;
    std::string __unit_space_count_str_ = "~";
    float       __gpr_market_rent_;
    float       __total_potential_rent_;
    float       __gain_loss_to_lease_;
    int         __days_vacant_;
    float       __vacancy_;
    float       __vacancy_adjustments_;
    float       __out_of_period_rent_;
    float       __scheduled_rent_;
    float       __rent_adjustments_;
    float       __rent_write_offs_;
    float       __rental_income_;
};

struct IncomeStatementAsCash
{
    typedef std::pair<std::string, float> balance_data;

    std::string  __property_;
    int          __unit_count_;
    std::string  __account_name_;
    balance_data __balance_11_months_ago;
    balance_data __balance_10_months_ago;
    balance_data __balance_9_months_ago;
    balance_data __balance_8_months_ago;
    balance_data __balance_7_months_ago;
    balance_data __balance_6_months_ago;
    balance_data __balance_5_months_ago;
    balance_data __balance_4_months_ago;
    balance_data __balance_3_months_ago;
    balance_data __balance_2_months_ago;
    balance_data __balance_1_months_ago;
    balance_data __balance_0_months_ago;
    float        __total;
};

struct JobCostDetails
{
    std::string __property_;
    std::string __bldg_unit_;
    std::string __gl_account_;
    std::string __gl_account_name_;
    std::tm     __transaction_date_;
    std::string __transaction_date_str_ = "~";
    std::tm     __post_date_;
    std::string __post_date_str_ = "~";
    std::string __post_month_;
    std::string __job_;
    std::string __phase_;
    std::string __reference_;
    std::string __transaction_type_;
    std::string __description_;
    std::string __cost_code_category_;
    float       __transaction_amount_;
    float       __total_;
    float       __remaining_budget_;
    float       __percent_remaining_budget_;
};

struct LeaseTradeOut
{
    std::string __property_;
    std::string __bldg_unit_;
    std::string __unit_;
    std::string __skip_mtm_;
    std::string __unit_type_;
    std::string __sqft_;
    int         __days_vacant_;
    std::string __days_vacant_str_ = "~";
    std::string __prior_resident_;
    std::tm     __move_in_;
    std::string __move_in_str_ = "~";
    std::string __current_resident_;
    std::string __current_lease_type_;
    std::tm     __prior_lease_start_;
    std::tm     __prior_lease_end_;
    std::tm     __current_lease_start_;
    std::tm     __current_lease_end_;
    float       __prior_base_rent_;
    std::string __prior_base_rent_str_ = "~";
    float       __prior_amenity_rent_;
    std::string __prior_amenity_rent_str_ = "~";
    float       __prior_lease_rent_;
    std::string __prior_lease_rent_str_ = "~";
    float       __current_base_rent_;
    std::string __current_base_rent_str_ = "~";
    float       __current_amenity_rent_;
    std::string __current_amenity_rent_str_ = "~";
    float       __current_lease_rent_;
    std::string __current_lease_rent_str_ = "~";
    float       __market_rent_;
    std::string __market_rent_str_ = "~";
    float       __budgeted_rent_;
    std::string __budgeted_rent_str_ = "~";
    float       __lease_rent_change_;
    std::string __lease_rent_change_str_ = "~";

    bool operator<(const LeaseTradeOut& other) const {
        std::tm lhs = __current_lease_start_;
        std::tm rhs = other.__current_lease_start_;
        return std::mktime(&lhs) < std::mktime(&rhs);
    }
};

struct MoveOutReasons
{
    std::string __property_;
    std::string __bldg_unit_;
    std::string __unit_type_;
    std::string __resident_;
    std::tm     __notice_given_;
    std::tm     __lease_end_date_;
    std::tm     __move_out_date_;
    std::string __reason_;
    std::string __early_termination_;
    float       __market_rent_;
    float       __scheduled_rent_;
    float       __deposit_held_;
    float       __balance_;
};

struct ReceiptByChargeCode_Receipts
{
    std::string __property_;
    std::string __charge_code_;
    std::string __gl_account_;
    float       __total_charges_;
    float       __total_cash_collections_;
    float       __credits_concessions_;
    float       __total_collections_;
    float       __percent_collected_;
    std::string __percent_collected_str_ = "~";
};

struct ResidentAgedReceivables_Detail
{
    std::string __property_;
    std::string __bldg_unit_;
    std::string __resident_;
    std::string __lease_status_;
    std::tm     __eviction_start_date_;
    float       __delinquent_total_;
    float       __0_to_30_days_;
    float       __31_to_60_days_;
    float       __61_to_90_days_;
    float       __90_plus_days_;
    float       __pre_payments_;
    float       __balance_;
};

struct ResidentAgedReceivables_Summary
{
    std::string __property_;
    std::string __lease_status_;
    float       __unallocated_charges_credits_;
    float       __0_to_30_days_;
    float       __31_to_60_days_;
    float       __61_to_90_days_;
    float       __90_plus_days_;
    float       __pre_payments_;
    float       __balance_;
};

struct ResidentRetention
{
    std::string __property_;
    std::string __month_;
    int         __units_;
    int         __rentable_units_;
    int         __expiring_leases_;
    int         __early_move_out_;
    float       __early_move_out_percent_;
    int         __ntv_;
    float       __ntv_percent_;
    int         __renewals_;
    float       __renewals_percent_;
    int         __renewal_transfers_;
    float       __renewal_transfers_percent_;
    int         __transfers_;
    float       __transfers_percent_;
    int         __pending_;
    float       __pending_percent_;
    int         __mtm_;
    float       __mtm_percent_;
};

struct RollingRenovation
{
    std::string __property_;
    std::string __bldg_unit_;
    std::string __unit_type_;
    std::string __sqft_;
    std::string __unit_status_;
    std::string __renovation_status_;
    std::string __phase_;
    std::tm     __move_out_date_;
    std::tm     __renovation_start_date_;
    std::string __renovation_start_date_str_ = "~";
    std::tm     __renovation_completion_date_;
    std::string __renovation_completion_date_str_ = "~";
    int         __actual_renovation_days_;
    std::string __actual_renovation_days_str_ = "~";
    std::tm     __move_in_date_;
    std::string __move_in_date_str_ = "~";
    float       __actual_renovation_cost_;
    float       __budgeted_renovation_cost_;
    float       __actual_vs_budget_variance_;
    float       __prior_market_rent_;
    float       __new_market_rent_;
    float       __monthly_unit_premium_;
    float       __monthly_roi_;
    float       __prior_budgeted_rent_;
    float       __new_budgeted_rent_;
};

struct WorkOrderPerformance
{
    std::string __property_;
    std::string __priority_;
    int         __response_previous_work_orders_;
    int         __response_new_work_orders_;
    int         __response_on_time_;
    float       __response_percent_on_time_;
    int         __response_late_;
    int         __response_total_;
    int         __response_not_started_;
    int         __completion_previous_work_orders_;
    int         __completion_new_work_orders_;
    int         __completion_on_time_;
    float       __completion_percent_on_time_;
    int         __completion_late_;
    int         __completion_total_;
    int         __completion_not_complete_;
    int         __completion_exceptions_;
};


#endif // __reports__hpp__