#include "DatabaseTests.h"

DatabaseTests::DatabaseTests(void)
{
}

void DatabaseTests::printLeaks(int leaks)
{
	std::cout << "Bonus Tests: Hubo " << leaks << " memory leaks." << endl << endl;
}

void DatabaseTests::printResult(std::string testName, bool result)
{
	std::cout << (testName.append(result ? ": Passed\n" : ": Failed!!!\n"));
}

void DatabaseTests::run()
{
	printResult("testCreateTableSuccesfulyCreated", testCreateTableSuccesfulyCreated());
	printResult("testInsertData", testInsertData());
	printResult("testUpdateData", testUpdateData());
    int leaks = _CrtDumpMemoryLeaks();
    printLeaks(leaks);
}

bool DatabaseTests::testCreateTableSuccesfulyCreated()
{
	Database db("DatabaseTests01.db");
	List<std::string> argumentos;
	argumentos.add("NOMBRE VARCHAR(20)");
	argumentos.add("EDAD INT");

	db.createTable("personas", argumentos);
	List<std::string> listaTablas = db.getTables();
	
	if(listaTablas.at(0) != "personas")
	{
		db.deleteDatabase();
		return false;
	}

	db.executeQuery("insert into personas values ('Gonzalo', '21')");

	std::string qs = "select * from personas";
	List<QueryResult> listaResultados = db.executeQuery(qs);

	if(strcmp(listaResultados.at(0).getValue("NOMBRE").c_str(), "Gonzalo") != 0)
	{
		db.deleteDatabase();
		return false;
	}

	if(strcmp(listaResultados.at(0).getValue("EDAD").c_str(), "21") != 0)
	{
		db.deleteDatabase();
		return false;
	}

	db.deleteDatabase();
	return true;
}

bool DatabaseTests::testInsertData()
{
	Database db("DatabaseTests02.db");
	db.executeQuery("create table personas (nombre varchar(20), edad int)");

	List<std::string> values;
	values.add("'Gonzalo', '21'");
	db.insertData("personas", values);

	List<QueryResult> listaResultados = db.executeQuery("select * from personas");
	
	if(strcmp(listaResultados.at(0).getValue("nombre").c_str(), "Gonzalo") != 0)
	{
		db.deleteDatabase();
		return false;
	}

	if(strcmp(listaResultados.at(0).getValue("edad").c_str(), "21") != 0)
	{
		db.deleteDatabase();
		return false;
	}

	db.deleteDatabase();
	return true;
}

bool DatabaseTests::testUpdateData()
{
	Database db("DatabaseTests03.db");
	db.executeQuery("create table personas (nombre varchar(20), edad int)");
	db.executeQuery("insert into personas values('Gonzalo', '21')");

	List<std::string> values;
	values.add("nombre='Martin', edad='15'");
	db.updateData("personas", values);
	//db.executeQuery("update personas set nombre='Martin', edad='15'");

	List<QueryResult> listaResultados = db.executeQuery("select * from personas");
	
	if(strcmp(listaResultados.at(0).getValue("nombre").c_str(), "Martin") != 0)
	{
		db.deleteDatabase();
		return false;
	}

	if(strcmp(listaResultados.at(0).getValue("edad").c_str(), "15") != 0)
	{
		db.deleteDatabase();
		return false;
	}

	db.deleteDatabase();
	return true;
}

DatabaseTests::~DatabaseTests(void)
{
}
