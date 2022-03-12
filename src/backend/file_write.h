#include "MySystemInfo.h"

class writefile {
private:
	bool write_file_binary(const std::string, const char*, const size_t);
public:
	static void writeSysInfoToFile(MySysInfo info);
	static MySysInfo readSysInfoFromFile(std::string);
};