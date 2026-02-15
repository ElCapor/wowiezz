#include <ui/executor.h>
#include <core/filesys.h>
#include <ptoria/scriptservice.h>
#include <ptoria/scriptinstance.h>
// +--------------------------------------------------------+
// |                       Variables                        |
// +--------------------------------------------------------+
TextEditor* ExecutorUI::scriptEditor;


// +--------------------------------------------------------+
// |                     User Interface                     |
// +--------------------------------------------------------+

void ExecutorUI::Init()
{
    static bool initialized = false;
    if (!initialized)
    {
        scriptEditor = new TextEditor();
        scriptEditor->SetLanguageDefinition(TextEditor::LanguageDefinitionId::Lua);
        initialized = true;
    }
}

void ExecutorUI::DrawTab()
{
    Init();
    ImGui::Text("Script Executor");

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open Script..."))
            {
                auto filters = std::vector<filesys::FileSelectFilters>{
                    {"Lua Scripts", "lua"},
                    {"Text Files", "txt"},
                };
                auto result = filesys::OpenDialog(filters);
                if (result)
                {
                    std::string scriptContent = filesys::ReadFileAsString(*result).value_or("");
                    scriptEditor->SetText(scriptContent);
                }
            }
            if (ImGui::MenuItem("Save Script..."))
            {
                auto filters = std::vector<filesys::FileSelectFilters>{
                    {"Lua Scripts", "lua"},
                    {"Text Files", "txt"},
                };
                auto result = filesys::SaveDialog(filters);
                if (result)
                {
                    std::string scriptContent = scriptEditor->GetText();
                    filesys::WriteStringToFile(*result, scriptContent);
                }
            }

            ImGui::EndMenu();
        }

        if (ImGui::MenuItem("Run"))
        {
            std::string script = scriptEditor->GetText();
            if (!script.empty())
            {
                ScriptService::RunScript<ScriptInstance>(script);
            }
        }
        ImGui::EndMenuBar();
    }
    scriptEditor->Render("Lua Script Executor");
}