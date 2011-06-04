#include "StdAfx.h"
#include "RichTextView.h"

std::string RichTextView::MENU_HEADER1	= "menu_header1";
std::string RichTextView::NORMAL			= "verdana_white_black";
std::string RichTextView::MENU_ITEM		= "menu_item";


RichTextView::RichTextView(std::string txt, std::string type, int r, int g, int b, int delta): View(r,g,b,delta){
	RichTextView::RichTextView(txt,type);
}


RichTextView::RichTextView(std::string txt, std::string type): View(){
	int letterCount = 0;
	int letterWidth		= 17;
	int letterHeight	= 17;
	
	// nueva imagen
	Image* aux = new Image((letterWidth*this->getLetterCount(txt)), letterHeight);

	// recorro el texto a renderizar
	size_t i=0;
	while( i < txt.length() ){
		char c = txt.at(i);
		std::string letterName = "";
		if(c == '&'){
			size_t k = i+1;
			while( k < txt.length() && txt.at(k) != ';'){
				letterName += txt.at(k);
				k++;
			}
			i=k;
		}else{
			letterName += c;
		}
		
		Image* letter = new Image("images/text/" + type + "/" + letterName + ".bmp");
		
		SDL_Rect dst;
		dst.h=letterHeight;
		dst.w=letterWidth;
		dst.x=(letterWidth*letterCount);
		dst.y=0;
		
		SDL_BlitSurface(letter->getSDLSurface(), NULL, aux->getSDLSurface(), &dst);
		delete letter;
		i++;
		letterCount++;
	}
	this->copy(*aux);

	delete aux;
}

RichTextView::~RichTextView(){}

int RichTextView::getLetterCount(std::string txt){
	int count = 0;
	size_t i=0;
	while( i < txt.length() ){
		char c = txt.at(i);
		std::string letterName = "";
		if(c == '&'){
			size_t k = i+1;
			while( k < txt.length() && txt.at(k) != ';'){
				k++;
			}
			i=k;
		}
		count++;
		i++;
	}
	return count;
}