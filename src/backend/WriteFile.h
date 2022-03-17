#include "MySystemInfo.h"

class WriteFile {
private:
	static bool write_file_binary(std::string const&, char const*, size_t const);
public:
	static void writeSysInfoToFile(MySysInfo info);
	static MySysInfo readSysInfoFromFile(std::string);
};