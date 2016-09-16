#pragma once

#include "Utility/TStableIndexDenseArray.h"

namespace ve
{

template<typename ComponentType>
using TComponentStorage = TStableIndexDenseArray<ComponentType>;

}// end namespace ve