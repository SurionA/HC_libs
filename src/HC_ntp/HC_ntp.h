#ifndef hc_ntp_h
#define hc_ntp_h

    namespace HC_ntp {

        void init(String timezone);
        void setTimezone(String timezone);
        void printLocalTime();
        int getMinutes();
        int getSencond();
        int getDelaySyncTime(int sleepInterval);

    }

#endif