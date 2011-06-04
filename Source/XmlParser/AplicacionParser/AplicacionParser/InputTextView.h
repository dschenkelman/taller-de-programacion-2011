#pragma once
#include "RichTextView.h"

class InputTextView: public RichTextView{
public:
	InputTextView(std::string txt, int size);
	~InputTextView();
};