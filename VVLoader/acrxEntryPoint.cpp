#include "StdAfx.h"
#include "resource.h"

// 全局浮点数精度
// 主要用于几何坐标判断
#define GLOBAL_TOLERANCE 1e-5

#include <ArxHelper/HelperClass.h>

#include <PyArx/InitPython.h>

#include <python.h>
#include <boost/python.hpp>
using namespace boost;

// 系统精度设置器全局变量
ArxTolSetter* pTS = 0;

static CString BuildArxFileName( const CString& arxModuleName )
{
    CString str;
    str.Format( _T( "%s.arx" ), arxModuleName );
    return str;
}

static CString BuildServiceName( const CString& arxModuleName )
{
    CString str;
    str.Format( _T( "%s_SERVICE_NAME" ), arxModuleName );
    return str.MakeUpper();
}

static void SetAutoCADTitle()
{
    //CWnd *pp= AfxGetMainWnd();
    CMDIFrameWnd* pp = acedGetAcadFrame();
    //CString appName = pp->GetWindowTitle();
    //acutPrintf(_T("\n程序名:%s"),appName);
    //acedGetAcadFrame()->ModifyStyle(0,WS_SYSMENU|WS_MAXIMIZEBOX|WS_MINIMIZEBOX);
    //AfxGetMainWnd()->SetWindowText(_T("瓦斯抽采达标评价系统(AutoCAD 2010版)"));
    pp->SetWindowText ( _T( "井下煤层气规模化抽采计算机辅助设计（CAD）系统" ) );
    //HICON hIcon =AfxGetApp()->LoadIcon(IDI_ICON1);
    //pp->SetIcon(hIcon,TRUE);
    //pp->SetIcon(hIcon,FALSE);
    pp->UpdateWindow ();
}

void simple_test()
{
	python::object main_module = python::import("__main__");
	python::object main_namespace = main_module.attr("__dict__");

	python::exec("result = 5 ** 2", main_namespace);
	int five_squared = python::extract<int>(main_namespace["result"]);
	acutPrintf(_T("\n解算结果:%d"), five_squared);

	// Load the sys module.
	python::object sys = python::import("sys");
	// Extract the python version.
	std::string version = python::extract<std::string>(sys.attr("version"));
	acutPrintf(_T("\n版本:%s"), C2W(version));
	python::exec("python_path = '\\n'.join(sys.path)", main_namespace);
	std::string python_path = python::extract<std::string>(main_namespace["python_path"]);
	acutPrintf(_T("\n系统路径:%s"), C2W(python_path));

	////要求simple.py与可执行文件在相同路径下! 运行ok
	//object simple = exec_file("simple.py",main_namespace, main_namespace);
	////dict global;
	////object result = exec_file("simple.py", global, global);
	//object foo = main_namespace["foo"];
	//int val = extract<int>(foo(5));
	//cout << "Python has caculated foo as " << val << endl;

	///////////////////////另一个例子////////////////////////
	//python::dict global;
	//python::object result = python::exec_file("test.py", global, global);
	python::object result = python::exec_file("./simple.py", main_namespace, main_namespace);
}

void SetPythonPath()
{
	CString stmt;
	stmt.Format(_T("sys.path.append(\"%s\")"), PathHelper::GetCurDir().c_str());
	acutPrintf(stmt);

	PyRun_SimpleString("import sys");
	//PyRun_SimpleString("sys.path.append(\"<some_path>\")");
	PyRun_SimpleString(W2C((LPCTSTR)stmt));
}

void EmbedPythonInterpreter()
{	

	// Python解释器初始化
	InitPythonEnv();

	try
	{
		// 设置PYTHONPATH环境变量
		SetPythonPath();
		// 测试
		simple_test();
	}
	catch(std::exception& e)
	{
		acutPrintf(_T("\nError in c++: %s"), C2W(e.what()));
	}

	// Python解释器退出和清理
	UnInitPythonEnv();
}

class CVVLoaderApp : public AcRxArxApp
{

public:
    CVVLoaderApp () : AcRxArxApp () {}

    virtual AcRx::AppRetCode On_kInitAppMsg ( void* pkt )
    {
        AcRx::AppRetCode retCode = AcRxArxApp::On_kInitAppMsg ( pkt ) ;

		//// Python解释器初始化
		//InitPythonEnv();

        // 修改cad系统全局精度
        pTS = new ArxTolSetter( GLOBAL_TOLERANCE );

        // 初始化可视化系统
        if( !initDrawSystem() ) return AcRx::kRetError;

        // 加载图元模块
        if( !loadGEModule() ) return AcRx::kRetError;

        // 加载命令模块
        if( !loadCmdModule() ) return AcRx::kRetError;

        // 加载专业功能模块
        if( !loadFunctionModule() ) return AcRx::kRetError;

        acutPrintf( _T( "\nVVLoader::On_kInitAppMsg\n" ) );

        SetAutoCADTitle();

        return ( retCode ) ;
    }

    virtual AcRx::AppRetCode On_kUnloadAppMsg ( void* pkt )
    {
        AcRx::AppRetCode retCode = AcRxArxApp::On_kUnloadAppMsg ( pkt ) ;

        // 恢复cad系统的全局精度
        delete pTS;
        pTS = 0;

        // 卸载专业功能模块
        unloadFunctionModule();

        // 卸载命令模块
        unloadCmdModule();

        // 卸载图元模块
        unloadGEModule();

        // 退出可视化系统
        unInitDrawSystem();

        acutPrintf( _T( "\nVVLoader::On_kUnloadAppMsg\n" ) );

		//// Python解释器退出和清理
		//UnInitPythonEnv();

        return ( retCode ) ;
    }

    virtual void RegisterServerComponents ()
    {
    }

    bool loadArxModule( const CString& arxModuleName )
    {
        CString arxName = BuildArxFileName( arxModuleName );
        CString serviceName = BuildServiceName( arxModuleName );

        AcRxObject* pSvc = acrxServiceDictionary->at ( serviceName );
        if( pSvc == NULL )
        {
            if( !acrxDynamicLinker->loadModule( arxName, false ) )
            {
                acutPrintf ( _T( "\n加载%s模块失败...\n" ), arxName ) ;
                return false;
            }
            acutPrintf ( _T( "\n成功加载%s模块...\n" ), arxName ) ;
        }
        else
        {
            acutPrintf ( _T( "\n%s模块已经加载过了...\n" ), arxName ) ;
        }
        return true;
    }

    void unloadArxModule( const CString& arxModuleName )
    {
        acrxDynamicLinker->unloadModule( BuildArxFileName( arxModuleName ), 0 );
        acutPrintf( _T( "\n卸载模块:%s\n" ), arxModuleName );
    }

    bool initDrawSystem()
    {
        //if( !loadArxModule( _T( "MineGEDraw" ) ) ) return false;
        //// 初始化MineGEDrawSystem
        //MineGEDrawSystem::CreateInstance();
        //MineGEDrawSystem* pDrawSystem = MineGEDrawSystem::GetInstance();
        //pDrawSystem->loadPlugin( ArxUtilHelper::BuildPath( ArxUtilHelper::GetAppPathDir(_hdllInstance), _T( "DefGEPlugin.arx" ) ) );

        return true;
    }

    void unInitDrawSystem()
    {
        // 退出并清理MineGEService系统
        //MineGEDrawSystem::DestroyInstance();
        //unloadArxModule( _T( "MineGEDraw" ) );
    }

    // 加载图元模块
    bool loadGEModule()
    {
        acutPrintf( _T( "\n-------- 加载图元模块 ------------\n" ) );

        //if( !loadArxModule( _T( "MineGE" ) ) ) return false;
        //if( !loadArxModule( _T( "DefGE" ) ) ) return false;

        return true;
    }

    void unloadGEModule()
    {
        acutPrintf( _T( "\n-------- 卸载图元模块 ------------" ) );

        //unloadArxModule( _T( "DefGE" ) );
        //unloadArxModule( _T( "MineGE" ) );
    }

    bool loadCmdModule()
    {
        acutPrintf( _T( "\n-------- 加载命令模块 ------------" ) );

        //if( !loadArxModule( _T( "MineGECmds" ) ) ) return false;
        //if( !loadArxModule( _T( "DrawVentCmd" ) ) ) return false;

        return true;
    }

    void unloadCmdModule()
    {
        acutPrintf( _T( "\n-------- 卸载命令模块 ------------" ) );

        //unloadArxModule( _T( "MineGECmds" ) );
        //unloadArxModule( _T( "DrawVentCmd" ) );
    }

    bool loadFunctionModule()
    {
        acutPrintf( _T( "\n-------- 加载功能模块 ------------" ) );

        if( !loadArxModule( _T( "ArxSoUI" ) ) ) return false;

        return true;
    }

    void unloadFunctionModule()
    {
        acutPrintf( _T( "\n-------- 卸载功能模块 ------------" ) );

        unloadArxModule( _T( "ArxSoUI" ) );
    }

    static void VVTest_testVector()
    {
        AcGeVector3d v( AcGeVector3d::kXAxis );
        v.rotateBy( PI / 6, AcGeVector3d::kZAxis );

        acutPrintf( _T( "\n%.3f, %.3f, %.3f" ), v.x, v.y, v.z );

        AcGeVector3d vv( -1, 1, 0 );
        double ang = vv.angleTo( AcGeVector3d::kYAxis, AcGeVector3d::kZAxis );
        acutPrintf( _T( "\n角度:%.3f" ), ang );
        /*
        	    AcGeVector3d v1( 100, 20, 0 );
        	    AcGeVector3d v2( 10, 50, 1 );
        	    AcGeVector3d v3 = v1.crossProduct( v2 );
        	    AcGeVector3d v4 = v2.crossProduct( v1 );

        	    acutPrintf( _T( "\n叉乘z1=%.3f, z2:%.3f" ), v3.z, v4.z );

        	    AcGePoint3d p1, p2( 1, 1, 0 ), p3( 2, 0, 0 ), p4( 1, -1, 0 );
        	    AcGeCircArc3d arc( p1, p2, p3 );
        	    AcGeCircArc3d arc2( p3, p2, p1 );
        	    AcGeCircArc3d arc3( p2, p4, p3 );
        	    AcGeCircArc3d arc4( p1, p3, p4 );

        	    acutPrintf( _T( "\n弧线z1=%.3f, z2:%.3f" ), arc.normal().z, arc2.normal().z );
        	    acutPrintf( _T( "\n[1]start angle:%.3f, end angle:%.3f" ), arc.startAng(), arc.endAng() );
        	    acutPrintf( _T( "\n[2]start angle:%.3f, end angle:%.3f" ), arc2.startAng(), arc2.endAng() );
        	    acutPrintf( _T( "\n[3]start angle:%.3f, end angle:%.3f" ), arc3.startAng(), arc3.endAng() );
        	    acutPrintf( _T( "\n[4]start angle:%.3f, end angle:%.3f" ), arc4.startAng(), arc4.endAng() );

        	    AcGeVector3d v5( 0, -1, 0 ), v6( 0, 1, 0 );
        	    double a1 = v5.angleTo( AcGeVector3d::kXAxis, -AcGeVector3d::kZAxis );
        	    double a2 = v6.angleTo( AcGeVector3d::kXAxis, -AcGeVector3d::kZAxis );

        	    acutPrintf( _T( "\na1:%.3f, a2:%.3f" ), a1, a2 );

        	    ads_point pt1, pt2, pt3, pt4;
        	    ads_name ssname;
        	    pt1[X] = pt1[Y] = pt1[Z] = 0.0;
        	    pt2[X] = pt2[Y] = 5.0;
        	    pt2[Z] = 0.0;

        	    // Get the current PICKFIRST set, if there is one;
        	    // otherwise, ask the user for a general entity selection.
        	    acedSSGet( _T( ":S" ), NULL, NULL, NULL, ssname );

        	    acutPrintf( _T( "\nxxx\n" ) );
        	    //acedSSGet(NULL, NULL, NULL, NULL, ssname);

        		AcGeVector3d v(-1, 1, 0);
        		acutPrintf(_T("\n...........\n"));
        		acutPrintf(_T("\n投影前:(%.3f, %.3f, %.3f)"), v.x, v.y, v.z);

        		v = v.dotProduct( AcGeVector3d::kXAxis ) * AcGeVector3d::kXAxis;
        		acutPrintf(_T("\n投影后:(%.3f, %.3f, %.3f)"), v.x, v.y, v.z);
        */
    }


	static void VVTest_test_python()
	{
		EmbedPythonInterpreter();
	}
	
};

IMPLEMENT_ARX_ENTRYPOINT( CVVLoaderApp )

ACED_ARXCOMMAND_ENTRY_AUTO( CVVLoaderApp, VVTest, _testVector, tvec, ACRX_CMD_TRANSPARENT, NULL )
ACED_ARXCOMMAND_ENTRY_AUTO( CVVLoaderApp, VVTest, _test_python, test_python, ACRX_CMD_TRANSPARENT, NULL )
