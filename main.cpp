#include "bitmaps.hpp"

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/aboutdlg.h>
#include <wx/notebook.h>
#include <wx/treectrl.h>
#include <wx/listctrl.h>

class Frame : public wxFrame
{
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

		Centre();
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
};

class Application : public wxApp
{
	bool OnInit() override
	{
		return (new Frame())->Show();
	}
};

wxIMPLEMENT_APP(Application);