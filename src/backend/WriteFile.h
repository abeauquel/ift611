#include "MySystemInfo.h"

class WriteFile {
private:
public:
	static bool write_file_binary(std::string const&, char const*, size_t const);
	static void writeSysInfoToFile(MySysInfo info);
	static MySysInfo readSysInfoFromFile(std::string);
};