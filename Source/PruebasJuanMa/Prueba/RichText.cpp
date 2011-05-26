#include "StdAfx.h"
#include "RichText.h"

std::string RichText::MENU_HEADER1	= "menu_header1";
std::string RichText::NORMAL		= "normal";
std::string RichText::MENU_ITEM		= "menu_item";


RichText::RichText(std::string txt, std::string type): Image(1,1){
	
	int letterWidth		= 17;
	int letterHeight	= 17;
	
	// nueva imagen
	Image* aux = new Image((letterWidth*txt.length()), letterHeight);

	// recorro el texto a renderizar
	for(size_t i=0; i < txt.length(); i++){
		
		Image* letter = new Image("images/text/" + type + "/" + txt.at(i) + ".bmp");
		
		SDL_Rect* dst = new SDL_Rect();
		dst->h=17;
		dst->w=17;
		dst->x=(letterWidth*i);
		dst->y=0;
		
		SDL_BlitSurface(letter->getSDLSurface(), NULL, aux->getSDLSurface(), dst);

	}
	this->copy(*aux);
}
