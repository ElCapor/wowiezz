#ifndef SCRIPT_H
#define SCRIPT_H

#include <unity/unity.h>
#include <unity/object.h>

struct Script : public Object<Script, "Script", Unity::AssemblyFirstPass, "MoonSharp.Interpreter"> {
    
};

#endif /* SCRIPT_H */
