#include <map>
#include <vector>
#include <algorithm>

//stl container wrappers for ImGui
namespace pk
{

namespace ImGuiUtilities
{

/////////////////////////////////////
/// \fn void removeDuplicatesSorted(std::vector<std::string> &vec)
/// \brief Removes duplicate strings from
/// a sorted vector. Useful for Combo and ListBox
/// when duplicate entries are undesirable.
/// \param std::vector<std::string> &vec - a reference
/// to a std::vector of std::string.
/////////////////////////////////////
void removeDuplicatesSorted(std::vector<std::string> &vec)
{
    vec.erase( std::unique( vec.begin(), vec.end() ), vec.end() );
}

///////////////////////////////////////
/// \fn void removeDuplicates(std::vector<std::string> &vec)
/// \brief Sort a vector and remove duplicates
/// from it. Useful for Combo and ListBox
/// when duplicate entries are undesirable.
/// \param std::vector<std::string> &vec - a reference
/// to a std::vector of std::string.
///////////////////////////////////////
void removeDuplicates(std::vector<std::string> &vec)
{
    std::sort( vec.begin(), vec.end() );
    vec.erase( unique( vec.begin(), vec.end() ), vec.end() );
}

////////////////////////////////////////////////
/// \fn static void HelpMarker(const char* desc)
/// \brief Inserts a help marker next to an ImGui
/// element.
////////////////////////////////////////////////
static void HelpMarker(const char* desc)
{
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

////////////////////////////////////////////////////////////////////////////
/// \fn static auto vector_getter = [](void* vec, int idx, const char** out_text)
/// \brief Function for converting an array of std::string to an array of
/// const char* without copying the data. Useful for ImGui::List, ImGui::Combo,
/// or any other ImGui element that needs arrays of strings as const char*.
////////////////////////////////////////////////////////////////////////////
static auto vector_getter = [](void* vec, int idx, const char** out_text)
{
    auto& vector = *static_cast<std::vector<std::string>*>(vec);
    if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
    *out_text = vector.at(idx).c_str();
    return true;
};

////////////////////////////////////////////////////////////////////////////////////
/// \fn bool Combo(const char* label, int* currIndex, std::vector<std::string>& values)
/// \brief Wrapper function that takes a std::vector<std::string> and converts
/// it in place to build an ImGui::Combo element.
////////////////////////////////////////////////////////////////////////////////////
bool Combo(const char* label, int* currIndex, std::vector<std::string>& values)
{
    if (values.empty()) { return false; }
    return ImGui::Combo(label, currIndex, vector_getter, static_cast<void*>(&values), values.size());
}

////////////////////////////////////////////////////////////////////////////////////
/// \fn bool ListBox(const char* label, int* currIndex, std::vector<std::string>& values)
/// \brief Wrapper function that takes a std::vector<std::string> and converts
/// it in place to build an ImGui::ListBox element.
////////////////////////////////////////////////////////////////////////////////////
bool ListBox(const char* label, int* currIndex, std::vector<std::string>& values)
{
    if (values.empty()) { return false; }
    return ImGui::ListBox(label, currIndex, vector_getter, static_cast<void*>(&values), values.size());
}

}

}
