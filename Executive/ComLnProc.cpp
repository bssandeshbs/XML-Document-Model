#include "ComLnProc.h"


std::string CommandLineProc::processCommandLine(int argc, char* argv[]) {
	std::string type;

	std::transform(type.begin(), type.end(), type.begin(), ::tolower);
	for (int i = 1; i<argc; ++i)
	{
		try
		{
			std::string filename = argv[i];
			return filename;

			/*std::string filename = argv[i];
			std::string substr = "txt";
			if (0 == filename.compare(filename.length() - substr.length(), substr.length(), substr)) {
				return "string";
			}
			else {
				return "file";
			}*/
		}
		catch (std::exception ex)
		{
			std::cout << "\n  " << ex.what() << "\n\n";
		}
	}
	return NULL;
}


