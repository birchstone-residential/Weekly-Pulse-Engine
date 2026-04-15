#ifndef __Property__hpp__
#define __Property__hpp__

#include "reports.hpp"

struct Property {
    Property() = default;
    ~Property() = default;

    std::string __name_;
    std::string __entrata_name_;
    unsigned    __id_;

    BirchstoneDashboard                          __birchstone_dashboard_;
    std::vector<Availability>                    __availability_;
    BoxScore_Availability                        __box_score_availability_;
    BoxScore_LeadConversions                     __box_score_lead_conversions_;
    std::vector<BoxScore_MakeReadyStatus>        __box_score_make_ready_status_;
    BoxScore_PropertyPulse                       __box_score_property_pulse_;
    std::vector<DailyAndWeeklyOperations>        __daily_and_weekly_operations_;
    std::vector<GrossPotentialRent>              __gross_potential_rent_;
    IncomeStatementAsCash                        __income_statement_as_cash_;
    std::vector<JobCostDetails>                  __job_cost_details_;
    std::vector<LeaseTradeOut>                   __lease_trade_out_;
    std::vector<MoveOutReasons>                  __move_out_reasons_;
    std::vector<ReceiptByChargeCode_Receipts>    __receipt_by_charge_code_receipts_;
    std::vector<ResidentAgedReceivables_Detail>  __resident_aged_receivables_detail_;
    std::vector<ResidentAgedReceivables_Summary> __resident_aged_receivables_summary_;
    std::vector<ResidentRetention>               __resident_retention_;
    std::vector<WorkOrderPerformance>            __work_order_performance_;
    std::vector<RollingRenovation>               __rolling_renovation_;
};

#endif // __Property__hpp__