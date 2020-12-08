#ifndef __LOGGER_H__
#define __LOGGER_H__

typedef enum
{
	LOG_DEBUG,
	LOG_INFO,
	LOG_WARNING,
	LOG_ERROR,
	LOG_FATAL
} LOG_LEVEL;

void log_init();
void log_close();

void log_print(LOG_LEVEL level, const char* msg, ...);
#define log_debug(msg, ...) log_print(LOG_DEBUG, msg, ##__VA_ARGS__)
#define log_info(msg, ...) log_print(LOG_INFO, msg, ##__VA_ARGS__)
#define log_warn(msg, ...) log_print(LOG_WARNING, msg, ##__VA_ARGS__)
#define log_error(msg, ...) log_print(LOG_ERROR, msg, ##__VA_ARGS__)
#define log_fatal(msg, ...) log_print(LOG_FATAL, msg, ##__VA_ARGS__)

#endif // !__LOGGER_H__
