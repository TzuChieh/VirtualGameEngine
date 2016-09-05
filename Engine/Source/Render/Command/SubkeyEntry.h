#pragma once

#include "Common/type.h"

namespace ve
{

typedef int32 SubkeyEntryUnderlyingType;

enum class ESubkeyEntry : SubkeyEntryUnderlyingType
{
	MATERIAL_ID = 0,
	SHADER_ID   = 1,
	PRIORITY    = 2, 

	MAX_ENTRY = 2
};

}