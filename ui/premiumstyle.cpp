#include <ui/premiumstyle.h>
#include <imgui.h>
#include <imgui_internal.h>

namespace PremiumStyle
{
    // Font pointers
    ImFont* FontRegular = nullptr;
    ImFont* FontBold = nullptr;
    
    // Internal font config
    static ImFontConfig fontConfig;
    
    void Initialize()
    {
        // Set up font configuration for better rendering
        fontConfig.OversampleH = 2;
        fontConfig.OversampleV = 1;
        fontConfig.PixelSnapH = true;
        //fontConfig.Ras = 0x01; // Enable hinting
    }
    
    void LoadFonts()
    {
        ImGuiIO& io = ImGui::GetIO();
        
        // Load SNPro Regular as the main font
        FontRegular = io.Fonts->AddFontFromFileTTF("fonts/SNPro-Regular.ttf", 16.0f, &fontConfig);
        
        // Load SNPro Bold for headers and emphasis
        FontBold = io.Fonts->AddFontFromFileTTF("fonts/SNPro-Bold.ttf", 16.0f, &fontConfig);
        
        // Set default font
        if (FontRegular)
            io.FontDefault = FontRegular;
    }
    
    void ApplyStyle()
    {
        ImGuiStyle& style = ImGui::GetStyle();
        ImVec4* colors = style.Colors;
        
        // ========================================
        // STYLE SHAPING - Premium Modern Look
        // ========================================
        
        // Rounding - modern, friendly but professional
        style.FrameRounding = 6.0f;
        style.WindowRounding = 8.0f;
        style.GrabRounding = 6.0f;
        style.ScrollbarRounding = 6.0f;
        style.PopupRounding = 6.0f;
        style.ChildRounding = 6.0f;
        style.TabRounding = 6.0f;
        
        // Padding & Spacing - generous for easy interaction
        style.FramePadding = ImVec2(10.0f, 6.0f);
        style.ItemSpacing = ImVec2(10.0f, 6.0f);
        style.ItemInnerSpacing = ImVec2(6.0f, 4.0f);
        style.WindowPadding = ImVec2(12.0f, 12.0f);
        style.CellPadding = ImVec2(8.0f, 4.0f);
        
        // Borders
        style.WindowBorderSize = 1.0f;
        style.FrameBorderSize = 0.0f;  // Clean look
        style.PopupBorderSize = 1.0f;
        style.TabBorderSize = 0.0f;
        
        // Sizing
        style.WindowMinSize = ImVec2(200.0f, 100.0f);
        style.GrabMinSize = 12.0f;
        style.ScrollbarSize = 16.0f;
        style.IndentSpacing = 24.0f;
        style.ColumnsMinSpacing = 12.0f;
        
        // Anti-aliasing - always enabled for professional look
        style.AntiAliasedLines = true;
        style.AntiAliasedFill = true;
        
        // Alpha
        style.Alpha = 1.0f;
        
        // ========================================
        // COLOR PALETTE - Premium Dark Theme
        // ========================================
        
        // Background colors - sophisticated dark with subtle blue undertones
        colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.08f, 1.00f);
        colors[ImGuiCol_ChildBg] = ImVec4(0.05f, 0.05f, 0.07f, 1.00f);
        colors[ImGuiCol_PopupBg] = ImVec4(0.10f, 0.10f, 0.14f, 0.98f);
        colors[ImGuiCol_MenuBarBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
        
        // Text - high contrast, crisp
        colors[ImGuiCol_Text] = ImVec4(0.94f, 0.95f, 0.96f, 1.00f);
        colors[ImGuiCol_TextDisabled] = ImVec4(0.45f, 0.47f, 0.50f, 1.00f);
        colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.75f, 0.85f, 0.35f);
        
        // Borders - very subtle
        colors[ImGuiCol_Border] = ImVec4(0.18f, 0.18f, 0.24f, 0.50f);
        colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        
        // Separator
        colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.20f, 0.26f, 0.50f);
        colors[ImGuiCol_SeparatorHovered] = ImVec4(0.15f, 0.85f, 0.95f, 0.80f);
        colors[ImGuiCol_SeparatorActive] = ImVec4(0.00f, 0.60f, 0.70f, 1.00f);
        
        // Frame (Input fields, buttons base)
        colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.10f, 0.14f, 1.00f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.14f, 0.14f, 0.20f, 1.00f);
        colors[ImGuiCol_FrameBgActive] = ImVec4(0.18f, 0.18f, 0.26f, 1.00f);
        
        // Title bar
        colors[ImGuiCol_TitleBg] = ImVec4(0.05f, 0.05f, 0.07f, 1.00f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.75f, 0.85f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.05f, 0.05f, 0.07f, 0.75f);
        
        // Accent colors - vibrant cyan
        ImVec4 accentColor = ImVec4(0.00f, 0.75f, 0.85f, 1.00f);
        ImVec4 accentHovered = ImVec4(0.15f, 0.85f, 0.95f, 1.00f);
        ImVec4 accentActive = ImVec4(0.00f, 0.60f, 0.70f, 1.00f);
        
        // Menu items
        colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.10f, 0.14f, 1.00f);
        
        // Buttons
        colors[ImGuiCol_Button] = ImVec4(0.12f, 0.12f, 0.16f, 1.00f);
        colors[ImGuiCol_ButtonHovered] = accentHovered;
        colors[ImGuiCol_ButtonActive] = accentActive;
        
        // Headers (collapsing headers, tree nodes, selectables, menu items)
        colors[ImGuiCol_Header] = ImVec4(accentColor.x, accentColor.y, accentColor.z, 0.40f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(accentHovered.x, accentHovered.y, accentHovered.z, 0.60f);
        colors[ImGuiCol_HeaderActive] = ImVec4(accentActive.x, accentActive.y, accentActive.z, 0.80f);
        
        // Resize grip
        colors[ImGuiCol_ResizeGrip] = ImVec4(0.25f, 0.25f, 0.30f, 1.00f);
        colors[ImGuiCol_ResizeGripHovered] = accentHovered;
        colors[ImGuiCol_ResizeGripActive] = accentActive;
        
        // Tabs
        colors[ImGuiCol_Tab] = ImVec4(0.08f, 0.08f, 0.12f, 1.00f);
        colors[ImGuiCol_TabHovered] = ImVec4(accentHovered.x, accentHovered.y, accentHovered.z, 0.80f);
        colors[ImGuiCol_TabActive] = ImVec4(accentColor.x, accentColor.y, accentColor.z, 0.60f);
        colors[ImGuiCol_TabUnfocused] = ImVec4(0.06f, 0.06f, 0.08f, 1.00f);
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.10f, 0.10f, 0.14f, 1.00f);
        
        // Tables
        colors[ImGuiCol_TableHeaderBg] = ImVec4(0.08f, 0.08f, 0.12f, 1.00f);
        colors[ImGuiCol_TableBorderStrong] = ImVec4(0.18f, 0.18f, 0.24f, 0.60f);
        colors[ImGuiCol_TableBorderLight] = ImVec4(0.14f, 0.14f, 0.18f, 0.40f);
        colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_TableRowBgAlt] = ImVec4(0.06f, 0.06f, 0.10f, 0.50f);
        
        // Scrollbar
        colors[ImGuiCol_ScrollbarBg] = ImVec4(0.04f, 0.04f, 0.06f, 0.60f);
        colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.25f, 0.25f, 0.30f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.35f, 0.35f, 0.40f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabActive] = accentActive;
        
        // Slider
        colors[ImGuiCol_SliderGrab] = accentColor;
        colors[ImGuiCol_SliderGrabActive] = accentHovered;
        
        // Checkbox
        colors[ImGuiCol_CheckMark] = accentColor;
        
        // Plot/Graph
        colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.60f, 0.80f, 1.00f);
        colors[ImGuiCol_PlotLinesHovered] = accentHovered;
        colors[ImGuiCol_PlotHistogram] = ImVec4(0.00f, 0.75f, 0.85f, 0.80f);
        colors[ImGuiCol_PlotHistogramHovered] = accentHovered;
        
        // Drag and drop
        colors[ImGuiCol_DragDropTarget] = ImVec4(accentColor.x, accentColor.y, accentColor.z, 0.90f);
        
        // Nav highlight
        colors[ImGuiCol_NavHighlight] = accentColor;
        colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
        
        // Modal dimming
        colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.60f);
    }
    
    void PushAccentStyle()
    {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.00f, 0.75f, 0.85f, 1.00f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.15f, 0.85f, 0.95f, 1.00f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.00f, 0.60f, 0.70f, 1.00f));
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.06f, 0.06f, 0.08f, 1.00f));
    }
    
    void PopAccentStyle()
    {
        ImGui::PopStyleColor(4);
    }
    
    void PushWarningStyle()
    {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.85f, 0.55f, 0.10f, 1.00f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.95f, 0.65f, 0.20f, 1.00f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.75f, 0.45f, 0.00f, 1.00f));
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.06f, 0.06f, 0.08f, 1.00f));
    }
    
    void PopWarningStyle()
    {
        ImGui::PopStyleColor(4);
    }
    
    void PushSuccessStyle()
    {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.20f, 0.75f, 0.40f, 1.00f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.30f, 0.85f, 0.50f, 1.00f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.10f, 0.65f, 0.30f, 1.00f));
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.06f, 0.06f, 0.08f, 1.00f));
    }
    
    void PopSuccessStyle()
    {
        ImGui::PopStyleColor(4);
    }
    
    void DrawSectionHeader(const char* text)
    {
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.00f, 0.75f, 0.85f, 1.00f));
        if (FontBold)
            ImGui::PushFont(FontBold);
        
        ImGui::SeparatorText(text);
        
        if (FontBold)
            ImGui::PopFont();
        ImGui::PopStyleColor();
    }
    
    bool StyledButton(const char* label, bool useAccent, ImVec2 size)
    {
        if (useAccent)
        {
            PushAccentStyle();
            bool result = ImGui::Button(label, size);
            PopAccentStyle();
            return result;
        }
        return ImGui::Button(label, size);
    }
}
