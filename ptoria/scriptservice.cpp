#include <ptoria/scriptservice.h>
#include <ptoria/scriptinstance.h>
#include <hooking/hookmanager.h>
#include <moonsharp/cinterface.h>

ScriptService *ScriptService::GetInstance()
{
    static UnityMethod *method = nullptr;
    if (!method)
        method = Unity::GetMethod<"get_Instance">(StaticClass<ScriptService>());
    nasec::Assert(method != nullptr, "Failed to get ScriptService::get_Instance method");
    return method->Invoke<ScriptService *>();
}

void ScriptService::RunScript(BaseScript *script)
{
    Unity::GetMethod<"RunScript">(StaticClass<ScriptService>())->Invoke<void, void *, BaseScript *>(GetInstance(), script);
}

std::string ScriptService::ScriptSource(BaseScript *script)
{
    nasec::Assert(script != nullptr, "Script was nullptr");
    return script->Source()->ToString();
}


void InstallEnvironnement(Script *script);
DynValue *ScriptService::ExecuteScriptInstanceHook(ScriptService *self, Script *script, BaseScript *instance)
{
    nasec::Assert(self != nullptr, "ScriptService instance was nullptr");
    nasec::Assert(script != nullptr, "Script was nullptr");
    nasec::Assert(instance != nullptr, "BaseScript instance was nullptr");

    /*
    Inject our custom lua environnement
    */
    InstallEnvironnement(script);

    return HookManager::Call(ScriptService::ExecuteScriptInstanceHook, self, script, instance);
}


DynValue* poop(void*, ScriptExecutionContext* context, CallbackArguments* args) {
    return DynValue::FromString("Hello from C++!");
}

void InstallEnvironnement(Script *script)
{
    RegisterCallback(script->Globals(), "poop", poop);
}

void ScriptService::InstallHooks()
{
    HookManager::Install(Unity::GetMethod<"ExecuteScriptInstance">(StaticClass<ScriptService>())->Cast<DynValue*, ScriptService*, Script*, BaseScript*>(), ExecuteScriptInstanceHook);
}