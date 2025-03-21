#pragma once

//#include "Scatterbrain/General/Types/TStaticArray.h" // !Important!

// template <class T>
// class TLeftRight : public TStaticArray<T, 2> {};

// #define LEFT_RIGHT_DEF(Name, Type) TArray<Type> Name;
#define LEFT_RIGHT_INIT(Name, Value) Name.Init(Value, 2);

namespace LeftRight
{
    inline bool Left = false;
    inline bool Right = true;
}