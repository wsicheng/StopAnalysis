#ifndef ANALYZER_H
#define ANALYZER_H

// C++
#include <string>
#include <vector>
#include <iostream>


// Stop Analysis
#include "../StopCORE/stop_1l_babyAnalyzer.h"
#include "../StopCORE/genClassyInfo.h"


enum kJES{ kNominal=0, kUp=1, kDown=-1 };


class analyzer {

public:
	analyzer();
	// ~analyzer();

	void AddGenClassifications( std::vector<genClassyInfo::ID> new_classies );
	void AddSelection( std::string label, bool (*new_selection)() );
	void AddSelections( std::vector<std::pair<std::string,bool(*)()> > new_selections );
	void AddCategories( std::vector<something> new_categories );
	void AddSystematics( std::vector<sysInfo::ID> new_systematics );

	std::vector<genClassyInfo::ID> GetGenClassifications();
	std::vector<std::pair<std::string,bool(*)()> > GetSelections();
	std::vector<something> GetCategories();
	std::vector<sysInfo::ID> GetSystematics();
	bool GetAdd2ndLep();
	bool GetIncludeTaus();
	kJES GetJesType();

	bool PassSelections();

	void SetAdd2ndLep( bool use_lep2 );
	void SetIncludeTaus( bool use_taus );
	void SetJesType( kJES jestype );

private:
	std::vector<genClassyInfo::ID> classifications;
	std::vector< std::pair<std::string,bool(*)()> > selections;
	std::vector< something > categories;
	std::vector<sysInfo::ID> systematics;

	bool add2ndLep;
	bool includeTaus;
	kJES jesType;


};



#endif