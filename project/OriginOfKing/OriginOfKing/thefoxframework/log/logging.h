#ifndef _THEFOX_LOG_LOGMESSAGE_H_
#define _THEFOX_LOG_LOGMESSAGE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <functional>
#include <base/common.h>

namespace thefox {

enum LogLevel {
	LOGLEVEL_TRACE,
	LOGLEVEL_DEBUG,
	LOGLEVEL_INFO,
	LOGLEVEL_WARN,
	LOGLEVEL_ERROR,
	LOGLEVEL_FATAL,
	LOGLEVEL_NUM_LOG_LEVELS
};

namespace detail
{

// 从路径中得到文件名
inline const char *getFileNameFromPath(const char *pathName)
{
	const char* slash = strrchr(pathName, '/');
	if (slash) {
		return slash + 1;
	} else {
		const char *bslash = strrchr(pathName, '\\');
		if (bslash) {
			return bslash + 1;
		}
	}
	return pathName;
}

class LogFinisher;

class LogMessage 
{
public:
	LogMessage(LogLevel level, const char *filename, int line);
	~LogMessage();

	LogMessage &operator<<(const string &value);
	LogMessage &operator<<(const char *value);
	LogMessage &operator<<(char value);
	LogMessage &operator<<(int value);
	LogMessage &operator<<(unsigned int value);
	LogMessage &operator<<(long value);
	LogMessage &operator<<(unsigned long value);
	LogMessage &operator<<(long long value);
	LogMessage &operator<<(unsigned long long value);
	LogMessage &operator<<(double value);
	LogMessage &operator<<(const void *p);

private:
	friend class LogFinisher;
	friend class LogTraceFunction;
	void Finish();

	LogLevel _level;
	string _message;
};

class LogFinisher
{
public:
	void operator=(LogMessage &other);
};

// 跟踪函数的开头和结束, 放在函数的第一行
class LogTraceFunction {
public:
	LogTraceFunction(const char *func, const char *file, int line);
	~LogTraceFunction();
	
	void operator=(LogMessage &other);
private:
	const char *_func;
	const char *_file;
	int _line;
};

} // namespace detail

// 写日志函数
typedef void (*ThefoxLogHandler)(const string &message);

void thefoxSetLogHandler(ThefoxLogHandler newFunc);

void setLogLevel(LogLevel level);
LogLevel logLevel();

#undef ERROR

#define THEFOX_LOG(LEVEL) if (thefox::logLevel() <= thefox::LOGLEVEL_##LEVEL) \
	thefox::detail::LogFinisher() =                                           \
		thefox::detail::LogMessage(                                           \
			thefox::LOGLEVEL_##LEVEL, thefox::detail::getFileNameFromPath(__FILE__), __LINE__)
#define THEFOX_LOG_IF(LEVEL, CONDITION) \
	!(CONDITION) ? (void)0 : THEFOX_LOG(LEVEL)

#define THEFOX_CHECK(EXPRESSION) \
  THEFOX_LOG_IF(FATAL, !(EXPRESSION)) << "CHECK failed: " #EXPRESSION ": "
#define THEFOX_CHECK_EQ(A, B) THEFOX_CHECK((A) == (B))
#define THEFOX_CHECK_NE(A, B) THEFOX_CHECK((A) != (B))
#define THEFOX_CHECK_LT(A, B) THEFOX_CHECK((A) <  (B))
#define THEFOX_CHECK_LE(A, B) THEFOX_CHECK((A) <= (B))
#define THEFOX_CHECK_GT(A, B) THEFOX_CHECK((A) >  (B))
#define THEFOX_CHECK_GE(A, B) THEFOX_CHECK((A) >= (B))

namespace detail 
{
template<typename T>
T* checkNotNull(const char *name, T* val)
{
	if (val == NULL)
		THEFOX_LOG(FATAL) << name;
	return val;
}

}  // namespace detail

#define THEFOX_CHECK_NOTNULL(A) \
  thefox::detail::checkNotNull("'" #A "' must not be NULL", (A))

#define THEFOX_TRACE_FUNCTION  \
	thefox::detail::LogTraceFunction LogTraceFunction(__FUNCTION__, __FILE__, __LINE__); \
	if (thefox::logLevel() <= thefox::LOGLEVEL_TRACE)	                                 \
		LogTraceFunction = thefox::detail::LogMessage(LOGLEVEL_TRACE,                    \
			thefox::detail::getFileNameFromPath(__FILE__), __LINE__)                     \
			<< __FUNCTION__ << "() begin "
} // namespace thefox

#endif // _THEFOX_LOG_LOGMESSAGE_H_
