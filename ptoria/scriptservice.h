#ifndef SCRIPTSERVICE_H
#define SCRIPTSERVICE_H

#include <ptoria/basescript.h>

struct ScriptService : public InstanceBase,
                       public Object<ScriptService, "ScriptService", Unity::AssemblyCSharp> {
    static ScriptService* GetInstance();
    
    template <typename T>
    static void RunScript(std::string source)
    {
        BaseScript* script = BaseScript::New<T>(source);
        RunScript(script);
    }

    static void RunScript(BaseScript* script);
    static std::string ScriptSource(BaseScript* script);
};


#endif /* SCRIPTSERVICE_H */
