#include <ui/about.h>
#include <string>
#include <vector>

// +--------------------------------------------------------+
// |                       Variables                        |
// +--------------------------------------------------------+
struct Contributor
{
    std::string name;
    std::string link;
    std::string what;
};

std::vector <Contributor> contributors = {
    // in order of contribution
    {"0x108", "https://github.com/NtReadVirtualMemory", "Fantastic friend + Helped rewriting parts of the v1/v2"},
    {"Nasec", "https://github.com/NASCeria", "Smart boi => Custom Functions + Networking"},
    {"Eli","https://github.com/geringverdien", "Custom functions"},
    {"Ficello", "https://github.com/1337Skid", "Early findings and first scripts"}
};

// +--------------------------------------------------------+
// |                       Functions                        |
// +--------------------------------------------------------+
#include <imgui.h>
#include <core/filesys.h>
#include <ui/premiumstyle.h>
void AboutUI::Init()
{
}

void AboutUI::DrawTab()
{
    ImGui::Text("PolyHack - Polytoria Mod Menu");
    ImGui::Separator();
    ImGui::Text("Version: 3.0");
    ImGui::Text("Author: ElCapor");
    ImGui::Spacing();
    ImGui::TextWrapped("PolyHack is a mod menu for Polytoria, providing various features and enhancements to the game. Use at your own risk.");
    ImGui::Spacing();
    if (ImGui::Button("GitHub Repository"))
    {
        filesys::OpenUrlInBrowser("https://github.com/ElCapor/PolytoriaExecutor");
    }
    ImGui::SameLine();
    if (ImGui::Button("Discord Server"))
    {
        filesys::OpenUrlInBrowser("https://discord.gg/NrXZmyPRvh");
    }
    ImGui::SameLine();
    if (ImGui::Button("Youtube"))
    {
        filesys::OpenUrlInBrowser("https://www.youtube.com/@SkipSped");
    }
    ImGui::Separator();
    ImGui::Text("Contributors:");
    for (const auto& contributor : contributors)
    {
        ImGui::Text("%s - %s", contributor.name.c_str(), contributor.what.c_str());
        if (ImGui::Button(("View " + contributor.name + "'s Profile").c_str()))
        {
            filesys::OpenUrlInBrowser(contributor.link);
        }

        ImGui::SameLine();
        ImGui::Dummy(ImVec2(10, 0)); // Add spacing between buttons
    }
    ImGui::Separator();
    ImGui::TextWrapped("Disclaimer: PolyHack is intended for educational and testing purposes only. Use responsibly and respect the game's terms of service.");

}
