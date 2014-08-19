#ifndef __HRENGIN_FILESYSTEM_IModelParser_H__
#define __HRENGIN_FILESYSTEM_IModelParser_H__

#include <hrengin/core/hrenginmodels.h>
#include <hrengin/filesystem/IFileParser.h>

namespace hrengin {
namespace filesystem {

class IReadFile;

class IModelParser : public IFileParser
{
public:
	virtual bool validate(IReadFile& file);
	virtual bool parse(IReadFile& file);

};


}
}


#endif//__HRENGIN_FILESYSTEM_IModelParser_H__