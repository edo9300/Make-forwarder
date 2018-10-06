#include <iostream>
#include <fstream>
#ifdef _WIN32
#include <direct.h>
#define GetWorkingDir _getcwd(NULL, 0)
#else
#include <unistd.h>
#define GetWorkingDir  getcwd(NULL, 0)
#endif
#include <vector>
#include "headers.h"
#include "sha1.h"
#include "utils.h"

void ReplaceBanner(const std::string& target, const std::string& input, const std::string& output);
void MakeTmd(const std::string& target, const std::string& destination = "");

std::string string_to_hex(const std::string& input) {
	static const char* const lut = "0123456789ABCDEF";
	size_t len = input.length();

	std::string output;
	output.reserve(2 * len);
	for(size_t i = 0; i < len; ++i) {
		const unsigned char c = input[i];
		output.push_back(lut[c >> 4]);
		output.push_back(lut[c & 15]);
	}
	return output;
}

int main(int argc, char **argv) {
	if(argc < 2)
		return 1;
	std::string exepath(argv[0]);
	size_t folder = exepath.find_last_of(FOLDER_SEPARATOR);
	exepath = exepath.substr(0, folder);
	std::string file(argv[1]);
	std::string workingdir(GetWorkingDir);

	std::ifstream infile(file, std::ifstream::binary);
	infile.seekg(0xc);
	std::string gameid;
	gameid.resize(4);
	infile.read(&gameid[0], 4);
	infile.close();

	std::string gameidhex(string_to_hex(gameid));

	ReplaceBanner(exepath + FOLDER_SEPARATOR + "template.nds", file, exepath + FOLDER_SEPARATOR + "banner.nds");

	MakeTmd(exepath + FOLDER_SEPARATOR + "banner.nds", exepath + FOLDER_SEPARATOR + "title.tmd");
	
	std::fstream infile2(workingdir + FOLDER_SEPARATOR + "banner.nds", std::fstream::binary | std::fstream::out | std::fstream::in);
	infile2.seekg(0, infile2.beg);

	std::string str((std::istreambuf_iterator<char>(infile2)),
		std::istreambuf_iterator<char>());
	std::size_t found = str.find("sd:/kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk") + 4;
	infile2.seekg(found, infile2.beg);
	std::string path("title/00030004/" + gameidhex + "/data/");
	infile2.write(&path[0], path.size());
	infile2.put('\0');
	infile2.close();
	if(CreatePath("title/00030004/" + gameidhex + "/data", workingdir) && CreatePath("title/00030004/" + gameidhex + "/content", workingdir)) {
		std::string folderpath("title" + std::string(FOLDER_SEPARATOR) + "00030004" + FOLDER_SEPARATOR + gameidhex + FOLDER_SEPARATOR + "content");
		Movefile(exepath + FOLDER_SEPARATOR + "banner.nds", folderpath + FOLDER_SEPARATOR + "00000000.app");
		Movefile(exepath + FOLDER_SEPARATOR + "title.tmd", folderpath + FOLDER_SEPARATOR + "title.tmd");
	}
	
	return 0;
}

