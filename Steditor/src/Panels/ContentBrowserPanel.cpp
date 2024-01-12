#include "stpch.h"
#include "ContentBrowserPanel.h"

#include <imgui/imgui.h>

namespace Sten
{
	// TODO: projects
	static std::filesystem::path s_AssetsPath = "assets";

	ContentBrowserPanel::ContentBrowserPanel()
		: m_CurrentDirectory(s_AssetsPath)
	{
		m_DirectoryIcon = Texture2D::Create("assets/icons/contentbrowser/folder.png");
		m_FileIcon = Texture2D::Create("assets/icons/contentbrowser/file.png");
	}

	void ContentBrowserPanel::OnImGuiRender()
	{
		ImGui::Begin("Content Browser");

		if (m_CurrentDirectory != s_AssetsPath)
		{
			if (ImGui::Button("<-"))
			{
				m_CurrentDirectory = m_CurrentDirectory.parent_path();
			}
		}

		static float padding = 16.0f;
		static float thumbnailSize = 96.0f;
		float cellSize = thumbnailSize + padding;

		float panelWidth = ImGui::GetContentRegionAvail().x;
		int columnCount = (int)(panelWidth / cellSize);
		if (columnCount < 1)
			columnCount = 1;

		ImGui::Columns(columnCount, 0, false);

		for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(m_CurrentDirectory))
		{
			std::string path = entry.path().string();
			auto relativePath = std::filesystem::relative(entry.path(), s_AssetsPath);
			
			ImGui::PushID(relativePath.filename().string().c_str());

			Ref<Texture2D> icon = entry.is_directory() ? m_DirectoryIcon : m_FileIcon;
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0, 0, 0, 0});
			ImGui::ImageButton((ImTextureID)icon->GetRendererID(), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 });
			
			if (ImGui::BeginDragDropSource())
			{
				const char* itemPath = relativePath.c_str();
				ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", itemPath, strlen(itemPath) + 1);

				ImGui::EndDragDropSource();
			}

			ImGui::PopStyleColor();
			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			{
				if (entry.is_directory())
				{
					m_CurrentDirectory /= entry.path().filename();
				}
			}
			ImGui::TextWrapped(relativePath.string().c_str());

			ImGui::NextColumn();
			ImGui::PopID();	
		}

		ImGui::Columns(1);
		ImGui::End();
	}
}
