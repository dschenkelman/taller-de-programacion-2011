#include "SQLite.h"

SQLite::SQLite(void)
{
}

bool SQLite::openDatabase(std::string uri)
{
	Database db(uri.c_str());

	if(!db.hasError())
	{
		this->listDatabases.add(db);
		return true;
	}

	return false;
}

bool SQLite::createDatabase(std::string uri)
{
	Database db(uri.c_str());

	if(!db.hasError())
	{
		this->listDatabases.add(db);
		return true;
	}

	return false;
}

bool SQLite::removeDatabase(std::string name)
{
	Database db;

	try
	{
		db = this->getDatabase(name);
	}
	catch(exception& e)
	{
		return false;
	}

	for(int i = 0; i < listDatabases.length(); i++)
	{
		if(listDatabases.at(i).getName() == db.getName())
		{
			listDatabases.removeAt(i);
			remove(name.c_str());
			return true;
		}
	}

	return false;
}

List<Database> SQLite::getListDatabases()
{
	return this->listDatabases;
}

Database SQLite::getDatabase(int index)
{
	return this->listDatabases.at(index);
}

Database SQLite::getDatabase(std::string uri)
{
	for(int i = 0; i < listDatabases.length(); i++)
	{
		if (listDatabases.at(i).getName() == uri)
		{
			return listDatabases.at(i);
		}	
	}

	throw std::exception();
}

SQLite::~SQLite(void)
{
}
