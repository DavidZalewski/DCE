#include "pch.h"
#include "entity.h"


Entity::Entity(char* fileName) {
	this->_fileName = fileName;
}

char * Entity::getFileName() {
	return this->_fileName;
}