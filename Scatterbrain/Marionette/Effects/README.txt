=========================== Concepts ===========================

Effect - it can be active and inactive. It can also tick independently synchronously measuring the time of its work,
or it can be as a status and hang on an asynchronous timer.
 
=========================== Naming ===========================

All effects are classes with naming rule below.

Standard F prefix by Unreal.
-----------------------------------
EFCT - Effect
-----------------------------------
"_" symbol.
-----------------------------------
Name of Effect itself. Example: "Burning"

=========================== Name Examples ===========================

Class file name example: EFCT_Burning.h
Class name example: FEFCT_Burning

=========================== How to add new effect ===========================

Implement it in the ".Library" directory, creating its own directory for it and inheriting it 
either from the ticking class (Effect.h) or from the status effect class (EffectStatus.h). 
Add it to the "EffectsList.h" file according to the instructions inside.