#ifndef RUN_TIME_LOGGER
#define RUN_TIME_LOGGER

#include <chrono>
#include <iostream>
#include <fstream>
#include <thread>
#include <map>
#include <filesystem>

class RunTimeLogger
{
public:
    using clock = std::chrono::high_resolution_clock;
    using timepoint = std::chrono::time_point<clock>;
    enum Status{
        DEFAULT = 0,
        MEASURING = 1,
        PAUSED = 2,
        TERMINATED = 3
    };

    static timepoint global_start;
    static std::map<std::string, std::tuple<int, timepoint, double>> names;
    static std::string logfile_name;
    static std::ofstream LogFile;
    static bool is_running;

    static void StartGlobalTimer();
    static void StartTimer(std::string name);
    static void EndTimer(std::string);
    static void PrintTimerStats();
    static void PrintTimerStatsOnce();
    static void Log(std::string info);
    RunTimeLogger();
    ~RunTimeLogger();
};


#endif
