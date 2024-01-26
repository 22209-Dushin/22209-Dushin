#include <string>
#include <vector>
#include <map>
#include "factory.h"
#include "converter.h"

void Factory::addConvectorCreator(convectorCreator* convCreator) { 
	factoryMap.insert(std::make_pair(convCreator->convName(), convCreator));
}

std::shared_ptr<converter> Factory::create(const std::string& converterID,
    const std::vector<int>& iargs,
    const std::vector<std::string>& streams,
    const std::vector<size_t>& streamIndexes
) {
	return factoryMap[converterID]->parse(iargs, streams, streamIndexes);
}

