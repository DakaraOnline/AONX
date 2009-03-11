
#ifndef _vestadisticas_h_
#define _vestadisticas_h_

#include "SDL.h"
#include <guichan.hpp>
#include "customwidgets.h"
#include <string>
#include <vector>
#include "stats.h"

class vestadisticas : public gcn::Window, public gcn::ActionListener, public SkillsObserver, public AttributesObserver
{
public:

	vestadisticas();
	~vestadisticas();

	void update(Skills *d);
	void update(Attributes *d);
	void draw (gcn::Graphics *graphics);
	void drawBorder (gcn::Graphics *graphics){}

	void action(const gcn::ActionEvent& actionEvent);

	bool is_visible();
	void set_visible(const bool);

private:


	gcn::Label* _attributes[NUM_ATTRIBUTES];
	gcn::Label* _attributes_names[NUM_ATTRIBUTES];

	gcn::Label* SkillName[NUM_SKILLS];
	gcn::Label* Skill[NUM_SKILLS];
	gcn::Button* Skill_up[NUM_SKILLS];
	gcn::Button* Skill_down[NUM_SKILLS];

	gcn::Button* Commit;
	gcn::Button* Cancel;

	gcn::Label* Label_Restantes;

	bool visible;

	gcn::Image* img;
};


#endif // #ifdef _vestadisticas_h_
