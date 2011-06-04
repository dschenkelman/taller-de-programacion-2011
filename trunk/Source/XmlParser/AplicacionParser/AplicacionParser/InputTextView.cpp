#include "StdAfx.h"
#include "InputTextView.h"

InputTextView::InputTextView(int size):RichTextView("",RichTextView::NORMAL){
	std::string txt = "";
	for(int i=0; i<size; i++){
		txt += "&udash;";
	}
	RichTextView* aux = new RichTextView(txt,RichTextView::NORMAL_GREEN);
	this->copy(*aux);
	delete aux;
}

InputTextView::~InputTextView(){
}