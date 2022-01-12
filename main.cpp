#include "bitmaps.hpp"

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/aboutdlg.h>

#include <wx/notebook.h>

#include <wx/treectrl.h>
#include <wx/listctrl.h>

#include <wx/clipbrd.h>

class Frame : public wxFrame
{
	enum OwnedID
	{
		ID_COPY1 = 1,
		ID_COPY2,
		ID_COPY3
	};

public:
	Frame() : wxFrame(nullptr, wxID_ANY, "Stealer Checker")
	{
		MenuFile->Append(wxID_EXIT);
		MenuHelp->Append(wxID_ABOUT);

		MenuBar->Append(MenuFile, "&File");
		MenuBar->Append(MenuHelp, "&Help");

		MenuBar->Bind(wxEVT_MENU, [&](wxCommandEvent& Event)
		{
			switch (Event.GetId())
			{
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
			case wxID_EXIT:
				Close(true);
				break;
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

		Bind(wxEVT_MENU, &Frame::OnCopy1, this, ID_COPY1);
		LoginsListCtrl->Bind(wxEVT_LIST_ITEM_RIGHT_CLICK, [&](wxListEvent& Event)
		{
			wxMenu Menu;

			Menu.Append(new wxMenuItem(&Menu, ID_COPY1, "asd"));

			PopupMenu(&Menu);
		});

		Bind(wxEVT_MENU, &Frame::OnCopy2, this, ID_COPY2);
		WalletsListCtrl->Bind(wxEVT_LIST_ITEM_RIGHT_CLICK, [&](wxListEvent& Event)
		{
			wxMenu Menu;

			Menu.Append(new wxMenuItem(&Menu, ID_COPY2));

			PopupMenu(&Menu);
		});

		Bind(wxEVT_MENU, &Frame::OnCopy3, this, ID_COPY3);
		TokensListCtrl->Bind(wxEVT_LIST_ITEM_RIGHT_CLICK, [&](wxListEvent& Event)
		{
			wxMenu Menu;

			Menu.Append(new wxMenuItem(&Menu, ID_COPY3));

			PopupMenu(&Menu);
		});

		Centre();

		long LoginsListCtrlItem = LoginsListCtrl->InsertItem(LoginsListCtrl->GetItemCount(), "amoveo");
		LoginsListCtrl->SetItem(LoginsListCtrlItem, 1, "compello");
		LoginsListCtrl->SetItem(LoginsListCtrlItem, 2, "fluo");
		LoginsListCtrl->SetItem(LoginsListCtrlItem, 3, "hoc");

		LoginsListCtrlItem = LoginsListCtrl->InsertItem(LoginsListCtrl->GetItemCount(), "adstringo");
		LoginsListCtrl->SetItem(LoginsListCtrlItem, 1, "alioqui");
		LoginsListCtrl->SetItem(LoginsListCtrlItem, 2, "delecto");
		LoginsListCtrl->SetItem(LoginsListCtrlItem, 3, "edo");

		long WalletsListCtrlItem = WalletsListCtrl->InsertItem(WalletsListCtrl->GetItemCount(), "huius");
		WalletsListCtrl->SetItem(WalletsListCtrlItem, 1, "mussito");
		WalletsListCtrl->SetItem(WalletsListCtrlItem, 2, "plaustrum");

		WalletsListCtrlItem = WalletsListCtrl->InsertItem(WalletsListCtrl->GetItemCount(), "acidus");
		WalletsListCtrl->SetItem(WalletsListCtrlItem, 1, "aliquanta");
		WalletsListCtrl->SetItem(WalletsListCtrlItem, 2, "amitto");

		WalletsListCtrlItem = WalletsListCtrl->InsertItem(WalletsListCtrl->GetItemCount(), "aliquantus");
		WalletsListCtrl->SetItem(WalletsListCtrlItem, 1, "determino");
		WalletsListCtrl->SetItem(WalletsListCtrlItem, 2, "excipio");

		long TokensListCtrlItem = TokensListCtrl->InsertItem(TokensListCtrl->GetItemCount(), "pluvia");
		TokensListCtrl->SetItem(TokensListCtrlItem, 1, "tabellae");

		TokensListCtrlItem = TokensListCtrl->InsertItem(TokensListCtrl->GetItemCount(), "reprehendo");
		TokensListCtrl->SetItem(TokensListCtrlItem, 1, "sibimet");

		TokensListCtrlItem = TokensListCtrl->InsertItem(TokensListCtrl->GetItemCount(), "tergus");
		TokensListCtrl->SetItem(TokensListCtrlItem, 1, "emerio");

		TokensListCtrlItem = TokensListCtrl->InsertItem(TokensListCtrl->GetItemCount(), "absorbeo");
		TokensListCtrl->SetItem(TokensListCtrlItem, 1, "aqua");
	}

private:
	wxMenuBar* MenuBar = new wxMenuBar();
	wxMenu* MenuFile = new wxMenu(), * MenuHelp = new wxMenu();

	wxToolBar* ToolBar = CreateToolBar(wxTB_TEXT);
	wxToolBarToolBase* ToolBarAddTool = ToolBar->AddTool(wxID_ADD, "Add", wxBitmap(AddBitmap));
	wxToolBarToolBase* ToolBarRemoveTool = ToolBar->AddTool(wxID_REMOVE, "Remove", wxBitmap(RemoveBitmap));

	wxNotebook* Notebook = new wxNotebook(this, wxID_ANY);
	wxTreeCtrl* FilesTreeCtrl = new wxTreeCtrl(Notebook, 0, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE | wxTR_SINGLE | wxTR_HIDE_ROOT);
	wxTreeItemId FilesTreeCtrlRoot = FilesTreeCtrl->AddRoot(wxEmptyString);

	wxListCtrl* LoginsListCtrl = new wxListCtrl(Notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT), *WalletsListCtrl = new wxListCtrl(Notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT), *TokensListCtrl = new wxListCtrl(Notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);

	void OnCopy1(wxCommandEvent& Event)
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
	}

	void OnCopy2(wxCommandEvent& Event)
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
	}

	void OnCopy3(wxCommandEvent& Event)
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
	}
};

class Application : public wxApp
{
	bool OnInit() override
	{
		return (new Frame())->Show();
	}
};

wxIMPLEMENT_APP(Application);