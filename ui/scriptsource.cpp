#include <ui/scriptsource.h>
#include <ui/premiumstyle.h>
#include <imgui.h>

// +--------------------------------------------------------+
// |                       Variables                        |
// +--------------------------------------------------------+
std::vector<ScriptSourceUI::ScriptDecompileTab> ScriptSourceUI::openTabs;

// +--------------------------------------------------------+
// |                     User Interface                     |
// +--------------------------------------------------------+
#include <ptoria/scriptservice.h>
#include <core/filesys.h>

void ScriptSourceUI::DrawTab(ScriptDecompileTab *tab)
{
    if (!tab->isEditorReady)
    {
        tab->editor = new TextEditor();
        std::string source = ScriptService::ScriptSource(tab->instance);
        tab->editor->SetText(source);
        tab->editor->SetLanguageDefinition(TextEditor::LanguageDefinitionId::Lua);
        tab->editor->SetPalette(TextEditor::PaletteId::Dark);
        tab->isEditorReady = true;
    }
    
    // Script info header with premium styling
    if (tab->instance)
    {
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 8));
        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.06f, 0.06f, 0.08f, 1.00f));
        
        ImGui::BeginChild("ScriptInfo", ImVec2(0, 0), true);
        
        // Script name with accent color
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.00f, 0.75f, 0.85f, 1.00f));
        if (PremiumStyle::FontBold)
            ImGui::PushFont(PremiumStyle::FontBold);
        ImGui::Text("%s", tab->instance->Name()->ToString().c_str());
        if (PremiumStyle::FontBold)
            ImGui::PopFont();
        ImGui::PopStyleColor();
        
        ImGui::SameLine();
        ImGui::TextDisabled("(Decompiled Script)");
        
        ImGui::Spacing();
        
        // Status indicators
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(16, 4));
        
        // Running status
        bool isRunning = tab->instance->Running();
        ImGui::TextColored(ImVec4(0.70f, 0.70f, 0.75f, 1.00f), "Running:");
        ImGui::SameLine();
        if (isRunning)
        {
            ImGui::TextColored(ImVec4(0.20f, 0.85f, 0.40f, 1.00f), "Yes");
        }
        else
        {
            ImGui::TextColored(ImVec4(0.85f, 0.40f, 0.40f, 1.00f), "No");
        }
        
        // Requested Run status
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.70f, 0.70f, 0.75f, 1.00f), "Requested Run:");
        ImGui::SameLine();
        ImGui::TextColored(tab->instance->RequestedRun() ? ImVec4(0.20f, 0.85f, 0.40f, 1.00f) : ImVec4(0.85f, 0.40f, 0.40f, 1.00f), 
            tab->instance->RequestedRun() ? "Yes" : "No");
        
        ImGui::PopStyleVar();
        
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
        
        // Toolbar
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8, 6));
        
        // File operations
        if (ImGui::Button("Open..."))
        {
            auto filters = std::vector<filesys::FileSelectFilters>{
                {"Lua Scripts", "lua"},
                {"Text Files", "txt"},
            };
            auto result = filesys::OpenDialog(filters);
            if (result)
            {
                std::string scriptContent = filesys::ReadFileAsString(*result).value_or("");
                tab->editor->SetText(scriptContent);
            }
        }
        
        ImGui::SameLine();
        
        if (ImGui::Button("Save..."))
        {
            auto filters = std::vector<filesys::FileSelectFilters>{
                {"Lua Scripts", "lua"},
                {"Text Files", "txt"},
            };
            auto result = filesys::SaveDialog(filters);
            if (result)
            {
                std::string scriptContent = tab->editor->GetText();
                filesys::WriteStringToFile(*result, scriptContent);
            }
        }
        
        ImGui::SameLine();
        
        // Warning indicator
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.95f, 0.78f, 0.20f, 1.00f));
        ImGui::Text("[!] Experimental");
        ImGui::PopStyleColor();
        
        if (ImGui::IsItemHovered())
        {
            ImGui::SetTooltip("Can't save script to game yet - feature in development");
        }
        
        ImGui::PopStyleVar();
        
        ImGui::Spacing();
        
        // Save to game button with warning styling
        if (PremiumStyle::StyledButton("Save Changes To Game", false, ImVec2(160, 0)))
        {
            if (tab->instance)
            {
                if (!tab->isEditorReady)
                {
                    std::cout << "Editor not ready, cannot save changes" << std::endl;
                }
                else
                {
                    if (tab->instance->Running())
                    {
                        tab->instance->SetRunning(false);
                    }

                    std::string updatedSource = tab->editor->GetText();
                    tab->instance->SetSource(UnityString::New(updatedSource));
                }
            }
        }
        
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
        
        // Editor with premium styling
        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 6.0f);
        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.04f, 0.04f, 0.06f, 1.00f));
        
        tab->editor->Render("##ScriptEditor", false, ImVec2(0, 0), true);
        
        ImGui::PopStyleColor();
        ImGui::PopStyleVar();
        
        ImGui::EndChild();
        
        ImGui::PopStyleColor();
        ImGui::PopStyleVar();
    }
}

bool ScriptSourceUI::IsTabAlreadyOpen(BaseScript *instance)
{
    for (const auto &tab : openTabs)
    {
        if (tab.instance == instance)
            return true;
    }
    return false;
}

void ScriptSourceUI::OpenNewScriptDecompileTab(BaseScript *instance)
{
    openTabs.push_back({instance});
}
