#pragma once

#define TWO_LIMBS_DEF(Name, Type) Type Name[2];
#define TWO_LIMBS_INIT(Name, Type) Name[0]=Type(); Name[1]=Type();
#define TWO_LIMBS_VALUE(Name, Value1, Value2) Name[0]=Value1; Name[1]=Value2;

namespace TwoLimbs
{
    inline bool Left = false;
    inline bool Right = true;
}