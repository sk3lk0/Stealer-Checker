#include "bitmaps.hpp"
#include "cjson.h"

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/filehistory.h>

#include <wx/aboutdlg.h>

#include <wx/notebook.h>

#include <wx/treectrl.h>
#include <wx/listctrl.h>

#include <wx/clipbrd.h>

#include <wx/file.h>

#include <thread>

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

				break;
			case wxID_NEW:

				break;
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

	void ProcessPath(const wxString Path)
	{

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

	void OnCharHook(wxKeyEvent& Event)
	{

	}

	void OnClose(wxCloseEvent& Event)
	{
		Destroy();
	}

	wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(Frame, wxFrame)
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