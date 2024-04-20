#pragma once
#include "Config.h"
#include "Data.hpp"
#include <iostream>
#include <string>

using namespace std;

class Logger {
public:
  template <typename... Args> static inline void Trace(Args ...args) {InternalLoggingProcess(Types::LoggingLevel::TRACE,args...);}
  template <typename... Args> static inline void Debug(Args ...args) {InternalLoggingProcess(Types::LoggingLevel::DEBUG,args...);}
  template <typename... Args> static inline void Info(Args ...args)  {InternalLoggingProcess(Types::LoggingLevel::INFO,args...);}
  template <typename... Args> static inline void Warn(Args ...args)  {InternalLoggingProcess(Types::LoggingLevel::WARN,args...);}
  template <typename... Args> static inline void Error(Args ...args) {InternalLoggingProcess(Types::LoggingLevel::ERROR,args...);}
  template <typename... Args> static inline void Fatal(Args ...args) {InternalLoggingProcess(Types::LoggingLevel::FATAL,args...);}

private:
  template <typename... Args>
  static inline void InternalLoggingProcess(Types::LoggingLevel logLevel,
                                            Args ...args) {
    switch (logLevel) {
    case Types::LoggingLevel::TRACE:
      cout << "[TRACE]";
      break;
    case Types::LoggingLevel::DEBUG:
      cout << "[DEBUG]";
      break;
    case Types::LoggingLevel::INFO:
      cout << "[INFO]";
      break;
    case Types::LoggingLevel::WARN:
      cout << "[WARN]";
      break;
    case Types::LoggingLevel::ERROR:
      cout << "[ERROR]";
      break;
    case Types::LoggingLevel::FATAL:
      cout << "[FATAL]";
      break;
    }
    cout << "[" << time_ms() << "]";
    (cout << ... << args);
    cout << endl;
  }
};