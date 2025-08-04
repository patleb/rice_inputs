#pragma once

class Logger {
  public:

  enum LEVEL { TRACE, DEBUG, INFO, WARNING, ERROR };

  constexpr static std::string LEVELS[5] = { "TRACE", "DEBUG", "INFO", "WARNING", "ERROR" };
  inline static size_t marker_i = 0;
  inline static bool new_run = true;

  explicit Logger() { file.open("/home/patleb/code/web_tools/log/rice.log", std::ofstream::out | std::ofstream::app); }
  Logger(const Logger &) = delete;
  Logger(Logger &&) = delete;
  Logger & operator=(const Logger &) = delete;
  Logger & operator=(Logger &&) = delete;
  ~Logger() {} // no file.close, since global/static variables' destructors aren't called in DLL unload/exit

  // Parameter Pack: https://www.scs.stanford.edu/~dm/blog/param-pack.html
  template < class... Args >
  void log(const Args & ...messages, const LEVEL level) {
    if (new_run) { new_run = false; file << std::endl; }
    file << "[" << C::timestamp() << "][" << LEVELS[level] << "]: ";
    (file << ... << std::format("{}", messages));
    file << std::endl;
  }

  private:

  std::ofstream file;
};

inline auto logger = Logger();

template < class... Args >
inline void log_trace(const Args & ...messages) {
}

template < class... Args >
inline void log_debug(const Args & ...messages) {
}

template < class... Args >
inline void log_info(const Args & ...messages) {
}

template < class... Args >
inline void log_warning(const Args & ...messages) {
  logger.log< Args... >(messages..., Logger::LEVEL::WARNING);
}

template < class... Args >
inline void log_error(const Args & ...messages) {
  logger.log< Args... >(messages..., Logger::LEVEL::ERROR);
}

inline void log_mark() {
  log_error("mark: ", Logger::marker_i++);
}

template < class T >
inline void log_vector(std::string_view prefix, const T vector[], size_t count) {
  std::stringstream message;
  message << prefix;
  for (size_t i = 0; i < count; ++i) {
    message << " (" << std::to_string(i) << ") " << std::to_string(vector[i]);
  }
  log_error(message.str());
}

template < class T >
inline void log_vector(std::string_view prefix, const std::vector< T > & vector) {
  log_vector< T >(vector.data(), vector.size(), prefix);
}
