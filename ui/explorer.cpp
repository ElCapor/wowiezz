#include <ui/explorer.h>
#include <ui/premiumstyle.h>
#include <ptoria/game.h>
#include <imgui.h>
#include <ui/scriptsource.h>

// +--------------------------------------------------------+
// |                       Variables                        |
// +--------------------------------------------------------+
Instance *ExplorerUI::selectedInstance = nullptr;

// +--------------------------------------------------------+
// |                       Functions                        |
// +--------------------------------------------------------+
void RenderInstanceTree(Instance *instance);

// +--------------------------------------------------------+
// |                   Explorer Interface                   |
// +--------------------------------------------------------+

void ExplorerUI::Init()
{
}

void ExplorerUI::DrawTab()
{
    static Game *gameInstance = Game::GetSingleton();
    if (!gameInstance)
        return;

    float availableHeight = ImGui::GetContentRegionAvail().y;

    // Tree Explorer section with premium styling
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 6.0f);
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.05f, 0.05f, 0.07f, 1.00f));
    
    ImGui::BeginChild("TreeRegion", ImVec2(0, availableHeight * 0.55f), true);
    
    // Section header
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.00f, 0.75f, 0.85f, 1.00f));
    if (PremiumStyle::FontBold)
        ImGui::PushFont(PremiumStyle::FontBold);
    ImGui::Text("Instance Explorer");
    if (PremiumStyle::FontBold)
        ImGui::PopFont();
    ImGui::PopStyleColor();
    
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
    
    RenderInstanceTree((Instance *)gameInstance);
    ImGui::EndChild();
    
    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
    
    ImGui::Spacing();

    // Properties section with premium styling
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 6.0f);
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.05f, 0.05f, 0.07f, 1.00f));
    
    ImGui::BeginChild("PropertiesRegion", ImVec2(0, 0), true);
    
    if (selectedInstance)
    {
        // Properties header with gold accent
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.95f, 0.78f, 0.20f, 1.00f));
        if (PremiumStyle::FontBold)
            ImGui::PushFont(PremiumStyle::FontBold);
        ImGui::Text("Properties: %s", selectedInstance->Name()->ToString().c_str());
        if (PremiumStyle::FontBold)
            ImGui::PopFont();
        ImGui::PopStyleColor();
        
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        // Premium table styling
        ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(10, 6));
        if (ImGui::BeginTable("PropertiesTable", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable | ImGuiTableFlags_SizingStretchProp))
        {
            ImGui::TableSetupColumn("Property", ImGuiTableColumnFlags_WidthFixed, 120.0f);
            ImGui::TableSetupColumn("Value", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableHeadersRow();

            // Name
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::TextColored(ImVec4(0.70f, 0.70f, 0.75f, 1.00f), "Name");
            ImGui::TableSetColumnIndex(1);
            std::string nameStr = selectedInstance->Name()->ToString();
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.94f, 0.95f, 0.96f, 1.00f));
            if (ImGui::Selectable(nameStr.c_str()))
                ImGui::SetClipboardText(nameStr.c_str());
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("Click to copy: %s", nameStr.c_str());
            ImGui::PopStyleColor();

            // Type
            auto selectedInstanceObject = Unity::CastToUnityObject(selectedInstance);
            auto type = selectedInstanceObject->GetType();
            if (type)
            {
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::TextColored(ImVec4(0.70f, 0.70f, 0.75f, 1.00f), "Class");
                ImGui::TableSetColumnIndex(1);
                std::string classStr = type->GetFullNameOrDefault()->ToString();
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.00f, 0.75f, 0.85f, 1.00f));
                if (ImGui::Selectable(classStr.c_str()))
                    ImGui::SetClipboardText(classStr.c_str());
                if (ImGui::IsItemHovered())
                    ImGui::SetTooltip("Click to copy: %s", classStr.c_str());
                ImGui::PopStyleColor();

                // Script Source button for script types
                if (type->GetFullNameOrDefault()->ToString() == "Polytoria.Datamodel.LocalScript" || 
                    type->GetFullNameOrDefault()->ToString() == "Polytoria.Datamodel.Script" || 
                    type->GetFullNameOrDefault()->ToString() == "Polytoria.Datamodel.ModuleScript" || 
                    type->GetFullNameOrDefault()->ToString() == "Polytoria.Datamodel.ScriptInstance")
                {
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0);
                    ImGui::TextColored(ImVec4(0.70f, 0.70f, 0.75f, 1.00f), "Script Source");
                    ImGui::TableSetColumnIndex(1);
                    if (PremiumStyle::StyledButton("View Source", true, ImVec2(100, 0)))
                    {
                        if (!ScriptSourceUI::IsTabAlreadyOpen(Unity::Cast<BaseScript>(selectedInstance)))
                        {
                            BaseScript *scriptInstance = Unity::Cast<BaseScript>(selectedInstance);
                            ScriptSourceUI::OpenNewScriptDecompileTab(scriptInstance);
                        }
                    }
                }
            }

            // Memory Address
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::TextColored(ImVec4(0.70f, 0.70f, 0.75f, 1.00f), "Address");
            ImGui::TableSetColumnIndex(1);
            char addrBuf[32];
            snprintf(addrBuf, sizeof(addrBuf), "0x%p", selectedInstance);
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.60f, 0.80f, 0.60f, 1.00f));
            if (ImGui::Selectable(addrBuf))
                ImGui::SetClipboardText(addrBuf);
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("Click to copy: %s", addrBuf);
            ImGui::PopStyleColor();

            // Full Name
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::TextColored(ImVec4(0.70f, 0.70f, 0.75f, 1.00f), "Full Name");
            ImGui::TableSetColumnIndex(1);
            std::string fullNameStr = selectedInstance->FullName()->ToString();
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.94f, 0.95f, 0.96f, 1.00f));
            if (ImGui::Selectable(fullNameStr.c_str()))
                ImGui::SetClipboardText(fullNameStr.c_str());
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("Click to copy: %s", fullNameStr.c_str());
            ImGui::PopStyleColor();

            ImGui::EndTable();
        }
        ImGui::PopStyleVar();
    }
    else
    {
        // Empty state with centered text
        ImVec2 textSize = ImGui::CalcTextSize("Select an instance to see its properties");
        ImVec2 regionSize = ImGui::GetContentRegionAvail();
        ImGui::SetCursorPosX((regionSize.x - textSize.x) / 2);
        ImGui::SetCursorPosY((regionSize.y - textSize.y) / 2);
        ImGui::TextDisabled("Select an instance to see its properties");
    }
    ImGui::EndChild();
    
    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
}

// +--------------------------------------------------------+
// |                        Helpers                         |
// +--------------------------------------------------------+
void RenderInstanceTree(Instance *instance)
{
    if (!instance)
        return;

    // Premium tree node styling
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_FramePadding;

    auto children = instance->Children();
    bool hasChildren = children && children->max_length > 0;

    if (!hasChildren)
        flags |= ImGuiTreeNodeFlags_Leaf;

    // Highlight selected node
    bool isSelected = (ExplorerUI::selectedInstance == instance);
    if (isSelected)
    {
        ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.00f, 0.75f, 0.85f, 0.40f));
        ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.00f, 0.75f, 0.85f, 0.50f));
        ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.00f, 0.75f, 0.85f, 0.60f));
    }

    bool opened = ImGui::TreeNodeEx(instance, flags, "%s", instance->Name()->ToString().c_str());

    if (isSelected)
    {
        ImGui::PopStyleColor(3);
    }

    if (ImGui::IsItemClicked())
    {
        ExplorerUI::selectedInstance = instance;
    }

    if (opened)
    {
        if (hasChildren)
        {
            ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, 20.0f);
            for (auto child : children->ToVector())
            {
                RenderInstanceTree((Instance *)child);
            }
            ImGui::PopStyleVar();
        }
        ImGui::TreePop();
    }
}