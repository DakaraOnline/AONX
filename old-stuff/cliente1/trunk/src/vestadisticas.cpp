
#include "vestadisticas.h"
#include <sstream>
#include "clienteargentum.h"
#include "helpers.h"
#include "configdata.h"


vestadisticas::vestadisticas()
{
	setSize(300,390);
	setBaseColor(gcn::Color(0x20,0x20,0xFF,127));
	setCaption("Estadisticas");
	
	img = NULL;

	for(int i=0;i<NUM_ATTRIBUTES;i++)
	{
		_attributes[i] = new gcn::Label("0");
		//_attributes_names[i] = new gcn::Label("Nombre");
		_attributes[i]->setWidth(18);
		_attributes[i]->setHeight(12);
		//_attributes_names[i]->setWidth(80);
		//_attributes_names[i]->setHeight(12);
		add(_attributes[i],15+93,52+i*23);
		//add(_attributes_names[i],15,40+i*20);
	}


	for(int i=0;i<NUM_SKILLS;i++){
		//SkillName[i] = new gcn::Label("Nombre");
		//SkillName[i]->setWidth(80);
		//SkillName[i]->setHeight(302/21);
		//add(SkillName[i],240-100,14+i*(int)(302/20.9));
		Skill[i] = new gcn::Label("0");
		Skill[i]->setWidth(22);
		Skill[i]->setAlignment(gcn::Graphics::CENTER);
		Skill[i]->setHeight(302/22);
		add(Skill[i],248,43+i*(int)(302/21.9));//Magic align trick :D xDD
		Skill_up[i] = new NoDrawButton;
		Skill_down[i] = new NoDrawButton;
		Skill_up[i]->setBaseColor(gcn::Color(0x20,0x20,0xFF,127));
		Skill_up[i]->setWidth(10);
		Skill_up[i]->setHeight(302/22);
		Skill_down[i]->setBaseColor(gcn::Color(0x20,0x20,0xFF,127));
		Skill_down[i]->setWidth(10);
		Skill_down[i]->setHeight(302/22);
		std::stringstream pepe;
		pepe.str("");
		pepe << i;
		Skill_down[i]->setActionEventId(std::string("SD") + pepe.str());
		Skill_up[i]->setActionEventId(std::string("SU") + pepe.str());
		Skill_down[i]->addActionListener(this);
		Skill_up[i]->addActionListener(this);
		add(Skill_down[i],265,43+i*(int)(302/21.9));
		add(Skill_up[i],239,43+i*(int)(302/21.9));
	}

	Label_Restantes = new gcn::Label("0");
	Label_Restantes->setWidth(19);
	Label_Restantes->setHeight(12);
	add(Label_Restantes,248,14);

	Commit = new NoDrawButton;
	Cancel = new NoDrawButton;
	Commit->setWidth(85);
	Cancel->setWidth(85);
	Commit->setHeight(25);
	Cancel->setHeight(25);
	Commit->setBaseColor(gcn::Color(0x20,0x20,0xFF,107));
	Cancel->setBaseColor(gcn::Color(0x20,0x20,0xFF,107));
	add(Cancel,35,302+24);
	add(Commit,170,302+24);

	Commit->setActionEventId("COMMIT_SKILLS");
	Commit->addActionListener(this);

	Cancel->setActionEventId("STATS_TOGGLE");
	Cancel->addActionListener(ClienteArgentum::instancia());

	ClienteArgentum::instancia()->attributes().AddObserver(this);
	ClienteArgentum::instancia()->skills().AddObserver(this);
	visible= false;
}

void vestadisticas::draw(gcn::Graphics *graphics)
{
	if(!img){
		std::stringstream imgPath(std::string(""));
		imgPath << ConfigData::GetPath("gui") << "estadisticas.png";
		img = gcn::Image::load(imgPath.str());
	}
	graphics->drawImage(img,0,0);
	drawChildren(graphics);
}

vestadisticas::~vestadisticas()
{
	ClienteArgentum::instancia()->attributes().DelObserver(this);
	ClienteArgentum::instancia()->skills().DelObserver(this);

	
	for(int i=0;i<NUM_SKILLS;i++)
	{
		remove(Skill[i]);
		delete Skill[i];
		//remove(SkillName[i]);
		//delete SkillName[i];
		remove(Skill_down[i]);
		delete Skill_down[i];
		remove(Skill_up[i]);
		delete Skill_up[i];
	}

	for(int i=0;i<NUM_ATTRIBUTES;i++)
	{
		remove(_attributes[i]);
		delete _attributes[i];
		//remove(_attributes_names[i]);
		//delete _attributes_names[i];
	}

	remove(Label_Restantes);
	delete Label_Restantes;

	remove(Cancel);
	delete Cancel;
	remove(Commit);
	delete Commit;

}

void vestadisticas::update(Skills *d)
{
	for(int i=0;i<NUM_SKILLS;i++)
	{
		Skill[i]->setCaption(to_string((*d)[i].get()));
		//SkillName[i]->setCaption((*d)[i].getName());
	}
	Label_Restantes->setCaption(to_string((*d).getFree()));

}

void vestadisticas::update(Attributes *d)
{
	for(int i=0;i<NUM_ATTRIBUTES;i++)
	{
		_attributes[i]->setCaption(to_string((*d)[i].get()));
		//_attributes_names[i]->setCaption((*d)[i].getName());
	}
}

void vestadisticas::action(const gcn::ActionEvent& actionEvent)
{
	int n;
	int t;
	int n2;
	if(actionEvent.getId().substr(0,2)=="SD")
	{
		n = to_number(actionEvent.getId().substr(2,2));
		t = to_number(Label_Restantes->getCaption());
		n2 = to_number(Skill[n]->getCaption());

		if((n2>0)&&(n2>ClienteArgentum::instancia()->skills()[n].get()))
		{
			t++;
			n2--;
			Label_Restantes->setCaption(to_string(t));
			Skill[n]->setCaption(to_string(n2));
		}

	}else if(actionEvent.getId().substr(0,2)=="SU")
	{
		n = to_number(actionEvent.getId().substr(2,2));
		t = to_number(Label_Restantes->getCaption());
		n2 = to_number(Skill[n]->getCaption());

		if((t>0)&&(n2!=100))
		{
			t--;
			n2++;
			Label_Restantes->setCaption(to_string(t));
			Skill[n]->setCaption(to_string(n2));
		}
	}else if(actionEvent.getId()=="COMMIT_SKILLS")
	{
		std::vector<Sint8> skillsv(21);
		for(int i=0;i<21;i++)
		{
			skillsv[i] = to_number(Skill[i]->getCaption());
		}
		ClienteArgentum::instancia()->ModifySkills(&skillsv, to_number(Label_Restantes->getCaption()));
		ClienteArgentum::instancia()->action(gcn::ActionEvent(this,"STATS_TOGGLE"));
	}
}

bool vestadisticas::is_visible()
{
	return visible;
}

void vestadisticas::set_visible(const bool a)
{
	visible = a;
}