#include "FileName.h"

string FileName::getTitle() {
	return title;
}

void FileName::setTitle(string _title) {
	title = _title;
}

string FileName::getFinalName() {
	return title + ext;
}
