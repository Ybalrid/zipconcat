#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>

bool checkArgs(int argc, char** argv)
{
	(void)argv;
	if(argc < 3) return false;

	return true;
}

struct concatDescriptor
{
	const std::string exeFile;
	const std::string zipfile;
};

concatDescriptor getPaths(char** args) { return { args[1], args[2] }; }

std::string getFileExt(const std::string& filename)
{
	const auto lastDotPos = filename.find_last_of('.');
	if(lastDotPos == std::string::npos) return "";

	return filename.substr(lastDotPos + 1);
}

void concat(concatDescriptor inputs, const std::string& outputName)
{
	auto exeBinaryFile = std::ifstream(inputs.exeFile, std::ios::binary);
	if(!exeBinaryFile) throw std::runtime_error("couldn't open " + inputs.exeFile);

	auto zipBinaryFile = std::ifstream(inputs.zipfile, std::ios::binary);
	if(!zipBinaryFile) throw std::runtime_error("couldn't open " + inputs.zipfile);

	auto outputBinaryFile = std::ofstream(outputName, std::ios::binary);
	if(!outputBinaryFile) throw std::runtime_error("couldn't open for writing " + outputName);

	//Copy the bytes of the exe file
	std::copy(std::istreambuf_iterator<char>(exeBinaryFile), std::istreambuf_iterator<char>(), std::ostreambuf_iterator<char>(outputBinaryFile));

	//Copy the bytes of the zip file
	std::copy(std::istreambuf_iterator<char>(zipBinaryFile), std::istreambuf_iterator<char>(), std::ostreambuf_iterator<char>(outputBinaryFile));
}

int usage()
{
	std::cout << "USAGE:\n"
			  << "  -  zipconcat <path to exe file> <path to zip file>\n";

	return EXIT_SUCCESS;
}

int main(int argc, char** argv)
{
	if(!checkArgs(argc, argv)) return usage();
	const auto paths = getPaths(argv);

	const auto outputFileName = [&]() -> std::string {
		const auto exeExt = getFileExt(paths.exeFile);
		if(!exeExt.empty()) { return paths.exeFile.substr(0, paths.exeFile.size() - (exeExt.size())) + "output." + exeExt; }

		return paths.exeFile + ".output.exe";
	}();

	concat(paths, outputFileName);

	return EXIT_SUCCESS;
}
