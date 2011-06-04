#include "StdAfx.h"
#include "InputTextView.h"

InputTextView::InputTextView(std::string txt, int size):RichTextView(txt,RichTextView::NORMAL){
	
	int count = this->getLetterCount(txt);
	for(int i=count; i<size; i++){
		txt += "&udash;";
	}
	RichTextView* aux = new RichTextView(txt,RichTextView::NORMAL_GREEN);
	this->copy(*aux);
	delete aux;
}

InputTextView::~InputTextView(){
}