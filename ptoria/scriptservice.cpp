#include <ptoria/scriptservice.h>
#include <ptoria/scriptinstance.h>


ScriptService* ScriptService::GetInstance() {
    static UnityMethod* method = nullptr;
    if (!method) method = Unity::GetMethod<"get_Instance">(StaticClass<ScriptService>());
    nasec::Assert(method != nullptr, "Failed to get ScriptService::get_Instance method");
    return method->Invoke<ScriptService*>(nullptr);
}

void ScriptService::RunScript(BaseScript* script) {
    Unity::GetMethod<"RunScript">(StaticClass<ScriptService>())->Invoke<void, void*, BaseScript*>(GetInstance(), script);
}

std::string ScriptService::ScriptSource(BaseScript* script) {
    nasec::Assert(script != nullptr, "Script was nullptr");
    return script->Source()->ToString();
}