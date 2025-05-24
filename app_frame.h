#pragma once
#include"DNStest.h"
class SwitchDNSApp : public wxApp
{
public:
    bool OnInit() override;
};

class SwitchDNSFrame : public wxFrame
{
private:
protected:
	std::vector<std::pair<wxStaticText*,wxButton*> > Adapters;
	std::map<int, std::string>mp;
	wxTextCtrl* DNS_servers;
	wxButton* retest;
	wxMenuBar* m_menubar;
	wxMenu* m_menu;
	wxGridSizer* gSizer2;
	std::vector<std::pair<std::string, std::pair<double, double>>>DNStests;
	std::map<std::string, std::pair<std::string, std::vector<std::string>>> Ads;
	virtual void flush_a();
	virtual void tests(wxCommandEvent& event);
	virtual void AdaptersDNS(wxCommandEvent& event) {
		std::string s = mp[event.GetId()];
		if (DNStests.size() >= 1)system(("netsh interface ip set dns \"" + s + "\" static " + DNStests[0].first).c_str());
		if (DNStests.size() >= 2)system(("netsh interface ip add dns \"" + s + "\" " + DNStests[1].first).c_str());
		flush_a();
	}
	virtual void setWeb(wxCommandEvent& event) { DNSfiles::setWeb(); }
	virtual void setDNS(wxCommandEvent& event) { DNSfiles::setDNS(); }
public:
	SwitchDNSFrame(wxWindow* parent=NULL, wxWindowID id = wxID_ANY, const wxString& title = _("SwitchDNS"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(500, 600), long style = wxCAPTION | wxCLOSE_BOX | wxMINIMIZE | wxMINIMIZE_BOX | wxSYSTEM_MENU | wxTAB_TRAVERSAL);
	~SwitchDNSFrame() {};
};