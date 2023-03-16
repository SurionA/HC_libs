#ifndef hc_utils_h
#define hc_utils_h

    namespace HC_utils {
        using Callback = void (*)();

        void deepSleepLoop(Callback callback, int sleepInterval );

    }

#endif