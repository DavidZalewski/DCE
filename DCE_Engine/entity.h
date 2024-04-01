#pragma once

class Entity {
private:
	char * _fileName;

public:
	Entity(char* fileName);

	char* getFileName();

};