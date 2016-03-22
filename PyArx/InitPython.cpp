#include "StdAfx.h"

#include "InitPython.h"
#include <python.h>
#include <boost/python.hpp>
using namespace boost;

void InitPythonEnv()
{
	// Python��������ʼ��
	Py_Initialize();
}

void UnInitPythonEnv()
{
	// ����Python���������ͷ���Դ
	//Py_Finalize();//��Ҫ����Py_Finalize����Ϊboost��Ŀǰ�������ƣ���ȫ�ֱ�����δ�ͷ�
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
