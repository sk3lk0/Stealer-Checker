#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class Frame : public wxFrame
{
public:
	Frame(): wxFrame(nullptr, wxID_ANY, "Stealer Checker")
	{
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