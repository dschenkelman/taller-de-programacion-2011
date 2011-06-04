#include "StdAfx.h"
#include "RichTextView.h"

std::string RichTextView::MENU_HEADER1	= "menu_header1";
std::string RichTextView::NORMAL			= "verdana_white_black";
std::string RichTextView::MENU_ITEM		= "menu_item";


RichTextView::RichTextView(std::string txt, std::string type, int r, int g, int b, int delta): View(r,g,b,delta){
	RichTextView::RichTextView(txt,type);
}


RichTextView::RichTextView(std::string txt, std::string type): View(){
	
	int letterWidth		= 17;
	int letterHeight	= 17;
	
	// nueva imagen
	Image* aux = new Image((letterWidth*txt.length()), letterHeight);

	// recorro el texto a renderizar
	for(size_t i=0; i < txt.length(); i++){
		
		Image* letter = new Image("images/text/" + type + "/" + txt.at(i) + ".bmp");
		
		SDL_Rect dst;
		dst.h=letterHeight;
		dst.w=letterWidth;
		dst.x=(letterWidth*i);
		dst.y=0;
		
		SDL_BlitSurface(letter->getSDLSurface(), NULL, aux->getSDLSurface(), &dst);
		delete letter;
	}
	this->copy(*aux);

	delete aux;
}

RichTextView::~RichTextView(){}