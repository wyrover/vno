#include "StdAfx.h"

#include "InitPython.h"
#include <python.h>
#include <boost/python.hpp>
using namespace boost;

void InitPythonEnv()
{
	// Python解释器初始化
	Py_Initialize();
}

void UnInitPythonEnv()
{
	// 结束Python解释器，释放资源
	//Py_Finalize();//不要调用Py_Finalize，因为boost库目前还不完善，有全局变量还未释放
}

void exec_mythma()
{
	python::dict global;
	python::object result = python::exec_file("C://Develop//GitProject//vno//x64//Debug//test.py", global, global);

	python::object a = global["a"];
	python::object b = global["b"];

	//python::object world = global["world"];
	//CHelloWorld& py = python::extract<CHelloWorld&>(world) BOOST_EXTRACT_WORKAROUND;
	//std::cout << py.GetId() << std::endl;	
}

void EmbedPythonInterpreter()
{
	if (python::handle_exception(exec_mythma))
	{
		if (PyErr_Occurred())
		{
			//BOOST_ERROR("Python Error detected");
			PyErr_Print();
		}
		else
		{
			//BOOST_ERROR("A C++ exception was thrown  for which there was no exception translator registered.");
		}
	}
}
