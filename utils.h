#ifndef UTILS_H
#define UTILS_H
#include <fstream>
#include <vector>

#ifdef _WIN32
#define FOLDER_SEPARATOR "\\"
#undef UNICODE
#include <windows.h>
#else
#define FOLDER_SEPARATOR "/"
#include <errno.h>
#include <sys/stat.h>
#endif	// _WIN32

bool Makedirectory(const std::string& path) {
#ifdef _WIN32
	return CreateDirectory(path.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError();
#else
	return !mkdir((const char *)path.c_str(), 0777) || errno == EEXIST;
#endif
}
bool Movefile(const std::string& source, const std::string& destination) {
	std::ifstream  src(source, std::ios::binary);
	if(!src.is_open())
		return false;
	std::ofstream  dst(destination, std::ios::binary);
	if(!dst.is_open())
		return false;
	dst << src.rdbuf();
	src.close();
	remove(source.c_str());
	return true;
}
bool CreatePath(const std::string& path, const std::string& workingdir = "") {
	std::vector<std::string> folders;
	std::string temp;
	for(int i = 0; i < (int)path.size(); i++) {
		if(path[i] == '/') {
			folders.push_back(temp);
			temp.clear();
		} else
			temp += path[i];
	}
	if(!temp.empty())
		folders.push_back(temp);
	temp.clear();
	for(auto folder : folders) {
		if(temp.empty() && !workingdir.empty())
			temp = workingdir + FOLDER_SEPARATOR + folder;
		else
			temp += FOLDER_SEPARATOR + folder;
		if(!Makedirectory(temp))
			return false;
	}
	return true;
}

#endif