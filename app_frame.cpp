#include"app_frame.h"
SwitchDNSFrame::SwitchDNSFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	Ads = DNStest::DNS_search();
	wxBoxSizer* FirstSizer;
	FirstSizer = new wxBoxSizer(wxVERTICAL);
	gSizer2 = new wxGridSizer(0, 2, 0, 0);
	unsigned int cnt = 0;
	for (auto i : Ads) {
		std::string s = i.first + "\n" + i.second.first;
		for (auto j : i.second.second)s += "\n\t" + j;
		Adapters.push_back(std::make_pair(
			new wxStaticText(this, wxID_ANY, _(s.c_str()), wxDefaultPosition, wxDefaultSize, 0),
			new wxButton(this, cnt+5000, _("set DNS"), wxDefaultPosition, wxDefaultSize, 0)));
		Adapters[cnt].first->Wrap(-1);
		gSizer2->Add(Adapters[cnt].first, 0, wxALL, 5);
		gSizer2->Add(Adapters[cnt].second, 0, wxALL, 5);
		mp[Adapters[cnt].second->GetId()] = i.first;
		Adapters[cnt++].second->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(SwitchDNSFrame::AdaptersDNS), NULL, this);
	}
	FirstSizer->Add(gSizer2, 1, wxEXPAND, 5);
	DNS_servers = new wxTextCtrl(this, wxID_ANY, _("please press the button\n\t\"test DNS servers\""), wxDefaultPosition, wxSize(475, 100), wxTE_MULTILINE);
	FirstSizer->Add(DNS_servers, 0, wxALL, 5);
	retest = new wxButton(this, wxID_ANY, _("test DNS servers"), wxDefaultPosition, wxDefaultSize, 0);
	FirstSizer->Add(retest, 0, wxALL, 5);
	SetSizer(FirstSizer);
	Layout();
	DNS_servers->SetEditable(false);
	m_menubar = new wxMenuBar(0);
	m_menu = new wxMenu();
	wxMenuItem* websites_menu;
	websites_menu = new wxMenuItem(m_menu, wxID_ANY, wxString(_("modify websites")), wxEmptyString, wxITEM_NORMAL);
	m_menu->Append(websites_menu);
	wxMenuItem* DNS_menu;
	DNS_menu = new wxMenuItem(m_menu, wxID_ANY, wxString(_("modify DNS servers")), wxEmptyString, wxITEM_NORMAL);
	m_menu->Append(DNS_menu);
	m_menubar->Append(m_menu, _("Files"));
	SetMenuBar(m_menubar);
	Centre(wxBOTH);
	retest->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(SwitchDNSFrame::tests), NULL, this);
	m_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(SwitchDNSFrame::setWeb), this, websites_menu->GetId());
	m_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(SwitchDNSFrame::setDNS), this, DNS_menu->GetId());
}
void SwitchDNSFrame::tests(wxCommandEvent& event) {
	DNS_servers->SetLabelText((wxString)"test...");
	Layout();
	std::thread T(DNStest::tests, 1, &DNStests);
	T.join();
	DNS_servers->SetLabelText((wxString)"");
	for (auto i : DNStests) {
		char t[100] = {};
		sprintf(t, "\t\taverage time:%.2fms, success rate:%.2f\0", i.second.first, i.second.second * 100);
		DNS_servers->AppendText((wxString)(i.first + t + "%\n"));
	}
	Layout();
}
void SwitchDNSFrame::flush_a() {
	Ads = DNStest::DNS_search();
	for (auto i : Adapters) { delete i.first;delete i.second; }
	gSizer2->Clear(false);mp.clear();Adapters.clear();
	unsigned int cnt = 0;
	for (auto i : Ads) {
		std::string s = i.first + "\n" + i.second.first;
		for (auto j : i.second.second)s += "\n\t" + j;
		Adapters.push_back(std::make_pair(
			new wxStaticText(this, wxID_ANY, _(s.c_str()), wxDefaultPosition, wxDefaultSize, 0),
			new wxButton(this, cnt + 5000, _("set DNS"), wxDefaultPosition, wxDefaultSize, 0)));
		Adapters[cnt].first->Wrap(-1);
		gSizer2->Add(Adapters[cnt].first, 0, wxALL, 5);
		gSizer2->Add(Adapters[cnt].second, 0, wxALL, 5);
		mp[Adapters[cnt].second->GetId()] = i.first;
		Adapters[cnt++].second->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(SwitchDNSFrame::AdaptersDNS), NULL, this);
	}
	Layout();
}
bool SwitchDNSApp::OnInit()
{
	SwitchDNSFrame* frame = new SwitchDNSFrame();
	frame->Show(true);
	HWND consoleWnd = GetConsoleWindow();
	if (consoleWnd != NULL) ShowWindow(consoleWnd, SW_HIDE);
	return true;
}