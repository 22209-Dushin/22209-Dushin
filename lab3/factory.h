#pragma once
#include <string>
#include <map>
#include <vector>
#include "converter.h"

class Factory {
public:
	std::shared_ptr<converter> create(const std::string& converterID,
    const std::vector<int>& iargs,
    const std::vector<std::string>& streams,
    const std::vector<size_t>& streamIndexes
);
	void addConvectorCreator(convectorCreator* convCreator);
private:
	std::map<std::string, convectorCreator*> factoryMap;
};

