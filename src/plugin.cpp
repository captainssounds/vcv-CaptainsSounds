#include "plugin.hpp"

Plugin* pluginInstance;

void init(Plugin* p) {
	pluginInstance = p;

	// Add modules here
	p->addModel(modelBlank901);
	p->addModel(modelBlank902);
	p->addModel(modelBlank904);
	p->addModel(modelIMO);
	p->addModel(modelMIO);
	p->addModel(modelNip);
	p->addModel(modelPow);
	p->addModel(modelVBNO);

	// Any other plugin initialization may go here.
	// As an alternative, consider lazy-loading assets and lookup tables when your module is created to reduce startup times of Rack.
}