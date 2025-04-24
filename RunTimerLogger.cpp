#include "RunTimeLogger.h"

RunTimeLogger::timepoint RunTimeLogger::global_start;
std::map<std::string, std::tuple<int, RunTimeLogger::timepoint, double>> RunTimeLogger::names;
std::string RunTimeLogger::logfile_name;
std::ofstream RunTimeLogger::LogFile;
bool RunTimeLogger::is_running;


void RunTimeLogger::StartGlobalTimer(){
    std::cout << "Starting Global Timer" << std::endl;
    global_start = clock::now();
}


void RunTimeLogger::StartTimer(std::string name){
    if(names.find(name) != names.end()){
        int status = std::get<0>(names[name]);
        if(status == Status::MEASURING){
            std::ostringstream oss;
            oss << "Incorrect Calling of the StartTimer function, Name :"
            << name << "Status before calling StartTimer : " << status << std::endl;
            throw std::logic_error(oss.str());
        }
        names[name] = std::make_tuple(Status::MEASURING, clock::now(), std::get<2>(names[name]));
    }
    else{
        names[name] = std::make_tuple(Status::MEASURING, clock::now(), 0);
    }
}
void RunTimeLogger::EndTimer(std::string name){
    if(names.find(name) == names.end()){
        std::ostringstream oss;
        oss << "Cannot end Timer for not registered name : " << name << std::endl;
        throw std::logic_error(oss.str());
    }
    timepoint currenttime = clock::now();
    timepoint startpoint = std::get<1>(names[name]);
    std::chrono::duration<double> difference = currenttime - startpoint;
    names[name] = std::make_tuple(Status::PAUSED, std::get<1>(names[name]), std::get<2>(names[name]) + difference.count());
}

void RunTimeLogger::Log(std::string info){
    if(! LogFile.is_open()){throw std::logic_error("LogFile is not opened when logging");}
    std::cout << info << std::endl; 
    LogFile << info << std::endl;
}

void RunTimeLogger::PrintTimerStats(){
    while (is_running){
        Log("##################################################################################");

        std::chrono::duration<double> globalelapsed = clock::now() - global_start;
        std::ostringstream oss;
        oss << "Global Time Elaspsed : " << globalelapsed.count();
        Log(oss.str());
        std::ostringstream oss1;
        oss1 << "Custom Time Trackings : " << std::endl << std::endl;
        Log(oss1.str());
        for(std::map<std::string, std::tuple<int, timepoint, double>>::iterator pair = names.begin(); pair != names.end(); ++pair){
            std::ostringstream oss2;
            if(std::get<0>(pair->second) == Status::MEASURING){
                timepoint currenttime = clock::now();
                timepoint startpoint = std::get<1>(pair->second);
                std::chrono::duration<double> difference = currenttime - startpoint;
                oss2 << pair->first << " Time Elapsed : " << std::get<2>(pair->second) + difference.count()<< std::endl
                << "Percentage Time Spent with " << pair->first << " : " << 100 * (std::get<2>(pair->second) + difference.count()) / globalelapsed.count() << std::endl;
                Log(oss2.str());
            }
            else{
                oss2 << pair->first << " Time Elapsed : " << std::get<2>(pair->second) << std::endl
                << "Percentage Time Spent with " << pair->first << " : " << 100 * std::get<2>(pair->second) / globalelapsed.count() << std::endl;
                Log(oss2.str());
            }
        }
        std::ostringstream oss4;
        oss4 << std::endl;
        Log(oss4.str());
        Log("##############################################################################");
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
 }

 void RunTimeLogger::PrintTimerStatsOnce()
    {
        Log("##################################################################################");
        std::chrono::duration<double> globalelapsed = clock::now() - global_start;
        std::ostringstream oss;
        oss << "Global Time Elaspsed : " << globalelapsed.count();
        Log(oss.str());
        std::ostringstream oss1;
        oss1 << "Custom Time Trackings : " << std::endl << std::endl;
        Log(oss1.str());
        for(std::map<std::string, std::tuple<int, timepoint, double>>::iterator pair = names.begin(); pair != names.end(); ++pair){
            std::ostringstream oss2;
            if(std::get<0>(pair->second) == Status::MEASURING){
                timepoint currenttime = clock::now();
                timepoint startpoint = std::get<1>(pair->second);
                std::chrono::duration<double> difference = currenttime - startpoint;
                oss2 << pair->first << " Time Elapsed : " << std::get<2>(pair->second) + difference.count()<< std::endl
                << "Percentage Time Spent with " << pair->first << " : " << 100 * (std::get<2>(pair->second) + difference.count()) / globalelapsed.count() << std::endl;
                Log(oss2.str());
            }
            else{
                oss2 << pair->first << " Time Elapsed : " << std::get<2>(pair->second) << std::endl
                << "Percentage Time Spent with " << pair->first << " : " << 100 * std::get<2>(pair->second) / globalelapsed.count() << std::endl;
                Log(oss2.str());
            }
        }
        std::ostringstream oss4;
        oss4 << std::endl;
        Log(oss4.str());
        Log("##############################################################################");
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

RunTimeLogger::RunTimeLogger() {
    std::cout << "Name of LogFile" << std::endl;
    std::cin >> logfile_name;

    std::ostringstream path;
    path << "../log/" << logfile_name << ".txt" ;
    std::cout << "Writing Log File to : " << path.str() << std::endl;
    LogFile.open(path.str(), std::ios::app);
    is_running = true;
}

RunTimeLogger::~RunTimeLogger(){
    Log("Final Logging : ");
    PrintTimerStatsOnce();
    LogFile.close();
    is_running = false;
};
